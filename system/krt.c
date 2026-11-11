/* krt.c - ことのは実行時ライブラリ（PC Xinu 用）。意味はブラウザ版 web/runtime.js の実行系に合わせる */
#include <xinu.h>
#include "krt.h"

extern int strcmp(const char *, const char *);	/* lib/strcmp.c（string.h に宣言が無い） */

#define KSTK	16384
#define KPRIO	20

static sid32	klock = SYSERR;	/* 受信節を一つずつ実行するための錠	*/
static sid32	kdbgsem = SYSERR;	/* 止まっている文を先へ進める合図	*/
static int32	kpending;	/* 送られてまだ処理の終わっていない数（実行部を1と数える） */
static volatile int32 kabort;	/* 中止の合図: 次の文・次のメッセージでそのアクターを止める */
static struct kact *kcurself;	/* 錠を持って受信節を実行中のアクター（実行部は NULL） */
static pid32	krunner = SYSERR;	/* 実行部を走らせるプロセス		*/
static struct kfun *klastf;	/* 最後に通った文（誤りの場所の報告に使う） */
static int32	klastline;

struct kdbg kd;
char	kt_buf[KT_LINES][KT_WIDTH];
unsigned char kt_kind[KT_LINES];
int32	kt_count;

/* ───── 文字列 ───── */
static int32 kslen(const char *s) { int32 n = 0; while (s[n]) n++; return n; }

/* buf[0..n-1] に s を足す。UTF-8 の文字の途中では切らない。足した後の長さを返す */
static int32 kcat(char *buf, int32 pos, int32 n, const char *s)
{
	int32 i = 0, k;
	while (s[i] && pos < n - 1) {
		unsigned char c = (unsigned char)s[i];
		int32 len = c < 0x80 ? 1 : c < 0xE0 ? 2 : c < 0xF0 ? 3 : 4;
		if (pos + len > n - 1) break;
		for (k = 0; k < len && s[i]; k++) buf[pos++] = s[i++];
	}
	buf[pos] = '\0';
	return pos;
}

static int32 kcatnum(char *buf, int32 pos, int32 n, int32 v)
{
	char t[16];
	int32 i = 15;
	uint32 u = v < 0 ? (uint32)(-v) : (uint32)v;
	t[i] = '\0';
	do { t[--i] = '0' + (u % 10); u /= 10; } while (u);
	if (v < 0) t[--i] = '-';
	return kcat(buf, pos, n, &t[i]);
}

static int32 kshow_at(char *buf, int32 pos, int32 n, kv v, int32 depth)
{
	int32 i;
	switch (v.t) {
	case KN_NUM:  return kcatnum(buf, pos, n, v.u.n);
	case KN_BOOL: return kcat(buf, pos, n, v.u.n ? "はい" : "いいえ");
	case KN_STR:  return kcat(buf, pos, n, v.u.s);
	case KN_ARR:
		if (depth > 4) return kcat(buf, pos, n, "[…]");
		pos = kcat(buf, pos, n, "[");
		for (i = 0; i < v.u.a->len; i++) {
			if (i) pos = kcat(buf, pos, n, "、");
			pos = kshow_at(buf, pos, n, v.u.a->e[i], depth + 1);
		}
		return kcat(buf, pos, n, "]");
	case KN_ACT:
		pos = kcat(buf, pos, n, v.u.o->c->name);
		pos = kcat(buf, pos, n, "#");
		return kcatnum(buf, pos, n, v.u.o->id);
	case KN_UNSET: return kcat(buf, pos, n, "（未設定）");
	default:      return kcat(buf, pos, n, "なし");
	}
}
int32 kshowbuf(char *buf, int32 n, kv v) { buf[0] = '\0'; return kshow_at(buf, 0, n, v, 0); }

void kt_line(int32 kind, const char *s)
{
	int32 row = kt_count % KT_LINES;
	kcat(kt_buf[row], 0, KT_WIDTH, s);
	kt_kind[row] = kind;
	kt_count++;
	kd.gen++;
}

/* ───── 値 ───── */
static void *kalloc(uint32 n)
{
	char *p = getmem(n);
	if (p == (char *)SYSERR) kerror("メモリが足りない", "");
	return p;
}

kv kn(int32 n)   { kv v; v.t = KN_NUM;  v.u.n = n; return v; }
kv kb(int32 b)   { kv v; v.t = KN_BOOL; v.u.n = b ? 1 : 0; return v; }
kv knone(void)   { kv v; v.t = KN_NONE; v.u.n = 0; return v; }
kv ks(const char *s) { kv v; v.t = KN_STR; v.u.s = s; return v; }
kv kactv(struct kact *a) { kv v; v.t = KN_ACT; v.u.o = a; return v; }
kv knewarr(void)
{
	kv v;
	struct karr *a = (struct karr *)kalloc(sizeof(struct karr));
	a->len = 0; a->cap = 4;
	a->e = (kv *)kalloc(sizeof(kv) * a->cap);
	v.t = KN_ARR; v.u.a = a;
	return v;
}

/* ───── 止める・終わる ───── */
static void kdie(struct kact *a)
{
	if (a) a->st = KA_DEAD;
	kd.gen++;
	signal(klock);
	kill(getpid());
}

static void kfinish(void)
{
	char b[KT_WIDTH];
	int32 p, i, j, k, waits = 0;
	if (kd.state != KR_ERROR) kd.state = KR_DONE;
	/* 止まったとき、状態の中の「アクターだけが並ぶ配列」にアクターが残っていれば、待たされたまま終わった（runtime.js の waiting と同じ判定） */
	for (i = 0; i < kd.nact; i++) {
		struct kact *a = kd.act[i];
		for (j = 0; j < a->c->nf; j++) {
			kv v = a->f[j];
			if (v.t != KN_ARR || v.u.a->len == 0) continue;
			for (k = 0; k < v.u.a->len && v.u.a->e[k].t == KN_ACT; k++) ;
			if (k < v.u.a->len) continue;
			p = kcat(b, 0, sizeof(b), "待ち: ");
			p = kshow_at(b, p, sizeof(b), kactv(a), 0);
			p = kcat(b, p, sizeof(b), " の「");
			p = kcat(b, p, sizeof(b), a->c->fields[j]);
			p = kcat(b, p, sizeof(b), "」で ");
			for (k = 0; k < v.u.a->len; k++) {
				if (k) p = kcat(b, p, sizeof(b), "、");
				p = kshow_at(b, p, sizeof(b), v.u.a->e[k], 0);
			}
			kcat(b, p, sizeof(b), " が待っている");
			kt_line(2, b);
			waits++;
		}
	}
	if (waits) kt_line(2, "── 待たされたまま終わった（デッドロックの疑い）");
	p = kcat(b, 0, KT_WIDTH, "── 終わり（処理したメッセージ ");
	p = kcatnum(b, p, sizeof(b), kd.nmsgs);
	kcat(b, p, sizeof(b), " 通）");
	kt_line(3, b);
}

void kerror(const char *what, const char *where)
{
	char b[KT_WIDTH];
	int32 p = kcat(b, 0, sizeof(b), "実行時エラー: ");
	if (where && *where) {
		p = kcat(b, p, sizeof(b), "「");
		p = kcat(b, p, sizeof(b), where);
		p = kcat(b, p, sizeof(b), "」: ");
	}
	p = kcat(b, p, sizeof(b), what);
	if (klastf) {
		p = kcat(b, p, sizeof(b), "（");
		p = kcat(b, p, sizeof(b), klastf->cls < 0 ? "実行部" : klastf->prog->cls[klastf->cls]->name);
		if (klastf->cls >= 0) { p = kcat(b, p, sizeof(b), "の「"); p = kcat(b, p, sizeof(b), klastf->msg); p = kcat(b, p, sizeof(b), "」"); }
		p = kcat(b, p, sizeof(b), " ");
		p = kcatnum(b, p, sizeof(b), klastline);
		kcat(b, p, sizeof(b), " 行目）");
	}
	kprintf("%s\n", b);
	kt_line(2, b);
	kd.state = KR_ERROR;
	kabort = 1;		/* ブラウザ版と同じく、誤りが出たらプログラム全体を止める */
	kdie(kcurself);
}

/* 各文の前に呼ばれる。停止点・1文実行・一時停止ならここで止まる（錠は持ったまま） */
void kstep(struct kfun *f, int32 line, struct kact *self, kv *L)
{
	if (kabort) kdie(self);
	klastf = f; klastline = line;
	if (kd.mode == KM_STEP || f->prog->bp[line]) {
		kd.pf = f; kd.pline = line; kd.pself = self; kd.pL = L;
		kd.state = KR_PAUSED;
		if (self) self->st = KA_STOP;
		kd.gen++;
		wait(kdbgsem);
		if (kabort) kdie(self);
		kd.state = KR_RUN;
		if (self) self->st = KA_RUN;
		kd.pf = NULL;
		kd.gen++;
	}
}

/* ───── 演算 ───── */
int32 knum(kv v, const char *where)
{
	if (v.t != KN_NUM) kerror("数ではない", where);
	return v.u.n;
}
kv kread(kv v, const char *where)
{
	if (v.t == KN_UNSET) kerror("値が入っていない", where);
	return v;
}
kv kadd(kv a, kv b, const char *w) { return kn(knum(a, w) + knum(b, w)); }
kv ksub(kv a, kv b, const char *w) { return kn(knum(a, w) - knum(b, w)); }
kv kmod(kv a, kv b, const char *w)
{
	int32 x = knum(a, w), y = knum(b, w);
	if (y == 0) kerror("0 で割ろうとした", w);
	return kn(((x % y) + y) % y);
}
kv klen(kv a, const char *w)
{
	if (a.t != KN_ARR) kerror("配列ではないので要素数が無い", w);
	return kn(a.u.a->len);
}
static int32 kindex(kv base, kv idx, const char *w)
{
	int32 k;
	if (base.t != KN_ARR) kerror("配列ではない", w);
	k = knum(idx, w);
	if (k < 1 || k > base.u.a->len) kerror("その番目は無い", w);
	return k - 1;
}
kv   kget(kv base, kv idx, const char *w)       { return base.u.a->e[kindex(base, idx, w)]; }
void kset(kv base, kv idx, kv v, const char *w) { base.u.a->e[kindex(base, idx, w)] = v; }

kv *kfield(kv obj, const char *name, const char *w)
{
	int32 i;
	if (obj.t != KN_ACT) kerror("アクターではないので状態を持たない", w);
	for (i = 0; i < obj.u.o->c->nf; i++) {
		if (strcmp(obj.u.o->c->fields[i], name) == 0) return &obj.u.o->f[i];
	}
	kerror("その状態を持たない", w);
	return NULL;
}

/* 等しさ: 配列は両方とも空のときか同じ配列のときだけ等しい（runtime.js の eq） */
int32 keq(kv a, kv b)
{
	if (a.t == KN_ARR && b.t == KN_ARR) return (a.u.a->len == 0 && b.u.a->len == 0) || a.u.a == b.u.a;
	if (a.t != b.t) return 0;
	switch (a.t) {
	case KN_NUM: case KN_BOOL: return a.u.n == b.u.n;
	case KN_STR: return strcmp(a.u.s, b.u.s) == 0;
	case KN_ACT: return a.u.o == b.u.o;
	case KN_NONE: return 1;
	default: return 0;
	}
}
int32 klt(kv a, kv b, const char *wa, const char *wb) { return knum(a, wa) < knum(b, wb); }

void kpush(kv arr, kv v, const char *w)
{
	struct karr *a;
	kv *ne;
	int32 i;
	if (arr.t != KN_ARR) kerror("配列ではないので追加できない", w);
	a = arr.u.a;
	if (a->len == a->cap) {
		ne = (kv *)kalloc(sizeof(kv) * a->cap * 2);
		for (i = 0; i < a->len; i++) ne[i] = a->e[i];
		freemem((char *)a->e, sizeof(kv) * a->cap);
		a->e = ne; a->cap *= 2;
	}
	a->e[a->len++] = v;
}
kv kshift(kv arr, const char *w)
{
	kv v;
	int32 i;
	if (arr.t != KN_ARR) kerror("配列ではない", w);
	if (arr.u.a->len == 0) kerror("空なので先頭を取り出せない", w);
	v = arr.u.a->e[0];
	for (i = 1; i < arr.u.a->len; i++) arr.u.a->e[i - 1] = arr.u.a->e[i];
	arr.u.a->len--;
	return v;
}

/* ───── アクター ───── */
static process kactor(struct kact *a)
{
	struct kmsg *m;
	int32 i;
	intmask im;
	while (TRUE) {
		wait(a->msem);
		wait(klock);
		if (kabort) kdie(a);
		m = a->head;
		a->head = m->next;
		if (a->head == NULL) a->tail = NULL;
		a->st = KA_RUN; a->cur = m->msg; kcurself = a; kd.gen++;
		for (i = 0; i < a->c->nh; i++) {
			if (strcmp(a->c->h[i].msg, m->msg) == 0) break;
		}
		if (i == a->c->nh) kerror("このメッセージを受け取る受信節が無い", m->msg);
		a->c->h[i].fn(a, m->hasarg ? m->arg : knone());
		freemem((char *)m, sizeof(struct kmsg));
		kd.nmsgs++;
		a->st = KA_IDLE; a->cur = NULL; kcurself = NULL; kd.gen++;
		if (--kpending == 0) kfinish();
		signal(klock);
		/* 同じ優先度の他のアクターに順番を譲る（Xinu の resched は同じ優先度なら待ち行列の後ろへ回す） */
		im = disable();
		resched();
		restore(im);
	}
	return OK;
}

kv knew(struct kclass *c)
{
	struct kact *a = (struct kact *)kalloc(sizeof(struct kact));
	int32 i;
	a->c = c;
	a->id = ++c->count;
	a->f = (kv *)kalloc(sizeof(kv) * (c->nf ? c->nf : 1));
	for (i = 0; i < c->nf; i++) a->f[i] = knone();
	a->head = a->tail = NULL;
	a->st = KA_IDLE; a->cur = NULL;
	a->msem = semcreate(0);
	if (a->msem == SYSERR) kerror("セマフォが足りない（アクターを作れない）", c->name);
	a->pid = create((void *)kactor, KSTK, KPRIO, "kactor", 1, a);
	if (a->pid == SYSERR) kerror("プロセスが足りない（アクターを作れない）", c->name);
	if (kd.nact < KMAXACT) kd.act[kd.nact++] = a;
	kd.gen++;
	if (c->init) c->init(a);
	resume(a->pid);
	return kactv(a);
}

void ksend(kv target, const char *msg, kv arg, int32 hasarg)
{
	struct kmsg *m;
	struct kact *a;
	if (target.t != KN_ACT) kerror("アクターではないので送れない", msg);
	a = target.u.o;
	if (kd.trace) {
		char b[KT_WIDTH];
		int32 p = kcat(b, 0, sizeof(b), "→ ");
		p = kcurself ? kshow_at(b, p, sizeof(b), kactv(kcurself), 0) : kcat(b, p, sizeof(b), "実行部");
		p = kcat(b, p, sizeof(b), " から ");
		p = kshow_at(b, p, sizeof(b), target, 0);
		p = kcat(b, p, sizeof(b), " へ「");
		p = kcat(b, p, sizeof(b), msg);
		p = kcat(b, p, sizeof(b), "」");
		if (hasarg) {
			p = kcat(b, p, sizeof(b), "（");
			p = kshow_at(b, p, sizeof(b), arg, 0);
			p = kcat(b, p, sizeof(b), "）");
		}
		kt_line(1, b);
	}
	m = (struct kmsg *)kalloc(sizeof(struct kmsg));
	m->msg = msg; m->arg = arg; m->hasarg = hasarg; m->next = NULL;
	if (a->tail) a->tail->next = m; else a->head = m;
	a->tail = m;
	kpending++;
	kd.gen++;
	signal(a->msem);
}

void ksendall(kv arr, const char *msg, kv arg, int32 hasarg, const char *w)
{
	int32 i;
	if (arr.t != KN_ARR) kerror("配列ではないので全員に送れない", w);
	for (i = 0; i < arr.u.a->len; i++) ksend(arr.u.a->e[i], msg, arg, hasarg);
}

/* 並べて表示: 値と値が隣り合うときだけ空白を入れる（「…」の前後には入れない） */
void kdisp(int32 n, const int32 *lit, const kv *vals)
{
	char b[KT_WIDTH];
	int32 i, p = 0;
	b[0] = '\0';
	for (i = 0; i < n; i++) {
		if (i && !lit[i] && !lit[i - 1]) p = kcat(b, p, sizeof(b), " ");
		p = kshow_at(b, p, sizeof(b), vals[i], 0);
	}
	kprintf("%s\n", b);
	kt_line(0, b);
}

/* ───── 走らせる・止める（デバッガの画面から呼ぶ） ───── */
static process krun_body(struct kprogram *p)
{
	wait(klock);
	kcurself = NULL;
	p->body();
	if (--kpending == 0) kfinish();
	krunner = SYSERR;
	signal(klock);
	return OK;
}

/* 前の実行のアクターを片付ける。止まっている文があれば先に死なせる */
static void kcleanup(void)
{
	int32 i, tries;
	if (klock == SYSERR) return;
	kabort = 1;
	if (kd.state == KR_PAUSED) signal(kdbgsem);
	/* 走っている受信節が次の文で止まるのを待つ */
	for (tries = 0; tries < 200; tries++) {
		int32 busy = (krunner != SYSERR && kd.state == KR_RUN);
		for (i = 0; i < kd.nact; i++) {
			if (kd.act[i]->st == KA_RUN || kd.act[i]->st == KA_STOP) busy = 1;
		}
		if (!busy) break;
		sleepms(10);
	}
	for (i = 0; i < kd.nact; i++) {
		struct kact *a = kd.act[i];
		if (a->st != KA_DEAD && a->pid != SYSERR) kill(a->pid);
		a->st = KA_DEAD;
		if (a->msem != SYSERR) semdelete(a->msem);
		a->msem = SYSERR;
	}
	if (krunner != SYSERR) { kill(krunner); krunner = SYSERR; }
	semreset(klock, 1);
	semreset(kdbgsem, 0);
}

void kd_run(struct kprogram *p)
{
	int32 i;
	if (klock == SYSERR) {
		klock = semcreate(1);
		kdbgsem = semcreate(0);
	} else {
		kcleanup();
	}
	for (i = 0; i < p->ncls; i++) p->cls[i]->count = 0;
	kd.prog = p;
	kd.nact = 0;
	kd.nmsgs = 0;
	kd.pf = NULL;
	kd.state = KR_RUN;
	kabort = 0;
	klastf = NULL;
	kpending = 1;
	kcurself = NULL;
	{
		char b[KT_WIDTH];
		int32 q = kcat(b, 0, sizeof(b), "── 「");
		q = kcat(b, q, sizeof(b), p->name);
		kcat(b, q, sizeof(b), "」を実行します");
		kt_line(3, b);
	}
	krunner = create((void *)krun_body, KSTK, KPRIO, "krunner", 1, p);
	resume(krunner);
}

void kd_continue(void) { if (kd.state == KR_PAUSED) { kd.mode = KM_RUN; signal(kdbgsem); } }
void kd_step(void)     { if (kd.state == KR_PAUSED) { kd.mode = KM_STEP; signal(kdbgsem); } }
void kd_pause(void)    { if (kd.state == KR_RUN) kd.mode = KM_STEP; }
void kd_abort(void)
{
	if (kd.state == KR_RUN || kd.state == KR_PAUSED) {
		kcleanup();
		kd.state = KR_IDLE;
		kd.pf = NULL;
		kt_line(3, "── 中止しました");
	}
}
