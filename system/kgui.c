/* kgui.c - ことのはの開発環境（Xinu の上のウィンドウ群）
 *
 *   ブラウザ     … Smalltalk のシステムブラウザに倣う。プログラム｜アクター定義｜受信節 の3欄と、下にソース。
 *                   行番号の左をクリックすると停止点（●）を置く/外す。止まっている行は黄色。
 *   実行         … 実行・一時停止・1文・続ける・中止。送信の記録、最初の文で止める。
 *   アクター     … 生成されたアクターと、その様子（待ち／処理中／停止中）と受信箱の数。
 *   インスペクタ … 選んだアクターの状態（変数と値）と受信箱の中身。
 *   デバッガ     … 止まっている所（どのアクターがどのメッセージの何行目か）と局所変数。
 *   トランスクリプト … プログラムの出力、送信の記録、誤り。
 */
#include <xinu.h>
#include "krt.h"
#include "gfx.h"
#include "input.h"
#include "wm.h"
#include "kxsrc.h"
#include "kxc.h"
#include "kfs.h"

extern struct kprogram *kprogs[];
extern int32 nkprogs;
extern int strcmp(const char *, const char *);
extern int strncmp(const char *, const char *, int);

static struct win w_br, w_ctl, w_act, w_ins, w_dbg, w_tr, w_fs;

/* ───── 小道具 ───── */
static int32 scat(char *b, int32 p, int32 n, const char *s)
{
	while (*s && p < n - 1) b[p++] = *s++;
	b[p] = '\0';
	return p;
}
static int32 snum(char *b, int32 p, int32 n, int32 v)
{
	char t[16];
	int32 i = 15;
	uint32 u = v < 0 ? (uint32)(-v) : (uint32)v;
	t[i] = '\0';
	do { t[--i] = '0' + u % 10; u /= 10; } while (u);
	if (v < 0) t[--i] = '-';
	return scat(b, p, n, &t[i]);
}
static int32 sval(char *b, int32 p, int32 n, kv v)
{
	char t[200];
	kshowbuf(t, sizeof(t), v);
	return scat(b, p, n, t);
}
static const char *stname(int32 st)
{
	switch (st) {
	case KA_RUN:  return "処理中";
	case KA_STOP: return "停止中";
	case KA_DEAD: return "終了";
	default:      return "待ち";
	}
}
static int32 mailcount(struct kact *a)
{
	int32 n = 0;
	struct kmsg *m;
	for (m = a->head; m && n < 999; m = m->next) n++;
	return n;
}

/* ───── ブラウザ ───── */
static struct lst l_prog, l_cls, l_h;
static int32 code_mode;		/* 0=構造化形式 1=文章形式 */
static int32 code_from, code_to, code_top;
static int32 follow_pause = 1;
static int32 br_tab;		/* 0=ことのは 1=Xinu のソース */

static struct kprogram *cur_prog(void) { return nkprogs ? kprogs[l_prog.sel < 0 ? 0 : l_prog.sel] : NULL; }

static uint32 it_prog(struct lst *l, int32 i, char *b, int32 n) { scat(b, 0, n, kprogs[i]->name); return C_TEXT; }
static uint32 it_cls(struct lst *l, int32 i, char *b, int32 n)
{
	struct kprogram *p = cur_prog();
	if (i < p->ncls) scat(b, 0, n, p->cls[i]->name);
	else scat(b, 0, n, "実行部");
	return i < p->ncls ? C_TEXT : C_BLUE;
}
static uint32 it_h(struct lst *l, int32 i, char *b, int32 n)
{
	struct kprogram *p = cur_prog();
	int32 q;
	if (l_cls.sel >= p->ncls) { scat(b, 0, n, "実行を始める"); return C_BLUE; }
	if (i == 0) { scat(b, 0, n, "（定義全体）"); return C_DIM; }
	q = scat(b, 0, n, "「");
	q = scat(b, q, n, p->cls[l_cls.sel]->h[i - 1].msg);
	scat(b, q, n, "」");
	return C_TEXT;
}

/* 選んだ欄に応じてソースの範囲を決める */
static void set_range(void)
{
	struct kprogram *p = cur_prog();
	int32 i;
	if (!p) return;
	l_cls.n = p->ncls + 1;
	if (l_cls.sel >= l_cls.n) l_cls.sel = 0;
	if (l_cls.sel >= p->ncls) {
		l_h.n = 1; if (l_h.sel < 0 || l_h.sel >= 1) l_h.sel = 0;
		code_from = p->mline; code_to = p->mend;
	} else {
		struct kclass *c = p->cls[l_cls.sel];
		l_h.n = c->nh + 1;
		if (l_h.sel < 0 || l_h.sel >= l_h.n) l_h.sel = 0;
		code_from = p->cline[l_cls.sel]; code_to = p->cend[l_cls.sel];
		if (l_h.sel > 0) {
			const char *msg = c->h[l_h.sel - 1].msg;
			for (i = 0; i < p->nfun; i++) {
				if (p->funs[i].cls == l_cls.sel && strcmp(p->funs[i].msg, msg) == 0) {
					code_from = p->funs[i].line; code_to = p->funs[i].end;
				}
			}
		}
	}
	code_top = 0;
}

/* 止まった所へブラウザを合わせる */
static void goto_pause(void)
{
	struct kfun *f = kd.pf;
	int32 i;
	if (!f) return;
	br_tab = 0;
	for (i = 0; i < nkprogs; i++) if (kprogs[i] == f->prog) l_prog.sel = i;
	code_mode = 0;
	if (f->cls < 0) { l_cls.sel = f->prog->ncls; l_h.sel = 0; }
	else {
		struct kclass *c = f->prog->cls[f->cls];
		l_cls.sel = f->cls;
		for (i = 0; i < c->nh; i++) if (strcmp(c->h[i].msg, f->msg) == 0) l_h.sel = i + 1;
	}
	set_range();
}


/* 寸法はすべて文字の大きさ ui（1 か 2）に比例させる（U(n) = n*ui） */
#define BR_TOOL	U(28)
static void br_layout(int32 cw, int32 ch, int32 *ph, int32 *pw)
{
	*ph = ch / 3; if (*ph < U(156)) *ph = U(156);
	if (*ph > ch / 2) *ph = ch / 2;
	*pw = cw / 3;
}
/* 形式の切り替えボタンの位置 */
static int32 br_btnw(void) { return gfx_textw("■構造化形式") + U(16); }

static void kb_draw(struct win *w, int32 cw, int32 ch)
{
	int32 ph, pw, y, i, ln, rows, codey, codeh, from, to, bw, numw;
	struct kprogram *p = cur_prog();
	char b[40];
	br_layout(cw, ch, &ph, &pw);
	gfx_fill(0, 0, cw, ch, 0xF4F5F7);
	if (!p) { gfx_text(U(10), U(10), "プログラムが組み込まれていません", C_TEXT); return; }
	l_prog.n = nkprogs;
	lst_draw(&l_prog, U(4), U(4), pw - U(6), ph, 0);
	lst_draw(&l_cls, pw + U(1), U(4), pw - U(4), ph, 0);
	lst_draw(&l_h, 2 * pw + U(2), U(4), cw - 2 * pw - U(6), ph, 0);
	y = ph + U(8);
	bw = br_btnw();
	btn_draw(U(4), y, bw, U(24), code_mode == 0 ? "■構造化形式" : "□構造化形式", 1);
	btn_draw(U(8) + bw, y, bw, U(24), code_mode == 1 ? "■文章形式" : "□文章形式", 1);
	gfx_textn(U(16) + 2 * bw, y + U(4), code_mode == 0 ? "行番号の左をクリック＝停止点 ●" : "（文章形式は読むだけ）",
		  cw - U(20) - 2 * bw, C_DIM);
	codey = y + BR_TOOL; codeh = ch - codey - U(4);
	box_draw(U(4), codey, cw - U(8), codeh);
	rows = (codeh - U(4)) / ROW_H;
	if (code_mode == 0) { from = code_from; to = code_to; }
	else { from = 1; to = p->nsrc; }
	if (code_top > to - from + 1 - rows) code_top = to - from + 1 - rows;
	if (code_top < 0) code_top = 0;
	numw = U(70);
	wm_clip(U(5), codey + 1, cw - U(10), codeh - 2);
	for (i = 0, ln = from + code_top; ln <= to && i < rows; i++, ln++) {
		int32 yy = codey + U(2) + i * ROW_H;
		const char *text = code_mode == 0 ? (ln >= 1 && ln <= p->nlines ? p->lines[ln - 1] : "")
						  : p->src[ln - 1];
		int32 paused = code_mode == 0 && kd.state == KR_PAUSED && kd.pf && kd.pf->prog == p && kd.pline == ln;
		if (paused) gfx_fill(U(5), yy, cw - U(10), ROW_H, C_HILITE);
		if (code_mode == 0) {
			if (p->bp[ln]) gfx_text(U(6), yy + U(1), "●", C_RED);
			else if (p->stmt[ln]) gfx_fill(U(12), yy + U(8), U(3), U(3), 0xB0B0B0);
			if (paused) gfx_text(U(22), yy + U(1), "→", C_RED);
		}
		snum(b, 0, sizeof(b), ln);
		gfx_text(numw - U(4) - gfx_textw(b), yy + U(1), b, C_DIM);
		gfx_textn(numw + U(4), yy + U(1), text, cw - numw - U(14), paused ? C_TEXT : 0x202020);
	}
	wm_unclip();
}

static void kb_mouse(struct win *w, int32 ev, int32 mx, int32 my, int32 cw, int32 ch)
{
	int32 ph, pw, i, y, codey, bw;
	struct kprogram *p = cur_prog();
	if (ev != WM_DOWN || !p) return;
	br_layout(cw, ch, &ph, &pw);
	if ((i = lst_hit(&l_prog, U(4), U(4), pw - U(6), ph, mx, my)) >= 0) { l_prog.sel = i; l_cls.sel = 0; l_h.sel = 0; set_range(); return; }
	if ((i = lst_hit(&l_cls, pw + U(1), U(4), pw - U(4), ph, mx, my)) >= 0) { l_cls.sel = i; l_h.sel = 0; set_range(); code_mode = 0; return; }
	if ((i = lst_hit(&l_h, 2 * pw + U(2), U(4), cw - 2 * pw - U(6), ph, mx, my)) >= 0) { l_h.sel = i; set_range(); code_mode = 0; return; }
	y = ph + U(8);
	bw = br_btnw();
	if (in_rect(mx, my, U(4), y, bw, U(24))) { code_mode = 0; code_top = 0; return; }
	if (in_rect(mx, my, U(8) + bw, y, bw, U(24))) { code_mode = 1; code_top = 0; return; }
	codey = y + BR_TOOL;
	if (code_mode == 0 && my >= codey + U(2) && mx < U(70)) {
		int32 ln = code_from + code_top + (my - codey - U(2)) / ROW_H;
		if (ln <= code_to && p->stmt[ln]) p->bp[ln] = !p->bp[ln];
	}
}

static void kb_wheel(struct win *w, int32 mx, int32 my, int32 dz, int32 cw, int32 ch)
{
	int32 ph, pw;
	br_layout(cw, ch, &ph, &pw);
	if (my < ph + U(4)) {
		if (mx < pw) lst_scroll(&l_prog, ph, dz);
		else if (mx < 2 * pw) lst_scroll(&l_cls, ph, dz);
		else lst_scroll(&l_h, ph, dz);
	} else {
		code_top += dz * 3;
		if (code_top < 0) code_top = 0;
	}
}


/* ───── ブラウザの「Xinu ソース」タブ ─────
 * ［ことのは版］ことのはで書き直した Xinu（kxinu/）。グループ｜対応する C のファイル｜受信節
 * ［C の原文］  このカーネル自身の C のソース。ディレクトリ｜ファイル｜関数
 * どちらも kxsrc.c に埋め込み（gen_xsrc.py） */
static int32 xs_mode;			/* 0=ことのは版 1=C の原文 */
static struct lst l_xd, l_xf, l_xn;	/* C の原文 */
static struct lst l_kd, l_kf, l_kn;	/* ことのは版 */
static int32 xf_list[400], xf_n;	/* 選んだディレクトリのファイル（xfiles の番号） */
static int32 kf_list[64], kf_n;		/* 選んだグループのファイル（kxfiles の番号） */
static int32 xs_top, xs_hl0, xs_hl1;	/* C: 表示の先頭行（0 から）と、色を付ける関数の行範囲 */
static int32 ks_top;			/* ことのは版の表示の先頭行 */
static void do_button(int32 i);
static void set_range(void);

static const struct xfile *xs_file(void) { return (l_xf.sel >= 0 && l_xf.sel < xf_n) ? &xfiles[xf_list[l_xf.sel]] : NULL; }
static const struct kxfile *ks_file(void) { return (l_kf.sel >= 0 && l_kf.sel < kf_n) ? &kxfiles[kf_list[l_kf.sel]] : NULL; }
static uint32 it_xd(struct lst *l, int32 i, char *b, int32 n) { int32 q = scat(b, 0, n, xdirs[i]); scat(b, q, n, "/"); return C_TEXT; }
static uint32 it_xf(struct lst *l, int32 i, char *b, int32 n)
{
	const struct xfile *f = &xfiles[xf_list[i]];
	scat(b, 0, n, f->name);
	return f->nfn ? C_TEXT : C_DIM;
}
static uint32 it_xn(struct lst *l, int32 i, char *b, int32 n)
{
	const struct xfile *f = xs_file();
	if (i == 0) { scat(b, 0, n, "（ファイル全体）"); return C_DIM; }
	scat(b, 0, n, f->fns[i - 1].name);
	return C_BLUE;
}
static uint32 it_kd(struct lst *l, int32 i, char *b, int32 n) { scat(b, 0, n, kxgrps[i].name); return C_TEXT; }
static uint32 it_kf(struct lst *l, int32 i, char *b, int32 n) { scat(b, 0, n, kxfiles[kf_list[i]].path); return C_TEXT; }
static uint32 it_kn(struct lst *l, int32 i, char *b, int32 n)
{
	const struct kxfile *f = ks_file();
	if (i == 0) { scat(b, 0, n, "（ファイル全体）"); return C_DIM; }
	scat(b, 0, n, f->fns[i - 1].name);
	return C_BLUE;
}
static void xs_pickdir(int32 d)
{
	int32 i;
	l_xd.sel = d; xf_n = 0;
	for (i = 0; i < nxfiles && xf_n < 400; i++) if (xfiles[i].dir == d) xf_list[xf_n++] = i;
	l_xf.n = xf_n; l_xf.sel = 0; l_xf.top = 0;
}
static void xs_pickfile(int32 i)
{
	const struct xfile *f;
	l_xf.sel = i;
	f = xs_file();
	l_xn.n = f ? f->nfn + 1 : 0; l_xn.sel = 0; l_xn.top = 0;
	xs_top = 0; xs_hl0 = xs_hl1 = 0;
}
static void xs_pickfn(int32 i)
{
	const struct xfile *f = xs_file();
	l_xn.sel = i;
	if (!f || i == 0) { xs_top = 0; xs_hl0 = xs_hl1 = 0; return; }
	xs_hl0 = f->fns[i - 1].line; xs_hl1 = f->fns[i - 1].end;
	xs_top = xs_hl0 > 4 ? xs_hl0 - 4 : 0;		/* 関数の頭の少し上から見せる */
}
static void ks_pickfn(int32 i)
{
	const struct kxfile *f = ks_file();
	int32 at;
	l_kn.sel = i;
	if (!f) return;
	at = i == 0 ? f->sec[0][0] : f->fns[i - 1].line;
	ks_top = at > 3 ? at - 3 : 0;
}
static void ks_pickfile(int32 i) { const struct kxfile *f; l_kf.sel = i; f = ks_file(); l_kn.n = f ? f->nfn + 1 : 0; l_kn.top = 0; ks_pickfn(0); }
static void ks_pickgrp(int32 g)
{
	int32 i;
	l_kd.sel = g; kf_n = 0;
	for (i = 0; i < nkxfiles && kf_n < 64; i++) if (kxfiles[i].grp == g) kf_list[kf_n++] = i;
	l_kf.n = kf_n; l_kf.top = 0;
	ks_pickfile(0);
}
/* ことのは版で選んでいるファイル・関数を、C の原文の同じ場所へ */
static void ks_to_c(void)
{
	const struct kxfile *f = ks_file();
	int32 i, j;
	if (!f) return;
	for (i = 0; i < nxfiles; i++) {
		const struct xfile *x = &xfiles[i];
		const char *d = xdirs[x->dir];
		int32 dl = 0;
		while (d[dl]) dl++;
		if (strncmp(f->path, d, dl) != 0 || f->path[dl] != '/' || strcmp(f->path + dl + 1, x->name) != 0) continue;
		xs_pickdir(x->dir);
		for (j = 0; j < xf_n; j++) if (xf_list[j] == i) { xs_pickfile(j); lst_show(&l_xf, U(156), j); }
		if (l_kn.sel > 0)
			for (j = 0; j < x->nfn; j++) if (strcmp(x->fns[j].name, f->fns[l_kn.sel - 1].name) == 0) xs_pickfn(j + 1);
		return;
	}
}
/* ことのは版の Xinu を、ことのはのタブで走らせる */
static void ks_run(void)
{
	int32 i;
	const char *pn = kxgrps[l_kd.sel < 0 ? 0 : l_kd.sel].prog;
	for (i = 0; i < nkprogs; i++) {
		if (strcmp(kprogs[i]->name, pn) == 0) {
			br_tab = 0; l_prog.sel = i; l_cls.sel = 0; l_h.sel = 0; code_mode = 0; set_range();
			do_button(0);
			return;
		}
	}
}
/* 再起動: キーボード制御器にリセットを頼む（QEMU は -kernel を読み直して Xinu が最初から立ち上がる） */
static void xinu_reboot(void)
{
	int32 i;
	kprintf("\n*** ブラウザから再起動（ブート）します ***\n");
	disable();
	for (i = 0; i < 100000 && (inb(0x64) & 2); i++) ;
	outb(0x64, 0xFE);
	for (;;) ;
}
static int32 xs_bootw(void) { return gfx_textw("Xinu を再起動（ブート）") + U(20); }
static int32 xs_modew(void) { return gfx_textw("■ことのは版") + U(16); }
static int32 xs_runw(void) { return gfx_textw("この Xinu を実行") + U(20); }

static void xs_draw(struct win *w, int32 cw, int32 ch)
{
	int32 ph, pw, y, i, ln, rows, codey, codeh, numw, bw, mw, x, nl, top;
	const char *const *lines;
	char b[96];
	struct lst *LD = xs_mode ? &l_xd : &l_kd, *LF = xs_mode ? &l_xf : &l_kf, *LN = xs_mode ? &l_xn : &l_kn;
	const struct xfile *xf = xs_file();
	const struct kxfile *kf = ks_file();
	br_layout(cw, ch, &ph, &pw);
	gfx_fill(0, 0, cw, ch, 0xF4F5F7);
	l_xd.n = nxdirs; l_kd.n = nkxgrps;
	l_kd.head = "ことのは版"; l_kf.head = "C のファイル"; l_kn.head = "受信節";
	lst_draw(LD, U(4), U(4), pw - U(6), ph, 0);
	lst_draw(LF, pw + U(1), U(4), pw - U(4), ph, 0);
	lst_draw(LN, 2 * pw + U(2), U(4), cw - 2 * pw - U(6), ph, 0);
	y = ph + U(8);
	mw = xs_modew(); bw = xs_bootw();
	btn_draw(U(4), y, mw, U(24), xs_mode == 0 ? "■ことのは版" : "□ことのは版", 1);
	btn_draw(U(8) + mw, y, mw, U(24), xs_mode == 1 ? "■C の原文" : "□C の原文", 1);
	x = U(14) + 2 * mw;
	if (xs_mode == 0) { btn_draw(x, y, xs_runw(), U(24), "この Xinu を実行", kd.state != KR_RUN); x += xs_runw() + U(8); }
	btn_draw(cw - U(4) - bw, y, bw, U(24), "Xinu を再起動（ブート）", 1);
	b[0] = 0;
	if (xs_mode == 1 && xf) {
		int32 q = scat(b, 0, sizeof(b), xdirs[xf->dir]);
		q = scat(b, q, sizeof(b), "/"); q = scat(b, q, sizeof(b), xf->name);
		q = scat(b, q, sizeof(b), "  "); q = snum(b, q, sizeof(b), xf->nlines); scat(b, q, sizeof(b), " 行");
	} else if (xs_mode == 0 && kf) {
		int32 q = scat(b, 0, sizeof(b), "← ");
		scat(b, q, sizeof(b), kf->path);
	}
	gfx_textn(x, y + U(4), b, cw - bw - x - U(10), C_DIM);
	codey = ph + U(8) + BR_TOOL; codeh = ch - codey - U(4);
	box_draw(U(4), codey, cw - U(8), codeh);
	rows = (codeh - U(4)) / ROW_H;
	if (xs_mode == 1) { if (!xf) return; lines = xf->lines; nl = xf->nlines; }
	else { const struct kxgrp *g = &kxgrps[l_kd.sel < 0 ? 0 : l_kd.sel]; lines = g->lines; nl = g->nlines; }
	{
		int32 *tp = xs_mode ? &xs_top : &ks_top;
		if (*tp > nl - rows) *tp = nl - rows;
		if (*tp < 0) *tp = 0;
		top = *tp;
	}
	numw = gfx_textw("00000") + U(8);
	wm_clip(U(5), codey + 1, cw - U(10), codeh - 2);
	for (i = 0, ln = top + 1; ln <= nl && i < rows; i++, ln++) {
		int32 yy = codey + U(2) + i * ROW_H, in = 0, k;
		const char *t = lines[ln - 1];
		uint32 col = 0x202020;
		if (xs_mode == 1) in = xs_hl0 > 0 && ln >= xs_hl0 && ln <= xs_hl1;
		else if (kf) {
			if (l_kn.sel > 0) in = ln >= kf->fns[l_kn.sel - 1].line && ln <= kf->fns[l_kn.sel - 1].end;
			else for (k = 0; k < kf->nsec; k++) if (ln >= kf->sec[k][0] && ln <= kf->sec[k][1]) in = 1;
		}
		if (xs_mode == 0) {
			const char *u = t;
			while (*u == ' ') u++;
			if (u[0] == (char)0xE2 && u[1] == (char)0x80 && u[2] == (char)0xBB) col = C_GREEN;	/* ※ 注釈 */
			else if (u[0] == (char)0xE2 && u[1] == (char)0x96 && u[2] == (char)0xA0) col = C_BLUE;	/* ■ 見出し */
		}
		if (in) gfx_fill(U(5), yy, cw - U(10), ROW_H, C_HILITE);
		snum(b, 0, sizeof(b), ln);
		gfx_text(numw - U(4) - gfx_textw(b), yy + U(1), b, C_DIM);
		gfx_textn(numw + U(4), yy + U(1), t, cw - numw - U(14), col);
	}
	wm_unclip();
}
static void xs_mouse(struct win *w, int32 ev, int32 mx, int32 my, int32 cw, int32 ch)
{
	int32 ph, pw, i, bw, mw, y;
	if (ev != WM_DOWN) return;
	br_layout(cw, ch, &ph, &pw);
	if (xs_mode == 1) {
		if ((i = lst_hit(&l_xd, U(4), U(4), pw - U(6), ph, mx, my)) >= 0) { xs_pickdir(i); xs_pickfile(0); return; }
		if ((i = lst_hit(&l_xf, pw + U(1), U(4), pw - U(4), ph, mx, my)) >= 0) { xs_pickfile(i); return; }
		if ((i = lst_hit(&l_xn, 2 * pw + U(2), U(4), cw - 2 * pw - U(6), ph, mx, my)) >= 0) { xs_pickfn(i); return; }
	} else {
		if ((i = lst_hit(&l_kd, U(4), U(4), pw - U(6), ph, mx, my)) >= 0) { ks_pickgrp(i); return; }
		if ((i = lst_hit(&l_kf, pw + U(1), U(4), pw - U(4), ph, mx, my)) >= 0) { ks_pickfile(i); return; }
		if ((i = lst_hit(&l_kn, 2 * pw + U(2), U(4), cw - 2 * pw - U(6), ph, mx, my)) >= 0) { ks_pickfn(i); return; }
	}
	y = ph + U(8); mw = xs_modew(); bw = xs_bootw();
	if (in_rect(mx, my, U(4), y, mw, U(24))) { xs_mode = 0; return; }
	if (in_rect(mx, my, U(8) + mw, y, mw, U(24))) { if (xs_mode == 0) ks_to_c(); xs_mode = 1; return; }
	if (xs_mode == 0 && in_rect(mx, my, U(14) + 2 * mw, y, xs_runw(), U(24)) && kd.state != KR_RUN) { ks_run(); return; }
	if (in_rect(mx, my, cw - U(4) - bw, y, bw, U(24))) xinu_reboot();
}
static void xs_wheel(struct win *w, int32 mx, int32 my, int32 dz, int32 cw, int32 ch)
{
	int32 ph, pw;
	br_layout(cw, ch, &ph, &pw);
	if (my < ph + U(4)) {
		if (mx < pw) lst_scroll(xs_mode ? &l_xd : &l_kd, ph, dz);
		else if (mx < 2 * pw) lst_scroll(xs_mode ? &l_xf : &l_kf, ph, dz);
		else lst_scroll(xs_mode ? &l_xn : &l_kn, ph, dz);
	} else {
		int32 *tp = xs_mode ? &xs_top : &ks_top;
		*tp += dz * 3;
		if (*tp < 0) *tp = 0;
	}
}

/* ───── ブラウザの窓: 上にタブ［ことのは］［Xinu ソース］、その下が選んだ方の中身 ───── */
#define TAB_H	U(26)
static const char *tab_label[2] = { "ことのは", "Xinu ソース" };
static int32 tab_w(int32 i) { return gfx_textw(tab_label[i]) + U(28); }
static void br_draw(struct win *w, int32 cw, int32 ch)
{
	int32 i, x = U(6);
	gfx_fill(0, 0, cw, TAB_H, 0xDDE1E6);
	gfx_fill(0, TAB_H - 1, cw, 1, C_LINE);
	for (i = 0; i < 2; i++) {
		int32 tw = tab_w(i), on = br_tab == i;
		gfx_fill(x, U(3), tw, TAB_H - U(3) - (on ? 0 : 1), on ? 0xF4F5F7 : 0xC9CED5);
		gfx_frame(x, U(3), tw, TAB_H - U(3) + (on ? 1 : 0), C_LINE);
		if (on) gfx_fill(x + 1, TAB_H - 1, tw - 2, 1, 0xF4F5F7);
		gfx_text(x + U(14), U(6), tab_label[i], on ? C_TEXT : C_DIM);
		x += tw + U(2);
	}
	/* 中身はタブの下を (0,0) として描く */
	wm_oy += TAB_H; wm_ch -= TAB_H;
	gfx_origin(wm_ox, wm_oy);
	wm_unclip();
	if (br_tab == 0) kb_draw(w, cw, ch - TAB_H); else xs_draw(w, cw, ch - TAB_H);
	wm_oy -= TAB_H; wm_ch += TAB_H;
	gfx_origin(wm_ox, wm_oy);
	wm_unclip();
}
static void br_mouse(struct win *w, int32 ev, int32 mx, int32 my, int32 cw, int32 ch)
{
	if (my < TAB_H) {
		int32 i, x = U(6);
		if (ev != WM_DOWN) return;
		for (i = 0; i < 2; i++) {
			if (mx >= x && mx < x + tab_w(i)) { br_tab = i; return; }
			x += tab_w(i) + U(2);
		}
		return;
	}
	if (br_tab == 0) kb_mouse(w, ev, mx, my - TAB_H, cw, ch - TAB_H);
	else xs_mouse(w, ev, mx, my - TAB_H, cw, ch - TAB_H);
}
static void br_wheel(struct win *w, int32 mx, int32 my, int32 dz, int32 cw, int32 ch)
{
	if (br_tab == 0) kb_wheel(w, mx, my - TAB_H, dz, cw, ch - TAB_H);
	else xs_wheel(w, mx, my - TAB_H, dz, cw, ch - TAB_H);
}

/* ───── 実行 ───── */
static int32 step_start;	/* 最初の文で止める */
static const char *cb_label[5] = { "実行", "一時停止", "1文", "続ける", "中止" };
static int32 cb_enabled(int32 i)
{
	switch (i) {
	case 0: return 1;
	case 1: return kd.state == KR_RUN;
	case 2: case 3: return kd.state == KR_PAUSED;
	default: return kd.state == KR_RUN || kd.state == KR_PAUSED;
	}
}
/* ボタンは文字の幅に合わせ、入りきらなければ次の段へ折り返す。*bottom に最後の段の下端を返す */
static void cb_rect(int32 i, int32 cw, int32 *x, int32 *y, int32 *w, int32 *bottom)
{
	int32 k, cx = U(4), cy = ROW_H + U(10), bw = 0;
	for (k = 0; k <= i || (bottom && k < 5); k++) {
		bw = gfx_textw(cb_label[k]) + U(20);
		if (cx + bw > cw - U(4) && cx > U(4)) { cx = U(4); cy += U(30); }
		if (k == i) { *x = cx; *y = cy; *w = bw; }
		cx += bw + U(4);
	}
	if (bottom) *bottom = cy + U(26);
}
static void do_button(int32 i)
{
	struct kprogram *p = cur_prog();
	if (!cb_enabled(i) || !p) return;
	switch (i) {
	case 0: kd.mode = step_start ? KM_STEP : KM_RUN; follow_pause = 1; kd_run(p); break;	/* アクターの窓はメニュー帯から開く */
	case 1: kd_pause(); break;
	case 2: kd_step(); break;
	case 3: kd_continue(); break;
	case 4: kd_abort(); break;
	}
}

static const char *state_text(void)
{
	switch (kd.state) {
	case KR_RUN:    return "実行中";
	case KR_PAUSED: return "停止中";
	case KR_DONE:   return "終わった";
	case KR_ERROR:  return "誤りで止まった";
	default:        return "待機";
	}
}

static void ctl_draw(struct win *w, int32 cw, int32 ch)
{
	char b[160];
	int32 i, x, y, bw, q, bot;
	struct kprogram *p = cur_prog();
	gfx_fill(0, 0, cw, ch, 0xF4F5F7);
	q = scat(b, 0, sizeof(b), "プログラム: ");
	scat(b, q, sizeof(b), p ? p->name : "（なし）");
	gfx_textn(U(6), U(6), b, cw - U(12), C_TEXT);
	for (i = 0; i < 5; i++) { cb_rect(i, cw, &x, &y, &bw, NULL); btn_draw(x, y, bw, U(26), cb_label[i], cb_enabled(i)); }
	cb_rect(0, cw, &x, &y, &bw, &bot);
	y = bot + U(6);
	gfx_text(U(6), y, kd.trace ? "■ 送信を記録" : "□ 送信を記録", C_TEXT);
	y += ROW_H + U(2);
	gfx_text(U(6), y, step_start ? "■ 最初の文で止める" : "□ 最初の文で止める", C_TEXT);
	y += ROW_H + U(6);
	q = scat(b, 0, sizeof(b), "状態: ");
	q = scat(b, q, sizeof(b), state_text());
	gfx_textn(U(6), y, b, cw - U(12), kd.state == KR_ERROR ? C_RED : kd.state == KR_PAUSED ? 0xB06000 : C_TEXT);
	y += ROW_H + U(2);
	q = scat(b, 0, sizeof(b), "メッセージ ");
	q = snum(b, q, sizeof(b), kd.nmsgs);
	q = scat(b, q, sizeof(b), " 通　アクター ");
	q = snum(b, q, sizeof(b), kd.nact);
	q = scat(b, q, sizeof(b), " 体");
	gfx_textn(U(6), y, b, cw - U(12), C_TEXT);
	y += ROW_H + U(2);
	gfx_textn(U(6), y, "F5 実行/続ける F7 1文 F8 一時停止", cw - U(12), C_DIM);
}

static void ctl_mouse(struct win *w, int32 ev, int32 mx, int32 my, int32 cw, int32 ch)
{
	int32 i, x, y, bw, bot;
	if (ev != WM_DOWN) return;
	for (i = 0; i < 5; i++) { cb_rect(i, cw, &x, &y, &bw, NULL); if (in_rect(mx, my, x, y, bw, U(26))) { do_button(i); return; } }
	cb_rect(0, cw, &x, &y, &bw, &bot);
	y = bot + U(6);
	if (in_rect(mx, my, 0, y - U(2), cw, ROW_H)) kd.trace = !kd.trace;
	y += ROW_H + U(2);
	if (in_rect(mx, my, 0, y - U(2), cw, ROW_H)) step_start = !step_start;
}

/* ───── アクター ───── */
static struct lst l_act;
static uint32 it_act(struct lst *l, int32 i, char *b, int32 n)
{
	struct kact *a = kd.act[i];
	int32 q = sval(b, 0, n, kactv(a));
	q = scat(b, q, n, "　");
	q = scat(b, q, n, stname(a->st));
	if (a->st == KA_RUN || a->st == KA_STOP) {
		q = scat(b, q, n, "「");
		q = scat(b, q, n, a->cur ? a->cur : "");
		q = scat(b, q, n, "」");
	}
	q = scat(b, q, n, "　受信箱 ");
	snum(b, q, n, mailcount(a));
	return a->st == KA_STOP ? C_RED : a->st == KA_RUN ? C_GREEN : a->st == KA_DEAD ? C_DIM : C_TEXT;
}
static void act_draw(struct win *w, int32 cw, int32 ch)
{
	l_act.n = kd.nact;
	if (l_act.sel >= l_act.n) l_act.sel = l_act.n - 1;
	gfx_fill(0, 0, cw, ch, 0xF4F5F7);
	lst_draw(&l_act, U(4), U(4), cw - U(8), ch - U(8), 1);
	if (!kd.nact) gfx_textn(U(12), U(8), "（まだアクターはありません）", cw - U(16), C_DIM);
}
static void act_mouse(struct win *w, int32 ev, int32 mx, int32 my, int32 cw, int32 ch)
{
	int32 i;
	if (ev == WM_DOWN && (i = lst_hit(&l_act, U(4), U(4), cw - U(8), ch - U(8), mx, my)) >= 0) {
		l_act.sel = i;
		w_ins.shown = 1;
		wm_front(&w_ins);
		wm_front(&w_act);
	}
}
static void act_wheel(struct win *w, int32 mx, int32 my, int32 dz, int32 cw, int32 ch) { lst_scroll(&l_act, ch, dz); }

/* ───── インスペクタ ───── */
static struct lst l_ins;
static struct kact *ins_target(void) { return (l_act.sel >= 0 && l_act.sel < kd.nact) ? kd.act[l_act.sel] : NULL; }
static uint32 it_ins(struct lst *l, int32 i, char *b, int32 n)
{
	struct kact *a = ins_target();
	int32 q;
	if (!a) { b[0] = 0; return C_TEXT; }
	if (i < a->c->nf) {
		q = scat(b, 0, n, a->c->fields[i]);
		q = scat(b, q, n, " ＝ ");
		sval(b, q, n, a->f[i]);
		return C_TEXT;
	}
	if (i == a->c->nf) {
		q = scat(b, 0, n, "── 受信箱（");
		q = snum(b, q, n, mailcount(a));
		scat(b, q, n, " 通）");
		return C_DIM;
	}
	{
		struct kmsg *m = a->head;
		int32 k;
		for (k = a->c->nf + 1; m && k < i; k++) m = m->next;
		if (!m) { b[0] = 0; return C_TEXT; }
		q = scat(b, 0, n, "「");
		q = scat(b, q, n, m->msg);
		q = scat(b, q, n, "」");
		if (m->hasarg) { q = scat(b, q, n, " と "); sval(b, q, n, m->arg); }
		return C_BLUE;
	}
}

static void ins_draw(struct win *w, int32 cw, int32 ch)
{
	struct kact *a = ins_target();
	char b[96];
	int32 q;
	gfx_fill(0, 0, cw, ch, 0xF4F5F7);
	if (!a) { gfx_textn(U(8), U(8), "アクターの一覧で選んでください", cw - U(16), C_DIM); return; }
	q = sval(b, 0, sizeof(b), kactv(a));
	q = scat(b, q, sizeof(b), "（");
	q = scat(b, q, sizeof(b), stname(a->st));
	scat(b, q, sizeof(b), "）");
	gfx_textn(U(8), U(4), b, cw - U(16), C_TITLE_ON);
	l_ins.n = a->c->nf + 1 + mailcount(a);
	l_ins.sel = -1;
	lst_draw(&l_ins, U(4), ROW_H + U(6), cw - U(8), ch - ROW_H - U(10), 0);
}
static void ins_wheel(struct win *w, int32 mx, int32 my, int32 dz, int32 cw, int32 ch) { lst_scroll(&l_ins, ch, dz); }

/* ───── デバッガ ───── */
static struct lst l_loc;
static uint32 it_loc(struct lst *l, int32 i, char *b, int32 n)
{
	struct kfun *f = kd.pf;
	int32 q;
	if (!f || i >= f->nslot) { b[0] = 0; return C_TEXT; }
	q = scat(b, 0, n, f->slots[i]);
	q = scat(b, q, n, " ＝ ");
	sval(b, q, n, kd.pL[i]);
	return kd.pL[i].t == KN_UNSET ? C_DIM : C_TEXT;
}

static void dbg_draw(struct win *w, int32 cw, int32 ch)
{
	char b[200];
	int32 q, x, bw, y;
	struct kfun *f = kd.pf;
	gfx_fill(0, 0, cw, ch, 0xF4F5F7);
	if (kd.state != KR_PAUSED || !f) {
		gfx_textn(U(8), U(8), "止まっていません。", cw - U(16), C_DIM);
		gfx_textn(U(8), U(8) + ROW_H, "ブラウザで停止点を置くか、", cw - U(16), C_DIM);
		gfx_textn(U(8), U(8) + 2 * ROW_H, "［一時停止］を押す。", cw - U(16), C_DIM);
		return;
	}
	if (kd.pself) { q = sval(b, 0, sizeof(b), kactv(kd.pself)); q = scat(b, q, sizeof(b), " が「"); q = scat(b, q, sizeof(b), f->msg); q = scat(b, q, sizeof(b), "」を処理中"); }
	else q = scat(b, 0, sizeof(b), "実行部");
	gfx_textn(U(8), U(4), b, cw - U(16), 0xB06000);
	q = snum(b, 0, sizeof(b), kd.pline);
	scat(b, q, sizeof(b), " 行目で停止");
	gfx_textn(U(8), U(4) + ROW_H, b, cw - U(16), 0xB06000);
	y = U(8) + 2 * ROW_H;
	gfx_fill(U(4), y, cw - U(8), ROW_H + U(2), C_HILITE);
	{
		const char *t = kd.pline >= 1 && kd.pline <= f->prog->nlines ? f->prog->lines[kd.pline - 1] : "";
		while (*t == ' ') t++;
		gfx_textn(U(8), y + U(2), t, cw - U(16), C_TEXT);
	}
	y += ROW_H + U(6);
	l_loc.n = f->nslot;
	l_loc.sel = -1;
	l_loc.head = "局所変数";
	lst_draw(&l_loc, U(4), y, cw - U(8), ch - y - U(36), 0);
	bw = (cw - U(12)) / 2;
	x = U(4);
	btn_draw(x, ch - U(30), bw, U(26), "1文 F7", 1);
	btn_draw(x + bw + U(4), ch - U(30), bw, U(26), "続ける F5", 1);
}
static void dbg_mouse(struct win *w, int32 ev, int32 mx, int32 my, int32 cw, int32 ch)
{
	int32 bw = (cw - U(12)) / 2;
	if (ev != WM_DOWN || kd.state != KR_PAUSED) return;
	if (in_rect(mx, my, U(4), ch - U(30), bw, U(26))) kd_step();
	else if (in_rect(mx, my, U(8) + bw, ch - U(30), bw, U(26))) kd_continue();
}

/* ───── トランスクリプト ───── */
static int32 tr_base;		/* 「消す」を押した時点の行数	*/
static int32 tr_top = -1;	/* -1 なら最後を追いかける	*/
#define TR_Y	U(32)
/* 一行が折り返して何段になるか */
static int32 tr_height(const char *t, int32 w)
{
	int32 n = 1, k;
	while ((k = gfx_fitbytes(t, w)) > 0 && t[k]) { t += k; n++; }
	return n;
}
static void tr_draw(struct win *w, int32 cw, int32 ch)
{
	int32 first = kt_count - KT_LINES > tr_base ? kt_count - KT_LINES : tr_base;
	int32 n = kt_count - first, rows = (ch - TR_Y - U(6)) / ROW_H, top, i, used, tw = cw - U(20);
	int32 bw = gfx_textw("消す") + U(20);
	static const uint32 col[4] = { C_TEXT, C_BLUE, C_RED, C_GREEN };
	gfx_fill(0, 0, cw, ch, 0xF4F5F7);
	btn_draw(cw - bw - U(4), U(3), bw, U(25), "消す", 1);
	gfx_textn(U(8), U(6), tr_top < 0 ? "最新を表示中" : "さかのぼって表示中", cw - bw - U(16), C_DIM);
	box_draw(U(4), TR_Y, cw - U(8), ch - TR_Y - U(4));
	if (tr_top < 0) {
		/* 最後の行が下端に来るように、後ろから段数を足して始まりを決める */
		for (top = n, used = 0; top > 0; top--) {
			int32 hgt = tr_height(kt_buf[(first + top - 1) % KT_LINES], tw);
			if (used + hgt > rows) break;
			used += hgt;
		}
	} else top = tr_top < n ? tr_top : n - 1;
	if (top < 0) top = 0;
	wm_clip(U(5), TR_Y + 1, cw - U(10), ch - TR_Y - U(6));
	for (i = top, used = 0; i < n && used < rows; i++) {
		int32 row = (first + i) % KT_LINES;
		const char *t = kt_buf[row];
		do {
			int32 k = gfx_fitbytes(t, tw);
			char seg[KT_WIDTH];
			int32 j;
			for (j = 0; j < k && j < KT_WIDTH - 1; j++) seg[j] = t[j];
			seg[j] = 0;
			gfx_text(U(10), TR_Y + U(2) + used * ROW_H, seg, col[kt_kind[row] & 3]);
			t += k; used++;
		} while (*t && used < rows);
	}
	wm_unclip();
}
static void tr_mouse(struct win *w, int32 ev, int32 mx, int32 my, int32 cw, int32 ch)
{
	int32 bw = gfx_textw("消す") + U(20);
	if (ev == WM_DOWN && in_rect(mx, my, cw - bw - U(4), U(3), bw, U(25))) { tr_base = kt_count; tr_top = -1; }
}
static void tr_wheel(struct win *w, int32 mx, int32 my, int32 dz, int32 cw, int32 ch)
{
	int32 first = kt_count - KT_LINES > tr_base ? kt_count - KT_LINES : tr_base;
	int32 n = kt_count - first, rows = (ch - TR_Y - U(6)) / ROW_H;
	int32 top = tr_top < 0 ? (n - rows > 0 ? n - rows : 0) : tr_top;
	top += dz * 2;
	if (dz > 0 && top >= n - rows) tr_top = -1;
	else tr_top = top < 0 ? 0 : top;
}


/* ───── ファイル: ディスク（KFS）の中身。保存・コンパイル・実行 ───── */
static struct lst l_fs;
#define FS_BUFN	65536
#define FS_MAXL	3000
static char	fs_buf[FS_BUFN];
static const char *fs_line[FS_MAXL];
static int32	fs_nl, fs_top, fs_errl;		/* 表示の先頭行、色を付ける誤りの行（0 なら無し） */
static char	fs_cur[KFS_NAMEL];		/* 表示しているファイル */
static char	fs_msg[200];
static uint32	fs_msgc = C_DIM;
static const char *fs_btn[4] = { "カーネルを保存", "コンパイル", "コンパイルして実行", "消す" };

static uint32 it_fs(struct lst *l, int32 i, char *b, int32 n)
{
	int32 q = snum(b, 0, n, kfs_size(i));
	while (q < 7 && q < n - 1) { int32 k; for (k = q; k >= 0; k--) b[k + 1] = b[k]; b[0] = ' '; q++; }
	q = scat(b, q, n, "  ");
	scat(b, q, n, kfs_name(i));
	return C_TEXT;
}
static void fs_setmsg(uint32 c, const char *a, const char *b)
{
	int32 q = scat(fs_msg, 0, sizeof(fs_msg), a);
	scat(fs_msg, q, sizeof(fs_msg), b);
	fs_msgc = c;
}
static void fs_load(int32 i)
{
	int32 n, k;
	const char *nm = kfs_name(i);
	scat(fs_cur, 0, sizeof(fs_cur), nm);
	n = kfs_read(nm, fs_buf, FS_BUFN - 1);
	if (n < 0) n = 0;
	fs_buf[n] = 0;
	fs_nl = 0; fs_top = 0; fs_errl = 0;
	if (n) fs_line[fs_nl++] = fs_buf;
	for (k = 0; k < n && fs_nl < FS_MAXL; k++) if (fs_buf[k] == '\n') { fs_buf[k] = 0; if (k + 1 < n) fs_line[fs_nl++] = fs_buf + k + 1; }
}
/* 誤りの「名前 12行:」を読んで、そのファイルのその行を見せる */
static void fs_showerr(const char *e)
{
	int32 i, k, ln = 0;
	for (k = 0; e[k] && e[k] != ' '; k++) ;
	if (!e[k]) return;
	{ int32 j = k + 1; while (e[j] >= '0' && e[j] <= '9') ln = ln * 10 + (e[j++] - '0'); }
	for (i = 0; i < kfs_count(); i++) {
		const char *nm = kfs_name(i);
		int32 j;
		for (j = 0; j < k && nm[j] == e[j]; j++) ;
		if (j == k && nm[k] == 0) {
			l_fs.sel = i; fs_load(i);
			fs_errl = ln; fs_top = ln > 5 ? ln - 5 : 0;
			return;
		}
	}
}
static int32 fs_bw(int32 i) { return gfx_textw(fs_btn[i]) + U(16); }
static void fs_btnrect(int32 i, int32 cw, int32 *x, int32 *y)
{
	int32 k, xx = U(4), yy = U(4);
	for (k = 0; k <= i; k++) {
		if (xx + fs_bw(k) > cw - U(4) && xx > U(4)) { xx = U(4); yy += U(28); }
		if (k == i) break;
		xx += fs_bw(k) + U(6);
	}
	*x = xx; *y = yy;
}
static int32 fs_head(int32 cw) { int32 x, y; fs_btnrect(3, cw, &x, &y); return y + U(28); }

static void fs_draw(struct win *w, int32 cw, int32 ch)
{
	int32 i, x, y, top = fs_head(cw), lh, codey, codeh, rows, ln, numw;
	char b[64];
	gfx_fill(0, 0, cw, ch, 0xF4F5F7);
	for (i = 0; i < 4; i++) {
		int32 en = kfs_ready() || i == 0;
		if ((i == 1 || i == 2 || i == 3) && (l_fs.sel < 0 || l_fs.sel >= kfs_count())) en = 0;
		if (i == 2 && (kd.state == KR_RUN || kd.state == KR_PAUSED)) en = 0;
		fs_btnrect(i, cw, &x, &y);
		btn_draw(x, y, fs_bw(i), U(24), fs_btn[i], en);
	}
	if (!kfs_ready()) {
		gfx_textn(U(6), top + U(4), kfs_error(), cw - U(12), C_RED);
		gfx_textn(U(6), top + U(4) + ROW_H, "［カーネルを保存］でディスクを初期化して保存する", cw - U(12), C_DIM);
		return;
	}
	{
		int32 q = scat(b, 0, sizeof(b), "ディスク ");
		q = snum(b, q, sizeof(b), kfs_used() / 2);
		q = scat(b, q, sizeof(b), " / ");
		q = snum(b, q, sizeof(b), kfs_total() / 2);
		scat(b, q, sizeof(b), " KB");
		gfx_textn(U(6), top, b, cw - U(12), C_DIM);
	}
	gfx_textn(U(6), top + ROW_H, fs_msg, cw - U(12), fs_msgc);
	l_fs.n = kfs_count();
	lh = (ch - top - 2 * ROW_H) / 3;
	if (lh < U(80)) lh = U(80);
	lst_draw(&l_fs, U(4), top + 2 * ROW_H + U(2), cw - U(8), lh, 0);
	codey = top + 2 * ROW_H + U(6) + lh; codeh = ch - codey - U(4);
	box_draw(U(4), codey, cw - U(8), codeh);
	rows = (codeh - U(4)) / ROW_H;
	if (fs_top > fs_nl - rows) fs_top = fs_nl - rows;
	if (fs_top < 0) fs_top = 0;
	numw = gfx_textw("0000") + U(6);
	wm_clip(U(5), codey + 1, cw - U(10), codeh - 2);
	for (i = 0, ln = fs_top + 1; ln <= fs_nl && i < rows; i++, ln++) {
		int32 yy = codey + U(2) + i * ROW_H;
		const char *t = fs_line[ln - 1], *u = t;
		uint32 col = 0x202020;
		while (*u == ' ') u++;
		if (u[0] == (char)0xE2 && u[1] == (char)0x80 && u[2] == (char)0xBB) col = C_GREEN;
		else if (u[0] == (char)0xE2 && u[1] == (char)0x96 && u[2] == (char)0xA0) col = C_BLUE;
		if (ln == fs_errl) gfx_fill(U(5), yy, cw - U(10), ROW_H, 0xFFD0D0);
		snum(b, 0, sizeof(b), ln);
		gfx_text(numw - U(2) - gfx_textw(b), yy + U(1), b, C_DIM);
		gfx_textn(numw + U(4), yy + U(1), t, cw - numw - U(14), col);
	}
	wm_unclip();
}
static void fs_do(int32 i)
{
	char err[200];
	int32 r;
	if (i == 0) {
		r = kx_save_kernel(NULL, 0);
		if (r == SYSERR) { fs_setmsg(C_RED, "保存できない: ", kfs_error()); return; }
		{ char b[60]; int32 q = scat(b, 0, sizeof(b), "保存した: "); q = snum(b, q, sizeof(b), r); scat(b, q, sizeof(b), " 個（kxinu/ に核と見本、例題/ に例題）");
		  fs_setmsg(C_GREEN, b, ""); kt_line(3, b); }
		l_fs.n = kfs_count();
		if (l_fs.sel < 0 && l_fs.n) { l_fs.sel = 0; fs_load(0); }
		return;
	}
	if (l_fs.sel < 0 || l_fs.sel >= kfs_count()) return;
	if (i == 3) {
		if (kfs_delete(kfs_name(l_fs.sel)) != OK) { fs_setmsg(C_RED, "消せない: ", kfs_error()); return; }
		fs_setmsg(C_DIM, "消した: ", fs_cur);
		l_fs.sel = -1; fs_nl = 0; fs_cur[0] = 0;
		return;
	}
	/* コンパイル（して実行） */
	{
		char nm[KFS_NAMEL];
		scat(nm, 0, sizeof(nm), kfs_name(l_fs.sel));
		r = kx_compile_file(nm, err, sizeof(err));
		if (r == SYSERR) {
			fs_setmsg(C_RED, "コンパイルできない: ", err);
			{ char b[KT_WIDTH]; int32 q = scat(b, 0, sizeof(b), "コンパイルできない: "); scat(b, q, sizeof(b), err); kt_line(2, b); }
			fs_showerr(err);
			return;
		}
		{
			char b[KT_WIDTH];
			int32 q = scat(b, 0, sizeof(b), "コンパイルした: ");
			q = scat(b, q, sizeof(b), nm);
			q = scat(b, q, sizeof(b), "（アクター定義 ");
			q = snum(b, q, sizeof(b), kprogs[r]->ncls);
			q = scat(b, q, sizeof(b), "、受信節と実行部 ");
			q = snum(b, q, sizeof(b), kprogs[r]->nfun);
			scat(b, q, sizeof(b), "）。ブラウザの一覧に入れた");
			fs_setmsg(C_GREEN, b, ""); kt_line(3, b);
		}
		/* ブラウザで見せる */
		br_tab = 0; l_prog.sel = r; l_cls.sel = 0; l_h.sel = 0; code_mode = 0; set_range();
		lst_show(&l_prog, U(156), r);
		if (i == 2) do_button(0);
	}
}
static void fs_mouse(struct win *w, int32 ev, int32 mx, int32 my, int32 cw, int32 ch)
{
	int32 i, x, y, top = fs_head(cw), lh;
	if (ev != WM_DOWN) return;
	for (i = 0; i < 4; i++) {
		fs_btnrect(i, cw, &x, &y);
		if (in_rect(mx, my, x, y, fs_bw(i), U(24))) {
			if (i == 2 && (kd.state == KR_RUN || kd.state == KR_PAUSED)) return;
			fs_do(i);
			return;
		}
	}
	if (!kfs_ready()) return;
	lh = (ch - top - 2 * ROW_H) / 3;
	if (lh < U(80)) lh = U(80);
	if ((i = lst_hit(&l_fs, U(4), top + 2 * ROW_H + U(2), cw - U(8), lh, mx, my)) >= 0) { l_fs.sel = i; fs_load(i); }
}
static void fs_wheel(struct win *w, int32 mx, int32 my, int32 dz, int32 cw, int32 ch)
{
	int32 top = fs_head(cw), lh = (ch - top - 2 * ROW_H) / 3;
	if (lh < U(80)) lh = U(80);
	if (my < top + 2 * ROW_H + lh) lst_scroll(&l_fs, lh, dz);
	else { fs_top += dz * 3; if (fs_top < 0) fs_top = 0; }
}

/* ───── キー ───── */
static void gkey(struct win *w, int32 k)
{
	if (k == KEY_F5) { if (kd.state == KR_PAUSED) kd_continue(); else if (kd.state != KR_RUN) do_button(0); }
	else if (k == KEY_F7) {
		if (kd.state == KR_PAUSED) kd_step();
		else if (kd.state != KR_RUN) { int32 s = step_start; step_start = 1; do_button(0); step_start = s; }
	}
	else if (k == KEY_F8) kd_pause();
	else if (w == &w_fs && (k == KEY_DOWN || k == KEY_UP)) {
		fs_top += k == KEY_DOWN ? 1 : -1;
		if (fs_top < 0) fs_top = 0;
	}
	else if (w == &w_br && (k == KEY_DOWN || k == KEY_UP)) {
		int32 *t = br_tab == 0 ? &code_top : xs_mode ? &xs_top : &ks_top;
		*t += k == KEY_DOWN ? 1 : -1;
		if (*t < 0) *t = 0;
	}
}

/* ───── 見回り: 実行の様子が変わったら描き直す ───── */
static int32 tick(void)
{
	static int32 lastgen = -1, lastline = -1;
	static struct kfun *lastf = NULL;
	if (kd.gen == lastgen) return 0;
	lastgen = kd.gen;
	if (kd.state == KR_PAUSED && kd.pf && (kd.pf != lastf || kd.pline != lastline)) {
		lastf = kd.pf; lastline = kd.pline;
		if (follow_pause) {
			int32 i;
			goto_pause();
			/* 止まった行が見えるように */
			if (kd.pline - code_from > 3) code_top = kd.pline - code_from - 3;
			for (i = 0; i < kd.nact; i++) if (kd.act[i] == kd.pself) l_act.sel = i;
			if (!w_dbg.shown) w_dbg.shown = 1;
			wm_front(&w_dbg);
		}
	}
	if (kd.state != KR_PAUSED) { lastf = NULL; lastline = -1; }
	return 1;
}

static void place(struct win *w, int32 x, int32 y, int32 ww, int32 h, int32 shown)
{
	w->x = x; w->y = y; w->w = ww; w->h = h; w->shown = shown;
}
/* 既定の並び。文字が大きいときは、ブラウザを縦いっぱいにし、アクターとインスペクタは必要なときに開く */
static void layout(void)
{
	if (ui == 2) {
		place(&w_br,  8, 56, 924, 836, 1);
		place(&w_ctl, 942, 56, 490, 448, 1);
		place(&w_tr,  942, 512, 490, 380, 1);
		place(&w_fs,  380, 120, 552, 700, 0);
		place(&w_act, 942, 512, 490, 380, 0);
		place(&w_ins, 380, 420, 552, 472, 0);
		place(&w_dbg, 380, 56, 552, 340, 0);
		wm_front(&w_ctl); wm_front(&w_tr); wm_front(&w_br);
	} else {
		place(&w_br,  8, 32, 900, 620, 1);
		place(&w_ctl, 916, 32, 516, 236, 1);
		place(&w_act, 916, 276, 516, 196, 1);
		place(&w_ins, 916, 480, 516, 196, 1);
		place(&w_dbg, 916, 684, 516, 208, 1);
		place(&w_tr,  8, 660, 900, 232, 1);
		place(&w_fs,  916, 276, 516, 616, 1);
		wm_front(&w_br); wm_front(&w_fs);
	}
}

static void mkwin(struct win *w, const char *t, int32 x, int32 y, int32 ww, int32 h,
		  void (*d)(struct win *, int32, int32),
		  void (*m)(struct win *, int32, int32, int32, int32, int32),
		  void (*wh)(struct win *, int32, int32, int32, int32, int32))
{
	w->title = t; w->x = x; w->y = y; w->w = ww; w->h = h; w->minw = 160; w->minh = 100;
	w->draw = d; w->mouse = m; w->wheel = wh; w->key = gkey;
	wm_add(w);
}

process kgui_main(void)
{
	input_init();
	wm_init();
	l_prog.item = it_prog; l_prog.head = "プログラム";
	l_cls.item = it_cls;   l_cls.head = "アクター定義";
	l_h.item = it_h;       l_h.head = "受信節";
	l_xd.item = it_xd;     l_xd.head = "ディレクトリ";
	l_xf.item = it_xf;     l_xf.head = "ファイル";
	l_xn.item = it_xn;     l_xn.head = "関数";
	l_kd.item = it_kd; l_kf.item = it_kf; l_kn.item = it_kn;
	xs_pickdir(0); xs_pickfile(0); ks_pickgrp(0);
	l_act.item = it_act;   l_ins.item = it_ins; l_loc.item = it_loc;
	l_prog.n = nkprogs; l_prog.sel = 0; l_cls.sel = 0; l_h.sel = 0; l_act.sel = -1;
	set_range();
	/* 画面 1440x900（論理）。窓の並びは文字の大きさごとに決める（layout） */
	mkwin(&w_br,  "ブラウザ", 0, 0, 100, 100, br_draw, br_mouse, br_wheel);
	mkwin(&w_ctl, "実行", 0, 0, 100, 100, ctl_draw, ctl_mouse, NULL);
	mkwin(&w_act, "アクター", 0, 0, 100, 100, act_draw, act_mouse, act_wheel);
	mkwin(&w_ins, "インスペクタ", 0, 0, 100, 100, ins_draw, NULL, ins_wheel);
	mkwin(&w_dbg, "デバッガ", 0, 0, 100, 100, dbg_draw, dbg_mouse, NULL);
	mkwin(&w_tr,  "トランスクリプト", 0, 0, 100, 100, tr_draw, tr_mouse, tr_wheel);
	mkwin(&w_fs,  "ファイル", 0, 0, 100, 100, fs_draw, fs_mouse, fs_wheel);
	l_fs.item = it_fs; l_fs.head = "大きさ  名前"; l_fs.sel = -1;
	if (kfs_init() == OK) fs_setmsg(C_DIM, "ファイルを選び［コンパイル］。先頭の「※ 先に読む:」のファイルは前につなぐ", "");
	wm_ui_hook = layout;
	layout();
	kt_line(3, "ブラウザでプログラムを選び、［実行］を押す。");
	wm_run(tick);
	return OK;
}
