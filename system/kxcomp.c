/* kxcomp.c - Xinu の中のことのはコンパイラ: 構文木を作る・名前を解決する・struct kprogram にする・実行する
 *
 * 意味は k2xinu.mjs（Mac で C にする変換器）に合わせる:
 *   - 名前は、受信節のアクターの状態にあり、受け取った名前でなければ状態。そうでなければ局所変数
 *   - 繰り返しの範囲は終わり→始めの順に一度だけ計算する。「現在の番号」は一番内側の繰り返し
 *   - 各文の前で kstep（デバッガの停止点・1文実行）
 */
#include <xinu.h>
#include "kxc.h"
#include "kxc.tab.h"

extern int strcmp(const char *, const char *);
extern int kxparse(void);
extern const char *kx_curtext;

struct kxprog kx_prog;
char	kx_errmsg[200];
char	kx_errtext[200];
int32	kx_errline;

/* ───── 置き場（コンパイル1回分。プログラムを置き換えるときにまとめて返す） ───── */
struct kxchunk { struct kxchunk *next; uint32 size, used; };
static struct kxchunk *arena;
#define CHUNK	32768

void *kx_alloc(uint32 n)
{
	struct kxchunk *c;
	char *p;
	n = (n + 7) & ~7;
	if (!arena || arena->used + n > arena->size) {
		uint32 sz = n + sizeof(struct kxchunk) > CHUNK ? n + sizeof(struct kxchunk) : CHUNK;
		c = (struct kxchunk *)getmem(sz);
		if ((char *)c == (char *)SYSERR) panic("kxc: メモリが足りない");
		c->next = arena; c->size = sz; c->used = (sizeof(struct kxchunk) + 7) & ~7;
		arena = c;
	}
	p = (char *)arena + arena->used;
	arena->used += n;
	{ uint32 i; for (i = 0; i < n; i++) p[i] = 0; }
	return p;
}
static void arena_free(struct kxchunk *a)
{
	while (a) { struct kxchunk *n = a->next; freemem((char *)a, a->size); a = n; }
}

/* ───── 文字列の小道具 ───── */
static int32 slen(const char *s) { int32 n = 0; while (s[n]) n++; return n; }
static char *scat3(const char *a, const char *b, const char *c)
{
	int32 la = slen(a), lb = slen(b), lc = slen(c), i;
	char *r = kx_alloc(la + lb + lc + 1);
	for (i = 0; i < la; i++) r[i] = a[i];
	for (i = 0; i < lb; i++) r[la + i] = b[i];
	for (i = 0; i < lc; i++) r[la + lb + i] = c[i];
	return r;
}
static int32 ecat(char *b, int32 p, int32 n, const char *s) { while (*s && p < n - 1) b[p++] = *s++; b[p] = 0; return p; }
static int32 ecatnum(char *b, int32 p, int32 n, int32 v)
{
	char t[12]; int32 i = 11;
	t[i] = 0;
	do { t[--i] = '0' + v % 10; v /= 10; } while (v);
	return ecat(b, p, n, t + i);
}
static int32 failed;
void kx_semerr(int32 line, const char *a, const char *b, const char *c)
{
	int32 p = 0;
	if (failed) return;
	failed = 1;
	kx_errline = line;
	p = ecatnum(kx_errmsg, 0, sizeof(kx_errmsg), line);
	p = ecat(kx_errmsg, p, sizeof(kx_errmsg), "行: ");
	p = ecat(kx_errmsg, p, sizeof(kx_errmsg), a);
	p = ecat(kx_errmsg, p, sizeof(kx_errmsg), b);
	ecat(kx_errmsg, p, sizeof(kx_errmsg), c);
	p = ecat(kx_errtext, 0, sizeof(kx_errtext), a);
	p = ecat(kx_errtext, p, sizeof(kx_errtext), b);
	ecat(kx_errtext, p, sizeof(kx_errtext), c);
}
void kxerror(const char *m)
{
	kx_semerr(kxlloc.first_line, "構文エラー 「", kx_curtext, scat3("」の所: ", m, ""));
}
/* 「…」の中身 */
static const char *unq(const char *s)
{
	int32 n = slen(s);
	char *r;
	int32 i;
	if (n < 6) return s;
	r = kx_alloc(n - 5);
	for (i = 0; i < n - 6; i++) r[i] = s[3 + i];
	return r;
}

/* ───── 構文木を作る（kxc.y から） ───── */
struct kxe *kx_e(int32 k, const char *s)
{
	struct kxe *e = kx_alloc(sizeof(*e));
	e->k = k; e->s = s; e->txt = s;
	if (k == E_NUM) { const char *p = s; e->n = 0; while (*p >= '0' && *p <= '9') e->n = e->n * 10 + (*p++ - '0'); }
	if (k == E_STR) e->s = unq(s);
	if (k == E_NEW) e->txt = scat3("「", s, "」の新しいアクター");
	return e;
}
struct kxe *kx_e2(int32 k, struct kxe *a, struct kxe *b, const char *op)
{
	struct kxe *e = kx_alloc(sizeof(*e));
	e->k = k; e->a = a; e->b = b;
	switch (k) {
	case E_FIELD: e->txt = scat3(a->txt, "の", b->s); break;
	case E_INDEX: e->txt = scat3(scat3(a->txt, "の ", b->txt), " 番目", ""); break;
	case E_LEN:   e->txt = scat3(a->txt, " の要素数", ""); break;
	case E_ADD:   e->txt = scat3(scat3("（", a->txt, " 足す "), b->txt, "）"); break;
	case E_SUB:   e->txt = scat3(scat3("（", a->txt, " 引く "), b->txt, "）"); break;
	case E_MOD:   e->txt = scat3(scat3("（", a->txt, " を "), b->txt, " で割った余り）"); break;
	default:      e->txt = op ? op : "";
	}
	return e;
}
struct kxl *kx_list(struct kxe *e, struct kxl *prev)
{
	struct kxl *l = kx_alloc(sizeof(*l)), *p;
	l->e = e;
	if (!prev) return l;
	for (p = prev; p->next; p = p->next) ;
	p->next = l;
	return prev;
}
struct kxs *kx_st(int32 k, struct kxl *l, struct kxe *a, struct kxe *b, const char *msg, int32 line)
{
	struct kxs *s = kx_alloc(sizeof(*s));
	s->k = k; s->l = l; s->a = a; s->b = b; s->msg = msg ? unq(msg) : NULL; s->line = line;
	return s;
}
struct kxs *kx_stappend(struct kxs *a, struct kxs *b)
{
	struct kxs *p;
	if (!a) return b;
	for (p = a; p->next; p = p->next) ;
	p->next = b;
	return a;
}
struct kxs *kx_if(struct kxe *cond, struct kxs *then, struct kxs *els, int32 line)
{
	struct kxs *s = kx_st(S_IF, NULL, cond, NULL, NULL, line);
	s->body = then; s->els = els;
	return s;
}
struct kxs *kx_loop(struct kxe *lo, struct kxe *hi, struct kxs *body, int32 line)
{
	struct kxs *s = kx_st(S_LOOP, NULL, lo, hi, NULL, line);
	s->body = body;
	return s;
}
struct kxs *kx_bind(struct kxe *maker, const char *name, int32 line)
{
	return kx_st(S_CHG, kx_list(kx_e(E_NAME, name), NULL), maker, NULL, NULL, line);
}
struct kxname *kx_name(const char *s, struct kxname *prev)
{
	struct kxname *n = kx_alloc(sizeof(*n)), *p;
	n->s = s;
	if (!prev) return n;
	for (p = prev; p->next; p = p->next) ;
	p->next = n;
	return prev;
}
struct kxitem *kx_item(int32 kind, const char *h, struct kxs *st, int32 line, int32 last)
{
	struct kxitem *it = kx_alloc(sizeof(*it));
	it->kind = kind; it->h = h; it->st = st; it->line = line; it->last = last;
	return it;
}
struct kxitem *kx_inits(struct kxl *names, struct kxe *v, int32 line)
{
	struct kxitem *r = NULL;
	for (; names; names = names->next) {
		struct kxitem *it;
		if (names->e->k != E_NAME) { kx_semerr(line, "初期値は状態の名前に付ける（", names->e->txt, "）"); return NULL; }
		it = kx_item(0, NULL, NULL, line, line);
		it->field = names->e->s; it->val = v;
		r = kx_itemappend(r, it);
	}
	return r;
}
struct kxitem *kx_itemappend(struct kxitem *a, struct kxitem *b)
{
	struct kxitem *p;
	if (!a) return b;
	for (p = a; p->next; p = p->next) ;
	p->next = b;
	return a;
}
const char *kx_header(const char *msgtok, const char *param)
{
	return scat3(unq(msgtok), "\x1f", param ? param : "");
}
struct kxdef *kx_defappend(struct kxdef *a, struct kxdef *b)
{
	struct kxdef *p;
	if (!a) return b;
	for (p = a; p->next; p = p->next) ;
	p->next = b;
	return a;
}
/* 定義の平らな並びを、初期値と受信節に振り分ける（kotonoha.y の print_def と同じ検査） */
struct kxdef *kx_def(const char *name, struct kxname *decl, struct kxitem *items, const char *endname, int32 line, int32 end)
{
	struct kxdef *d = kx_alloc(sizeof(*d));
	struct kxname *n;
	struct kxitem *it;
	int32 i, nh = 0, ni = 0, cur = -1;
	if (strcmp(name, endname) != 0) { kx_semerr(end, scat3("意味エラー: 「", name, "」の定義を「"), endname, "」で閉じている"); return NULL; }
	d->name = name; d->line = line; d->end = end;
	for (n = decl; n; n = n->next) d->nf++;
	d->fields = kx_alloc(sizeof(char *) * (d->nf + 1));
	for (i = 0, n = decl; n; n = n->next) d->fields[i++] = n->s;
	for (it = items; it; it = it->next) { if (it->kind == 1) nh++; if (it->kind == 0) ni++; }
	d->h = kx_alloc(sizeof(struct kxhand) * (nh + 1));
	d->initf = kx_alloc(sizeof(char *) * (ni + 1));
	d->initv = kx_alloc(sizeof(struct kxe *) * (ni + 1));
	for (it = items; it; it = it->next) {
		if (it->kind == 0) {
			if (cur >= 0) { kx_semerr(it->line, "意味エラー: ", name, " の初期値の文は受信節より前に書く"); return NULL; }
			for (i = 0; i < d->nf && strcmp(d->fields[i], it->field) != 0; i++) ;
			if (i == d->nf) { kx_semerr(it->line, scat3("意味エラー: 「", it->field, "」は "), name, " の状態に無い"); return NULL; }
			d->initf[d->ninit] = it->field; d->initv[d->ninit++] = it->val;
		} else if (it->kind == 1) {
			const char *h = it->h;
			int32 k;
			struct kxhand *hd = &d->h[++cur];
			for (k = 0; h[k] && h[k] != '\x1f'; k++) ;
			{ char *m = kx_alloc(k + 1); int32 j; for (j = 0; j < k; j++) m[j] = h[j]; hd->msg = m; }
			hd->param = h[k] && h[k + 1] ? h + k + 1 : NULL;
			hd->body = it->st; hd->line = it->line; hd->end = it->last;
		} else {
			if (cur < 0) { kx_semerr(it->line, "意味エラー: ", name, " で受信節の外に文がある"); return NULL; }
			d->h[cur].body = kx_stappend(d->h[cur].body, it->st);
			d->h[cur].end = it->last;
		}
	}
	d->nh = cur + 1;
	return d;
}

/* ───── 名前の解決 ───── */
#define KX_MAXSLOT	64
#define KX_MAXLOOP	16
struct rctx { struct kxdef *d; const char *param; const char *slot[KX_MAXSLOT]; int32 nslot, depth; };

static int32 slotof(struct rctx *c, const char *n, int32 line)
{
	int32 i;
	for (i = 0; i < c->nslot; i++) if (strcmp(c->slot[i], n) == 0) return i;
	if (c->nslot >= KX_MAXSLOT) { kx_semerr(line, "局所変数が多すぎる", "", ""); return 0; }
	c->slot[c->nslot] = n;
	return c->nslot++;
}
static void rname(struct kxe *e, struct rctx *c, int32 line)
{
	int32 i;
	if (c->d && !(c->param && strcmp(c->param, e->s) == 0))
		for (i = 0; i < c->d->nf; i++)
			if (strcmp(c->d->fields[i], e->s) == 0) { e->isfield = 1; e->n = i; return; }
	e->isfield = 0; e->n = slotof(c, e->s, line);
}
static void rexpr(struct kxe *e, struct rctx *c, int32 line)
{
	if (!e || failed) return;
	switch (e->k) {
	case E_NAME: rname(e, c, line); return;
	case E_SELF: if (!c->d) kx_semerr(line, "「実行を始める。」の中に自分は無い", "", ""); return;
	case E_CUR:
		if (c->depth == 0) kx_semerr(line, "繰り返しの外で「現在の番号」を使った", "", "");
		e->n = c->depth - 1;
		return;
	case E_FIELD: rexpr(e->a, c, line); return;		/* b は欄の名前（実行時に相手のアクターで引く） */
	case E_NEW: {
		struct kxdef *d;
		int32 i = 0;
		for (d = kx_prog.defs; d; d = d->next, i++) if (strcmp(d->name, e->s) == 0) { e->n = i; return; }
		kx_semerr(line, "「", e->s, "」というアクターは定義されていない");
		return;
	}
	default: rexpr(e->a, c, line); rexpr(e->b, c, line);
	}
}
static void rtarget(struct kxe *e, struct rctx *c, int32 line)
{
	if (e->k == E_NAME || e->k == E_FIELD || e->k == E_INDEX) rexpr(e, c, line);
	else kx_semerr(line, "「", e->txt, "」には代入できない");
}
static void rstmts(struct kxs *s, struct rctx *c)
{
	struct kxl *l;
	for (; s && !failed; s = s->next) {
		switch (s->k) {
		case S_DISP: case S_SEND: for (l = s->l; l; l = l->next) rexpr(l->e, c, s->line); rexpr(s->a, c, s->line); break;
		case S_ZENIN: rexpr(s->a, c, s->line); rexpr(s->b, c, s->line); break;
		case S_CHG: rexpr(s->a, c, s->line); for (l = s->l; l; l = l->next) rtarget(l->e, c, s->line); break;
		case S_ADD: rexpr(s->a, c, s->line); rtarget(s->l->e, c, s->line); break;
		case S_PUSH: rexpr(s->a, c, s->line); for (l = s->l; l; l = l->next) rexpr(l->e, c, s->line); break;
		case S_TAKE: rexpr(s->b, c, s->line); rtarget(s->a, c, s->line); break;
		case S_IF: rexpr(s->a, c, s->line); rstmts(s->body, c); rstmts(s->els, c); break;
		case S_LOOP:
			rexpr(s->a, c, s->line); rexpr(s->b, c, s->line);
			if (c->depth >= KX_MAXLOOP) { kx_semerr(s->line, "繰り返しの入れ子が深すぎる", "", ""); return; }
			s->depth = c->depth++;
			rstmts(s->body, c);
			c->depth--;
			break;
		}
	}
}
static const char **keepslots(struct rctx *c)
{
	const char **r = kx_alloc(sizeof(char *) * (c->nslot + 1));
	int32 i;
	for (i = 0; i < c->nslot; i++) r[i] = c->slot[i];
	return r;
}

/* ───── 実行器 ───── */
struct kxframe { struct kact *self; struct kfun *f; kv L[KX_MAXSLOT]; int32 loop[KX_MAXLOOP]; };
static kv ev(struct kxe *e, struct kxframe *fr);

static kv *lval(struct kxe *e, struct kxframe *fr)	/* 名前・欄の置き場所（番目は kset で書く） */
{
	if (e->k == E_NAME) return e->isfield ? &fr->self->f[e->n] : &fr->L[e->n];
	return kfield(ev(e->a, fr), e->b->s, e->txt);
}
static void assign(struct kxe *t, kv v, struct kxframe *fr)
{
	if (t->k == E_INDEX) { kv base = ev(t->a, fr); kset(base, ev(t->b, fr), v, t->txt); return; }
	*lval(t, fr) = v;
}
static kv ev(struct kxe *e, struct kxframe *fr)
{
	switch (e->k) {
	case E_NAME:  return e->isfield ? fr->self->f[e->n] : kread(fr->L[e->n], e->txt);
	case E_NUM:   return kn(e->n);
	case E_STR:   return ks(e->s);
	case E_TRUE:  return kb(1);
	case E_FALSE: return kb(0);
	case E_NONE:  return knone();
	case E_ARR:   return knewarr();
	case E_SELF:  return kactv(fr->self);
	case E_CUR:   return kn(fr->loop[e->n]);
	case E_FIELD: return *kfield(ev(e->a, fr), e->b->s, e->txt);
	case E_INDEX: { kv a = ev(e->a, fr); return kget(a, ev(e->b, fr), e->txt); }
	case E_LEN:   return klen(ev(e->a, fr), e->txt);
	case E_ADD:   { kv a = ev(e->a, fr); return kadd(a, ev(e->b, fr), e->txt); }
	case E_SUB:   { kv a = ev(e->a, fr); return ksub(a, ev(e->b, fr), e->txt); }
	case E_MOD:   { kv a = ev(e->a, fr); return kmod(a, ev(e->b, fr), e->txt); }
	case E_NEW: {
		struct kxdef *d = kx_prog.defs;
		struct kclass *c = NULL;
		struct kprogram *p = kd.prog;
		int32 i;
		(void)d;
		for (i = 0; p && i < p->ncls; i++) if (strcmp(p->cls[i]->name, e->s) == 0) c = p->cls[i];
		if (!c) { kerror("アクター定義が見つからない", e->txt); return knone(); }
		return knew(c);
	}
	}
	return knone();
}
static void ex(struct kxs *s, struct kxframe *fr)
{
	struct kxl *l;
	for (; s; s = s->next) {
		kstep(fr->f, s->line, fr->self, fr->L);
		switch (s->k) {
		case S_DISP: {
			int32 lit[32], n = 0;
			kv vals[32];
			for (l = s->l; l && n < 32; l = l->next, n++) { lit[n] = l->e->k == E_STR; vals[n] = ev(l->e, fr); }
			kdisp(n, lit, vals);
			break;
		}
		case S_SEND: {
			kv a = s->a ? ev(s->a, fr) : knone();
			for (l = s->l; l; l = l->next) ksend(ev(l->e, fr), s->msg, a, s->a != NULL);
			break;
		}
		case S_ZENIN: {
			kv arr = ev(s->a, fr);
			ksendall(arr, s->msg, s->b ? ev(s->b, fr) : knone(), s->b != NULL, s->a->txt);
			break;
		}
		case S_CHG: { kv v = ev(s->a, fr); for (l = s->l; l; l = l->next) assign(l->e, v, fr); break; }
		case S_ADD: { kv v = ev(s->l->e, fr); assign(s->l->e, kadd(v, ev(s->a, fr), s->l->e->txt), fr); break; }
		case S_PUSH: { kv arr = ev(s->a, fr); for (l = s->l; l; l = l->next) kpush(arr, ev(l->e, fr), s->a->txt); break; }
		case S_TAKE: assign(s->a, kshift(ev(s->b, fr), s->b->txt), fr); break;
		case S_IF: {
			struct kxe *c = s->a;
			kv a = ev(c->a, fr), b = ev(c->b, fr);
			int32 t = c->k == E_EQ ? keq(a, b) : c->k == E_NE ? !keq(a, b) : klt(a, b, c->a->txt, c->b->txt);
			ex(t ? s->body : s->els, fr);
			break;
		}
		case S_LOOP: {
			int32 hi = knum(ev(s->b, fr), s->b->txt), v;
			for (v = knum(ev(s->a, fr), s->a->txt); v <= hi; v++) { fr->loop[s->depth] = v; ex(s->body, fr); }
			break;
		}
		}
	}
}

/* ───── コンパイルしたプログラムの記録（実行時に kclass／kprogram から構文木へ戻る） ───── */
struct kxcp {
	struct kprogram	*p;
	struct kxprog	prog;
	struct kxchunk	*arena;
	struct kfun	*mainf;
};
#define KX_MAXCP	KPROGS_MAX
static struct kxcp cps[KX_MAXCP];
static int32 ncps;

static struct kxcp *cp_of_prog(struct kprogram *p)
{
	int32 i;
	for (i = 0; i < ncps; i++) if (cps[i].p == p) return &cps[i];
	return NULL;
}
/* 受信節: 動いているアクターの定義と、処理中のメッセージ名（self->cur）から構文木を見つける */
static void kx_hfn(struct kact *self, kv arg)
{
	struct kxcp *cp = cp_of_prog(kd.prog);
	struct kxdef *d;
	struct kxframe fr;
	int32 i, fi = 0;
	if (!cp) { kerror("コンパイルしたプログラムが見つからない", ""); return; }
	for (d = cp->prog.defs; d; d = d->next) {
		if (d->kc == self->c) break;
		fi += d->nh;
	}
	if (!d) { kerror("アクター定義が見つからない", self->c->name); return; }
	for (i = 0; i < d->nh && strcmp(d->h[i].msg, self->cur) != 0; i++) ;
	if (i == d->nh) { kerror("受信節が見つからない", self->cur); return; }
	fr.self = self; fr.f = &cp->p->funs[fi + i];
	{ int32 k; for (k = 0; k < KX_MAXSLOT; k++) fr.L[k].t = KN_UNSET; }
	if (d->h[i].param) fr.L[0] = arg;		/* 受け取る名前は局所変数の 0 番 */
	ex(d->h[i].body, &fr);
}
static void kx_ifn(struct kact *self)
{
	struct kxcp *cp = cp_of_prog(kd.prog);
	struct kxdef *d;
	struct kxframe fr;
	int32 i, j, k;
	if (!cp) return;
	for (d = cp->prog.defs; d && d->kc != self->c; d = d->next) ;
	if (!d) return;
	fr.self = self; fr.f = NULL;
	for (k = 0; k < KX_MAXSLOT; k++) fr.L[k].t = KN_UNSET;
	for (i = 0; i < d->ninit; i++) {
		for (j = 0; j < d->nf && strcmp(d->fields[j], d->initf[i]) != 0; j++) ;
		self->f[j] = ev(d->initv[i], &fr);
	}
}
static void kx_body(void)
{
	struct kxcp *cp = cp_of_prog(kd.prog);
	struct kxframe fr;
	int32 k;
	if (!cp) return;
	fr.self = NULL; fr.f = cp->mainf;
	for (k = 0; k < KX_MAXSLOT; k++) fr.L[k].t = KN_UNSET;
	ex(cp->prog.main, &fr);
}

/* 文のある行に印を付ける（停止点を置ける行） */
static void markstmts(struct kxs *s, unsigned char *st, int32 n)
{
	for (; s; s = s->next) {
		if (s->line >= 1 && s->line <= n) st[s->line] = 1;
		markstmts(s->body, st, n); markstmts(s->els, st, n);
	}
}

static sid32 kxmutex = SYSERR;

int32 kx_compile(const char *name, const char *src, int32 len)
{
	struct kxchunk *saved;
	struct kprogram *p;
	struct kxdef *d;
	struct rctx *rc;
	int32 i, ncls = 0, nfun = 0, fi, nl, slot = -1;
	char *copy;
	const char **lines;

	if (kxmutex == SYSERR) kxmutex = semcreate(1);
	wait(kxmutex);
	saved = arena; arena = NULL;
	failed = 0; kx_errmsg[0] = 0; kx_errline = 0;
	kx_prog.defs = NULL; kx_prog.main = NULL;

	/* 字句 → 構文 */
	if (kx_lex_start(src, len) != OK || kxparse() != 0 || failed) {
		kx_lex_end();
		if (!failed) kx_semerr(kxlloc.first_line, "構文エラー", "", "");
		goto bad;
	}
	kx_lex_end();
	/* 名前の解決 */
	rc = kx_alloc(sizeof(*rc));
	for (d = kx_prog.defs; d; d = d->next) {
		ncls++;
		for (i = 0; i < d->nh; i++) {
			int32 k;
			rc->d = d; rc->param = d->h[i].param; rc->nslot = 0; rc->depth = 0;
			if (rc->param) slotof(rc, rc->param, d->h[i].line);
			rstmts(d->h[i].body, rc);
			d->h[i].nslot = rc->nslot; d->h[i].slots = keepslots(rc);
			for (k = 0; k < i; k++)
				if (strcmp(d->h[k].msg, d->h[i].msg) == 0) kx_semerr(d->h[i].line, "「", d->h[i].msg, "」の受信節が二つある");
			nfun++;
		}
		rc->d = d; rc->param = NULL; rc->nslot = 0; rc->depth = 0;
		for (i = 0; i < d->ninit; i++) rexpr(d->initv[i], rc, d->line);
	}
	rc->d = NULL; rc->param = NULL; rc->nslot = 0; rc->depth = 0;
	rstmts(kx_prog.main, rc);
	if (failed) goto bad;

	/* 本文の行（デバッガとブラウザで見せる） */
	copy = kx_alloc(len + 1);
	for (i = 0; i < len; i++) copy[i] = src[i] == '\r' ? ' ' : src[i];
	copy[len] = 0;
	while (len > 0 && copy[len - 1] == '\n') copy[--len] = 0;
	for (nl = 1, i = 0; i < len; i++) if (copy[i] == '\n') nl++;
	lines = kx_alloc(sizeof(char *) * nl);
	lines[0] = copy;
	for (nl = 1, i = 0; i < len; i++) if (copy[i] == '\n') { copy[i] = 0; lines[nl++] = copy + i + 1; }

	/* kprogram を組み立てる（形は k2xinu.mjs の出力と同じ） */
	p = kx_alloc(sizeof(*p));
	{
		char *nm = kx_alloc(slen(name) + 1);
		for (i = 0; name[i]; i++) nm[i] = name[i];
		p->name = nm;
	}
	p->ncls = ncls;
	p->cls = kx_alloc(sizeof(struct kclass *) * (ncls + 1));
	{
		int32 *cl = kx_alloc(sizeof(int32) * (ncls + 1)), *ce = kx_alloc(sizeof(int32) * (ncls + 1));
		for (i = 0, d = kx_prog.defs; d; d = d->next, i++) {
			struct kclass *c = kx_alloc(sizeof(*c));
			struct khent *h = kx_alloc(sizeof(struct khent) * (d->nh + 1));
			int32 k;
			for (k = 0; k < d->nh; k++) { h[k].msg = d->h[k].msg; h[k].fn = kx_hfn; }
			c->name = d->name; c->nf = d->nf; c->fields = d->fields; c->init = kx_ifn; c->nh = d->nh; c->h = h;
			d->kc = c; p->cls[i] = c; cl[i] = d->line; ce[i] = d->end;
		}
		p->cline = cl; p->cend = ce;
	}
	p->body = kx_body; p->mline = kx_prog.mline; p->mend = kx_prog.mend;
	p->nlines = nl; p->lines = lines; p->nsrc = nl; p->src = lines;
	{
		unsigned char *st = kx_alloc(nl + 2);
		for (d = kx_prog.defs; d; d = d->next) for (i = 0; i < d->nh; i++) markstmts(d->h[i].body, st, nl);
		markstmts(kx_prog.main, st, nl);
		p->stmt = st;
		p->bp = kx_alloc(nl + 2);
	}
	p->nfun = nfun + 1;
	p->funs = kx_alloc(sizeof(struct kfun) * (nfun + 1));
	for (fi = 0, i = 0, d = kx_prog.defs; d; d = d->next, i++) {
		int32 k;
		for (k = 0; k < d->nh; k++, fi++) {
			struct kfun *f = &p->funs[fi];
			f->prog = p; f->cls = i; f->msg = d->h[k].msg; f->line = d->h[k].line; f->end = d->h[k].end;
			f->nslot = d->h[k].nslot; f->slots = d->h[k].slots;
		}
	}
	{
		struct kfun *f = &p->funs[fi];
		f->prog = p; f->cls = -1; f->msg = "実行部"; f->line = kx_prog.mline; f->end = kx_prog.mend;
		f->nslot = rc->nslot; f->slots = keepslots(rc);
	}

	/* 一覧に入れる（同じ名前があれば置き換える） */
	for (i = 0; i < nkprogs; i++) if (strcmp(kprogs[i]->name, p->name) == 0) { slot = i; break; }
	if (slot >= 0) {
		struct kxcp *old = cp_of_prog(kprogs[slot]);
		if (kd.prog == kprogs[slot] && (kd.state == KR_RUN || kd.state == KR_PAUSED)) {
			kx_semerr(0, "「", name, "」は実行中なので置き換えられない（中止してから）");
			goto bad;
		}
		if (!old) {	/* Mac で組み込んだもの（同じ名前）は残して、新しい方を後ろへ */
			slot = -1;
		} else {
			if (kd.prog == old->p) kd.prog = NULL;
			arena_free(old->arena);
			old->p = NULL;
		}
	}
	if (slot < 0) {
		if (nkprogs >= KPROGS_MAX) { kx_semerr(0, "プログラムの一覧がいっぱい", "", ""); goto bad; }
		slot = nkprogs++;
	}
	kprogs[slot] = p;
	{
		struct kxcp *cp = NULL;
		for (i = 0; i < ncps; i++) if (cps[i].p == NULL) { cp = &cps[i]; break; }
		if (!cp) cp = &cps[ncps++];
		cp->p = p; cp->prog = kx_prog; cp->arena = arena; cp->mainf = &p->funs[fi];
	}
	arena = saved;
	signal(kxmutex);
	return slot;
bad:
	arena_free(arena);
	arena = saved;
	signal(kxmutex);
	return SYSERR;
}
