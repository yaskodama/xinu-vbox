/* kp1.c - ことのはから k2xinu.mjs で生成。手で直さないこと */
/* 元: ハノイの塔.txt */
#include <xinu.h>
#include "krt.h"

extern struct kprogram kp1_prog;
static struct kfun KF[4];
static struct kclass kcls0;
static struct kclass kcls1;

static void kinit0(struct kact *self) {
	self->f[5] = kn(0);
}

static void kh0_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[0], 7, self, L);
	{ kv v = kget(kread(L[0], "仕事"), kn(1), "仕事の 1 番目");
	  self->f[0] = v;
	}
	kstep(&KF[0], 8, self, L);
	{ kv v = kget(kread(L[0], "仕事"), kn(2), "仕事の 2 番目");
	  self->f[1] = v;
	}
	kstep(&KF[0], 9, self, L);
	{ kv v = kget(kread(L[0], "仕事"), kn(3), "仕事の 3 番目");
	  self->f[2] = v;
	}
	kstep(&KF[0], 10, self, L);
	{ kv v = kget(kread(L[0], "仕事"), kn(4), "仕事の 4 番目");
	  self->f[3] = v;
	}
	kstep(&KF[0], 11, self, L);
	{ kv v = kget(kread(L[0], "仕事"), kn(5), "仕事の 5 番目");
	  self->f[4] = v;
	}
	kstep(&KF[0], 12, self, L);
	if (keq(self->f[0], kn(1))) {
		kstep(&KF[0], 13, self, L);
		{ static const int32 lit[5] = { 1, 0, 1, 0, 1 };
		  kv vals[5];
		  vals[0] = ks("円盤1を");
		  vals[1] = self->f[1];
		  vals[2] = ks("から");
		  vals[3] = self->f[2];
		  vals[4] = ks("へ移す");
		  kdisp(5, lit, vals); }
		kstep(&KF[0], 14, self, L);
		{ kv a = knone();
		  ksend(self->f[4], "済んだ", a, 0);
		}
	} else {
		kstep(&KF[0], 16, self, L);
		{ kv v = kn(1);
		  self->f[5] = v;
		}
		kstep(&KF[0], 17, self, L);
		self->f[6] = knew(&kcls0);
		kstep(&KF[0], 18, self, L);
		{ kv v = knewarr();
		  self->f[7] = v;
		}
		kstep(&KF[0], 19, self, L);
		{ kv arr = self->f[7];
		  kpush(arr, ksub(self->f[0], kn(1), "（枚数 引く 1）"), "依頼");
		  kpush(arr, self->f[1], "依頼");
		  kpush(arr, self->f[3], "依頼");
		  kpush(arr, self->f[2], "依頼");
		  kpush(arr, kactv(self), "依頼");
		}
		kstep(&KF[0], 20, self, L);
		{ kv a = self->f[7];
		  ksend(self->f[6], "移せ", a, 1);
		}
	}
}

static void kh0_1(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[1], 24, self, L);
	if (keq(self->f[5], kn(1))) {
		kstep(&KF[1], 25, self, L);
		{ static const int32 lit[7] = { 1, 0, 1, 0, 1, 0, 1 };
		  kv vals[7];
		  vals[0] = ks("円盤");
		  vals[1] = self->f[0];
		  vals[2] = ks("を");
		  vals[3] = self->f[1];
		  vals[4] = ks("から");
		  vals[5] = self->f[2];
		  vals[6] = ks("へ移す");
		  kdisp(7, lit, vals); }
		kstep(&KF[1], 26, self, L);
		{ kv v = kn(2);
		  self->f[5] = v;
		}
		kstep(&KF[1], 27, self, L);
		{ kv v = knewarr();
		  self->f[7] = v;
		}
		kstep(&KF[1], 28, self, L);
		{ kv arr = self->f[7];
		  kpush(arr, ksub(self->f[0], kn(1), "（枚数 引く 1）"), "依頼");
		  kpush(arr, self->f[3], "依頼");
		  kpush(arr, self->f[2], "依頼");
		  kpush(arr, self->f[1], "依頼");
		  kpush(arr, kactv(self), "依頼");
		}
		kstep(&KF[1], 29, self, L);
		{ kv a = self->f[7];
		  ksend(self->f[6], "移せ", a, 1);
		}
	} else {
		kstep(&KF[1], 31, self, L);
		{ kv a = knone();
		  ksend(self->f[4], "済んだ", a, 0);
		}
	}
}

static const char *kf0[] = { "枚数", "元", "先", "経由", "依頼主", "段階", "子", "依頼" };
static const struct khent kht0[] = { { "移せ", kh0_0 }, { "済んだ", kh0_1 } };
static struct kclass kcls0 = { "移し係", 8, kf0, kinit0, 2, kht0, 0 };

static void kinit1(struct kact *self) {
}

static void kh1_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[2], 39, self, L);
	{ static const int32 lit[1] = { 1 };
	  kv vals[1];
	  vals[0] = ks("すべての円盤を移し終えました");
	  kdisp(1, lit, vals); }
}

static const char *kf1[] = { "枚数" };
static const struct khent kht1[] = { { "済んだ", kh1_0 } };
static struct kclass kcls1 = { "見届け係", 1, kf1, kinit1, 1, kht1, 0 };

static void kbody(void) {
	struct kact *self = NULL; (void)self;
	kv L[3];
	int32 i;
	(void)L;
	for (i = 0; i < 3; i++) L[i].t = KN_UNSET;
	kstep(&KF[3], 44, self, L);
	L[0] = knew(&kcls1);
	kstep(&KF[3], 45, self, L);
	L[1] = knew(&kcls0);
	kstep(&KF[3], 46, self, L);
	L[2] = knewarr();
	kstep(&KF[3], 47, self, L);
	{ kv arr = kread(L[2], "依頼");
	  kpush(arr, kn(4), "依頼");
	  kpush(arr, ks("A"), "依頼");
	  kpush(arr, ks("C"), "依頼");
	  kpush(arr, ks("B"), "依頼");
	  kpush(arr, kread(L[0], "見届け役"), "依頼");
	}
	kstep(&KF[3], 48, self, L);
	{ kv a = kread(L[2], "依頼");
	  ksend(kread(L[1], "頭"), "移せ", a, 1);
	}
}

static const char *KS0[] = { "仕事" };
static const char *KS1[] = { "" };
static const char *KS2[] = { "" };
static const char *KS3[] = { "見届け役", "頭", "依頼" };
static struct kfun KF[4] = {
	{ &kp1_prog, 0, "移せ", 6, 22, 1, KS0 },
	{ &kp1_prog, 0, "済んだ", 23, 33, 0, KS1 },
	{ &kp1_prog, 1, "済んだ", 38, 40, 0, KS2 },
	{ &kp1_prog, -1, "実行部", 43, 49, 3, KS3 },
};

static const char *KL[50] = {
	"「移し係」というアクターを定義する。",
	"    状態は 枚数、元、先、経由、依頼主、段階、子、依頼。",
	"    初期状態は",
	"        段階 は 0。",
	"    以上。",
	"    「移せ」と 仕事 を受け取ったとき、",
	"        枚数 は 仕事の 1 番目。",
	"        元 は 仕事の 2 番目。",
	"        先 は 仕事の 3 番目。",
	"        経由 は 仕事の 4 番目。",
	"        依頼主 は 仕事の 5 番目。",
	"        もし 枚数 が 1 ならば、",
	"            「円盤1を」 と 元 と 「から」 と 先 と 「へ移す」 を表示する。",
	"            依頼主 に「済んだ」を送る。",
	"        そうでなければ、",
	"            段階 は 1。",
	"            子 は 「移し係」の新しいアクター。",
	"            依頼 は 空の配列。",
	"            依頼 に （枚数 引く 1） と 元 と 経由 と 先 と 自分 を追加する。",
	"            子 に「移せ」と 依頼 を送る。",
	"        以上。",
	"    以上。",
	"    「済んだ」を受け取ったとき、",
	"        もし 段階 が 1 ならば、",
	"            「円盤」 と 枚数 と 「を」 と 元 と 「から」 と 先 と 「へ移す」 を表示する。",
	"            段階 は 2。",
	"            依頼 は 空の配列。",
	"            依頼 に （枚数 引く 1） と 経由 と 先 と 元 と 自分 を追加する。",
	"            子 に「移せ」と 依頼 を送る。",
	"        そうでなければ、",
	"            依頼主 に「済んだ」を送る。",
	"        以上。",
	"    以上。",
	"定義を終わる。",
	"",
	"「見届け係」というアクターを定義する。",
	"    状態は 枚数。",
	"    「済んだ」を受け取ったとき、",
	"        「すべての円盤を移し終えました」 を表示する。",
	"    以上。",
	"定義を終わる。",
	"",
	"実行を始める。",
	"    見届け役 は 「見届け係」の新しいアクター。",
	"    頭 は 「移し係」の新しいアクター。",
	"    依頼 は 空の配列。",
	"    依頼 に 4 と 「A」 と 「C」 と 「B」 と 見届け役 を追加する。",
	"    頭 に「移せ」と 依頼 を送る。",
	"実行を終わる。",
	"",
};
static const unsigned char KST[51] = { 0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0,0 };
static unsigned char KBP[51];
static const char *KSRC[38] = {
	"■ ハノイの塔",
	"※ 「n枚の円盤を、元の棒から先の棒へ、経由の棒を使って移す」仕事を、移し係というアクターに頼む。",
	"※ 移し係は、上のn−1枚を自分の子（もう一つの移し係）に頼み、「済んだ」という返事を待ってから",
	"※ いちばん下の円盤を動かし、残りのn−1枚をもう一度子に頼む。",
	"※ 再帰呼び出しの代わりに「頼む → 返事を待つ」を使うので、動く順をどう変えても手順は正しい順に出る。",
	"移し係というアクターを定義する。",
	"移し係は枚数と元と先と経由と依頼主と段階と子と依頼を持つ。",
	"段階の初期値は0とする。",
	"",
	"移し係が「移せ」というメッセージと仕事を受け取ったとき、",
	"枚数を仕事の1番目に変更し、元を仕事の2番目に変更し、先を仕事の3番目に変更する。",
	"経由を仕事の4番目に変更し、依頼主を仕事の5番目に変更する。",
	"枚数が1ならば、「円盤1を」と元と「から」と先と「へ移す」を表示し、依頼主に「済んだ」というメッセージを送る。",
	"そうでなければ、次のことを行う。",
	"段階を1に変更し、移し係というアクターを1つ生成し、子と名付ける。",
	"空の配列を用意し、依頼と名付け、（枚数から1を引いた数）と元と経由と先と自分自身を依頼の末尾に追加し、子に「移せ」というメッセージと依頼を送る。",
	"以上。",
	"",
	"移し係が「済んだ」というメッセージを受け取ったとき、",
	"段階が1ならば、次のことを行う。",
	"「円盤」と枚数と「を」と元と「から」と先と「へ移す」を表示し、段階を2に変更する。",
	"空の配列を用意し、依頼と名付け、（枚数から1を引いた数）と経由と先と元と自分自身を依頼の末尾に追加し、子に「移せ」というメッセージと依頼を送る。",
	"以上。",
	"そうでなければ、依頼主に「済んだ」というメッセージを送る。",
	"これで移し係の定義を終わる。",
	"",
	"見届け係というアクターを定義する。",
	"見届け係は枚数を持つ。",
	"",
	"見届け係が「済んだ」というメッセージを受け取ったとき、",
	"「すべての円盤を移し終えました」という文字列を表示する。",
	"これで見届け係の定義を終わる。",
	"",
	"実行を始める。",
	"見届け係というアクターを1つ生成し、見届け役と名付ける。",
	"移し係というアクターを1つ生成し、頭と名付ける。",
	"空の配列を用意し、依頼と名付け、4と「A」と「C」と「B」と見届け役を依頼の末尾に追加し、頭に「移せ」というメッセージと依頼を送る。",
	"これで実行を終わる。",
};
static struct kclass *KC[2] = { &kcls0, &kcls1 };
static const int32 KCL[2] = { 1, 36 };
static const int32 KCE[2] = { 34, 41 };
struct kprogram kp1_prog = { "ハノイの塔", 2, KC, KCL, KCE, kbody, 43, 49,
	50, KL, KST, KBP, 38, KSRC, 4, KF };
