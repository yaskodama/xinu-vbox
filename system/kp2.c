/* kp2.c - ことのはから k2xinu.mjs で生成。手で直さないこと */
/* 元: ユークリッドの互除法.txt */
#include <xinu.h>
#include "krt.h"

extern struct kprogram kp2_prog;
static struct kfun KF[3];
static struct kclass kcls0;

static void kinit0(struct kact *self) {
}

static void kh0_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[0], 4, self, L);
	{ kv v = kget(kread(L[0], "組"), kn(1), "組の 1 番目");
	  self->f[0] = v;
	}
	kstep(&KF[0], 5, self, L);
	{ kv v = kget(kread(L[0], "組"), kn(2), "組の 2 番目");
	  self->f[1] = v;
	}
	kstep(&KF[0], 6, self, L);
	{ static const int32 lit[6] = { 0, 1, 0, 1, 0, 1 };
	  kv vals[6];
	  vals[0] = kactv(self);
	  vals[1] = ks("：");
	  vals[2] = self->f[0];
	  vals[3] = ks("と");
	  vals[4] = self->f[1];
	  vals[5] = ks("の最大公約数を求める");
	  kdisp(6, lit, vals); }
	kstep(&KF[0], 7, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "割れ", a, 0);
	}
}

static void kh0_1(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[1], 10, self, L);
	if (keq(self->f[1], kn(0))) {
		kstep(&KF[1], 11, self, L);
		{ static const int32 lit[3] = { 0, 1, 0 };
		  kv vals[3];
		  vals[0] = kactv(self);
		  vals[1] = ks("：答えは");
		  vals[2] = self->f[0];
		  kdisp(3, lit, vals); }
	} else {
		kstep(&KF[1], 13, self, L);
		{ kv v = kmod(self->f[0], self->f[1], "（割られる数 を 割る数 で割った余り）");
		  self->f[2] = v;
		}
		kstep(&KF[1], 14, self, L);
		{ static const int32 lit[7] = { 0, 1, 0, 1, 0, 1, 0 };
		  kv vals[7];
		  vals[0] = kactv(self);
		  vals[1] = ks("：");
		  vals[2] = self->f[0];
		  vals[3] = ks("÷");
		  vals[4] = self->f[1];
		  vals[5] = ks("の余りは");
		  vals[6] = self->f[2];
		  kdisp(7, lit, vals); }
		kstep(&KF[1], 15, self, L);
		{ kv v = self->f[1];
		  self->f[0] = v;
		}
		kstep(&KF[1], 16, self, L);
		{ kv v = self->f[2];
		  self->f[1] = v;
		}
		kstep(&KF[1], 17, self, L);
		{ kv a = knone();
		  ksend(kactv(self), "割れ", a, 0);
		}
	}
}

static const char *kf0[] = { "割られる数", "割る数", "余り" };
static const struct khent kht0[] = { { "求めよ", kh0_0 }, { "割れ", kh0_1 } };
static struct kclass kcls0 = { "計算係", 3, kf0, kinit0, 2, kht0, 0 };

static void kbody(void) {
	struct kact *self = NULL; (void)self;
	kv L[3];
	int32 i;
	(void)L;
	for (i = 0; i < 3; i++) L[i].t = KN_UNSET;
	kstep(&KF[2], 23, self, L);
	L[0] = knew(&kcls0);
	kstep(&KF[2], 24, self, L);
	L[1] = knew(&kcls0);
	kstep(&KF[2], 25, self, L);
	L[2] = knewarr();
	kstep(&KF[2], 26, self, L);
	{ kv arr = kread(L[2], "組");
	  kpush(arr, kn(1071), "組");
	  kpush(arr, kn(1029), "組");
	}
	kstep(&KF[2], 27, self, L);
	{ kv a = kread(L[2], "組");
	  ksend(kread(L[0], "一号"), "求めよ", a, 1);
	}
	kstep(&KF[2], 28, self, L);
	{ kv v = knewarr();
	  L[2] = v;
	}
	kstep(&KF[2], 29, self, L);
	{ kv arr = kread(L[2], "組");
	  kpush(arr, kn(240), "組");
	  kpush(arr, kn(46), "組");
	}
	kstep(&KF[2], 30, self, L);
	{ kv a = kread(L[2], "組");
	  ksend(kread(L[1], "二号"), "求めよ", a, 1);
	}
}

static const char *KS0[] = { "組" };
static const char *KS1[] = { "" };
static const char *KS2[] = { "一号", "二号", "組" };
static struct kfun KF[3] = {
	{ &kp2_prog, 0, "求めよ", 3, 8, 1, KS0 },
	{ &kp2_prog, 0, "割れ", 9, 19, 0, KS1 },
	{ &kp2_prog, -1, "実行部", 22, 31, 3, KS2 },
};

static const char *KL[32] = {
	"「計算係」というアクターを定義する。",
	"    状態は 割られる数、割る数、余り。",
	"    「求めよ」と 組 を受け取ったとき、",
	"        割られる数 は 組の 1 番目。",
	"        割る数 は 組の 2 番目。",
	"        自分 と 「：」 と 割られる数 と 「と」 と 割る数 と 「の最大公約数を求める」 を表示する。",
	"        自分 に「割れ」を送る。",
	"    以上。",
	"    「割れ」を受け取ったとき、",
	"        もし 割る数 が 0 ならば、",
	"            自分 と 「：答えは」 と 割られる数 を表示する。",
	"        そうでなければ、",
	"            余り は （割られる数 を 割る数 で割った余り）。",
	"            自分 と 「：」 と 割られる数 と 「÷」 と 割る数 と 「の余りは」 と 余り を表示する。",
	"            割られる数 は 割る数。",
	"            割る数 は 余り。",
	"            自分 に「割れ」を送る。",
	"        以上。",
	"    以上。",
	"定義を終わる。",
	"",
	"実行を始める。",
	"    一号 は 「計算係」の新しいアクター。",
	"    二号 は 「計算係」の新しいアクター。",
	"    組 は 空の配列。",
	"    組 に 1071 と 1029 を追加する。",
	"    一号 に「求めよ」と 組 を送る。",
	"    組 は 空の配列。",
	"    組 に 240 と 46 を追加する。",
	"    二号 に「求めよ」と 組 を送る。",
	"実行を終わる。",
	"",
};
static const unsigned char KST[33] = { 0,0,0,0,1,1,1,1,0,0,1,1,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0 };
static unsigned char KBP[33];
static const char *KSRC[27] = {
	"■ ユークリッドの互除法",
	"※ 2つの数の最大公約数を、「割った余り」を求めることを繰り返して計算する。",
	"※ 計算係は、自分自身にメッセージを送ることで繰り返す。2つの計算係が並行して動くので、",
	"※ 「動く順」の種を変えると、2組の途中経過が混ざる順番が変わる（答えは変わらない）。",
	"計算係というアクターを定義する。",
	"計算係は割られる数と割る数と余りを持つ。",
	"",
	"計算係が「求めよ」というメッセージと組を受け取ったとき、",
	"割られる数を組の1番目に変更し、割る数を組の2番目に変更する。",
	"自分自身と「：」と割られる数と「と」と割る数と「の最大公約数を求める」という文字列を表示する。",
	"自分自身に「割れ」というメッセージを送る。",
	"",
	"計算係が「割れ」というメッセージを受け取ったとき、",
	"割る数が0ならば、自分自身と「：答えは」と割られる数を表示する。",
	"そうでなければ、次のことを行う。",
	"余りを（割られる数を割る数で割った余り）に変更する。",
	"自分自身と「：」と割られる数と「÷」と割る数と「の余りは」と余りを表示する。",
	"割られる数を割る数に変更し、割る数を余りに変更し、自分自身に「割れ」というメッセージを送る。",
	"以上。",
	"これで計算係の定義を終わる。",
	"",
	"実行を始める。",
	"計算係というアクターを1つ生成し、一号と名付ける。",
	"計算係というアクターを1つ生成し、二号と名付ける。",
	"空の配列を用意し、組と名付け、1071と1029を組の末尾に追加し、一号に「求めよ」というメッセージと組を送る。",
	"空の配列を用意し、組と名付け、240と46を組の末尾に追加し、二号に「求めよ」というメッセージと組を送る。",
	"これで実行を終わる。",
};
static struct kclass *KC[1] = { &kcls0 };
static const int32 KCL[1] = { 1 };
static const int32 KCE[1] = { 20 };
struct kprogram kp2_prog = { "ユークリッドの互除法", 1, KC, KCL, KCE, kbody, 22, 31,
	32, KL, KST, KBP, 27, KSRC, 3, KF };
