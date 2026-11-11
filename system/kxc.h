/* kxc.h - Xinu の中で動くことのはのコンパイラ
 *
 *   ソース（文章形式）─ kxlex.c ─→ 字句 ─ kxc.y（bison）─→ 構文木 ─ kxcomp.c ─→ struct kprogram
 *
 * できた kprogram は k2xinu.mjs が Mac で作るものと同じ形なので、実行・デバッガ（krt.c・kgui.c）はそのまま使える。
 * 受信節は構文木をたどって実行する（kxcomp.c の実行器）。各文の前で kstep を呼ぶので停止点・1文実行も効く。
 * xinu.h には二重読み込みの防ぎが無いので、ここでは読まない（使う側が先に読む）。
 */
#ifndef KXC_H
#define KXC_H
#include "krt.h"

/* 式 */
enum { E_NAME, E_NUM, E_STR, E_TRUE, E_FALSE, E_NONE, E_ARR, E_SELF, E_CUR, E_FIELD, E_INDEX, E_LEN,
       E_ADD, E_SUB, E_MOD, E_NEW, E_EQ, E_NE, E_LT };
struct kxe {
	int32	k;
	const char *s;		/* 名前・数字・文字列・アクター定義の名前 */
	struct kxe *a, *b;
	const char *txt;	/* 誤りの報告に使う式の文字列 */
	int32	n;		/* 数の値／解決したあと: 状態の番号か局所変数の番号 */
	int32	isfield;	/* 解決したあと: 1＝アクターの状態、0＝局所変数 */
};
struct kxl { struct kxe *e; struct kxl *next; };	/* 式の並び（書いた順） */

/* 文 */
enum { S_DISP, S_SEND, S_ZENIN, S_CHG, S_ADD, S_PUSH, S_TAKE, S_IF, S_LOOP };
struct kxs {
	int32	k, line;
	struct kxl *l;		/* 表示する値／送り先／代入の行き先／追加する値 */
	struct kxe *a, *b;	/* S_SEND: a＝添え物  S_ZENIN: a＝配列 b＝添え物  S_CHG/S_ADD: a＝値  S_PUSH: a＝配列
				   S_TAKE: a＝行き先 b＝配列  S_IF: a＝条件  S_LOOP: a,b＝範囲 */
	const char *msg;
	struct kxs *body, *els;
	struct kxs *next;
	int32	depth;		/* S_LOOP: 入れ子の深さ（解決したあと） */
};

/* 定義の中身（初期値・受信節の頭＋文・続きの文） */
struct kxitem { int32 kind; const char *h; const char *field; struct kxe *val; struct kxs *st; int32 line, last; struct kxitem *next; };
struct kxname { const char *s; struct kxname *next; };
struct kxhand { const char *msg, *param; struct kxs *body; int32 line, end, nslot; const char **slots; };
struct kxdef {
	const char *name;
	int32	nf;
	const char **fields;
	int32	ninit;
	const char **initf;
	struct kxe **initv;
	int32	nh;
	struct kxhand *h;
	int32	line, end;
	struct kxdef *next;
	struct kclass *kc;	/* できた実行時のアクター定義 */
};
struct kxprog { struct kxdef *defs; struct kxs *main; int32 mline, mend; };
extern struct kxprog kx_prog;	/* 解析の結果（kxc.y が書く） */

/* 構文木を作る（kxc.y から呼ぶ） */
void	*kx_alloc(uint32 n);
struct kxe *kx_e(int32 k, const char *s);
struct kxe *kx_e2(int32 k, struct kxe *a, struct kxe *b, const char *op);
struct kxl *kx_list(struct kxe *e, struct kxl *prev);
struct kxs *kx_st(int32 k, struct kxl *l, struct kxe *a, struct kxe *b, const char *msg, int32 line);
struct kxs *kx_stappend(struct kxs *a, struct kxs *b);
struct kxs *kx_if(struct kxe *cond, struct kxs *then, struct kxs *els, int32 line);
struct kxs *kx_loop(struct kxe *lo, struct kxe *hi, struct kxs *body, int32 line);
struct kxs *kx_bind(struct kxe *maker, const char *name, int32 line);
struct kxname *kx_name(const char *s, struct kxname *prev);
struct kxitem *kx_item(int32 kind, const char *h, struct kxs *st, int32 line, int32 last);
struct kxitem *kx_inits(struct kxl *names, struct kxe *v, int32 line);
struct kxitem *kx_itemappend(struct kxitem *a, struct kxitem *b);
const char *kx_header(const char *msgtok, const char *param);
struct kxdef *kx_def(const char *name, struct kxname *decl, struct kxitem *items, const char *endname, int32 line, int32 end);
struct kxdef *kx_defappend(struct kxdef *a, struct kxdef *b);
void	kx_semerr(int32 line, const char *a, const char *b, const char *c);

/* 字句（kxlex.c） */
int32	kx_lex_start(const char *src, int32 len);	/* 字句に切る。OK／SYSERR（kx_errmsg に説明） */
void	kx_lex_end(void);				/* 字句の表を返す */

/* コンパイル（kxcomp.c）。src は文章形式。名前はブラウザの一覧に出す名前。
   できたら kprograms の一覧へ入れて（同じ名前があれば置き換えて）その番号を返す。だめなら SYSERR */
int32	kx_compile(const char *name, const char *src, int32 len);
extern char kx_errmsg[200];	/* 最後の誤り（「12行: …」） */
extern char kx_errtext[200];	/* 同じもので行番号の無いもの */
extern int32 kx_errline;
extern struct kprogram *kprogs[];
extern int32 nkprogs;
#define KPROGS_MAX	32

/* ファイルとのつなぎ（kxfiles.c） */
#define KX_MAXINC	4
int32	kx_save_kernel(char *log, int32 logn);			/* 書いたファイルの数か SYSERR */
int32	kx_compile_file(const char *name, char *err, int32 errn);	/* プログラムの番号か SYSERR */
#endif
