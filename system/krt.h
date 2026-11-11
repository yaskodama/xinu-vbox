/* krt.h - ことのは実行時ライブラリ（PC Xinu 用）
 *
 * アクター1つ = Xinu のプロセス1つ。受信箱は連結リスト＋計数セマフォ。
 * 受信節の実行は大域の錠（klock）の中で行うので、一つの受信節は途中で他のアクターに割り込まれない
 * （ブラウザ版の実行系と同じ「一通ずつ処理する」意味）。どのアクターが次に動くかは Xinu のスケジューラが決める。
 *
 * デバッガ: 生成コードは各文の前に kstep() を呼ぶ。停止点・1文実行・一時停止のときは、そこで
 * 錠を持ったまま止まる（＝プログラム全体が止まり、どのアクターの状態も動かない）。
 */
#ifndef KRT_H
#define KRT_H
/* xinu.h には二重読み込みの防ぎが無いので、ここでは読まない（使う側が先に読む） */

enum { KN_UNSET, KN_NONE, KN_NUM, KN_BOOL, KN_STR, KN_ARR, KN_ACT };

struct karr;
struct kact;
typedef struct {
	int32	t;
	union { int32 n; const char *s; struct karr *a; struct kact *o; } u;
} kv;

struct karr { int32 len, cap; kv *e; };

struct kmsg {
	const char *msg;
	kv	arg;
	int32	hasarg;
	struct kmsg *next;
};

typedef void (*khandler)(struct kact *self, kv arg);
struct khent { const char *msg; khandler fn; };

struct kclass {
	const char	*name;
	int32		nf;
	const char	**fields;
	void		(*init)(struct kact *);
	int32		nh;
	const struct khent *h;
	int32		count;
};

/* アクターの様子（デバッガの表示用） */
enum { KA_IDLE, KA_RUN, KA_STOP, KA_DEAD };

struct kact {
	struct kclass	*c;
	int32		id;
	kv		*f;
	struct kmsg	*head, *tail;
	sid32		msem;
	pid32		pid;
	int32		st;		/* KA_*			*/
	const char	*cur;		/* 処理中のメッセージ名	*/
};

struct kprogram;
/* 関数（受信節または実行部）一つ分の情報 */
struct kfun {
	struct kprogram	*prog;
	int32		cls;		/* -1 は実行部		*/
	const char	*msg;
	int32		line, end;	/* 構造化形式での行の範囲 */
	int32		nslot;
	const char	**slots;	/* 局所変数の名前	*/
};
/* プログラム一本分（k2xinu.mjs が生成） */
struct kprogram {
	const char	*name;
	int32		ncls;
	struct kclass	**cls;
	const int32	*cline, *cend;	/* 各アクター定義の行の範囲 */
	void		(*body)(void);
	int32		mline, mend;	/* 実行部の行の範囲	*/
	int32		nlines;
	const char	**lines;	/* 構造化形式（番号＝添字+1） */
	const unsigned char *stmt;	/* その行に文があるか	*/
	unsigned char	*bp;		/* 停止点		*/
	int32		nsrc;
	const char	**src;		/* 元の文章形式		*/
	int32		nfun;
	struct kfun	*funs;
};

/* 値を作る */
kv	kn(int32 n);
kv	kb(int32 b);
kv	knone(void);
kv	ks(const char *s);
kv	knewarr(void);
kv	kactv(struct kact *a);

/* 演算（where は誤りの報告に使う式の文字列） */
kv	kadd(kv a, kv b, const char *where);
kv	ksub(kv a, kv b, const char *where);
kv	kmod(kv a, kv b, const char *where);
kv	klen(kv a, const char *where);
kv	kget(kv base, kv idx, const char *where);
void	kset(kv base, kv idx, kv v, const char *where);
kv	*kfield(kv obj, const char *name, const char *where);
kv	kread(kv v, const char *where);
int32	keq(kv a, kv b);
int32	klt(kv a, kv b, const char *wa, const char *wb);
int32	knum(kv v, const char *where);
void	kpush(kv arr, kv v, const char *where);
kv	kshift(kv arr, const char *where);
kv	knew(struct kclass *c);
void	ksend(kv target, const char *msg, kv arg, int32 hasarg);
void	ksendall(kv arr, const char *msg, kv arg, int32 hasarg, const char *where);
void	kdisp(int32 n, const int32 *lit, const kv *vals);
void	kerror(const char *what, const char *where);
void	kstep(struct kfun *f, int32 line, struct kact *self, kv *L);

/* ───── デバッガとのやりとり ───── */
enum { KR_IDLE, KR_RUN, KR_PAUSED, KR_DONE, KR_ERROR };
enum { KM_RUN, KM_STEP };		/* 走らせ方: そのまま／次の文で止まる */

#define KMAXACT	64
struct kdbg {
	struct kprogram	*prog;		/* 走っている（走った）プログラム */
	int32		state;		/* KR_*				*/
	int32		mode;		/* KM_*				*/
	int32		trace;		/* 送信を記録するか		*/
	int32		nact;
	struct kact	*act[KMAXACT];	/* 生成された順			*/
	/* 止まっている所 */
	struct kfun	*pf;
	int32		pline;
	struct kact	*pself;
	kv		*pL;
	int32		nmsgs;		/* 処理したメッセージの数	*/
	int32		gen;		/* 表示を描き直す合図（変わるたびに増える） */
};
extern struct kdbg kd;

void	kd_run(struct kprogram *p);	/* 走らせる（前の実行は片付ける） */
void	kd_continue(void);
void	kd_step(void);
void	kd_pause(void);
void	kd_abort(void);

/* 出力の記録（トランスクリプト） */
#define KT_LINES	400
#define KT_WIDTH	160
extern char	kt_buf[KT_LINES][KT_WIDTH];
extern unsigned char kt_kind[KT_LINES];	/* 0=出力 1=送信の記録 2=誤り 3=案内 */
extern int32	kt_count;		/* これまでに書いた行数（KT_LINES を超えたら古い行から消える） */
void	kt_line(int32 kind, const char *s);

/* 値を文字列にする（runtime.js の show と同じ書き方）。書いた長さを返す */
int32	kshowbuf(char *buf, int32 n, kv v);

#endif
