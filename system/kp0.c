/* kp0.c - ことのはから k2xinu.mjs で生成。手で直さないこと */
/* 元: Xinuの挨拶.txt */
#include <xinu.h>
#include "krt.h"

extern struct kprogram kp0_prog;
static struct kfun KF[4];
static struct kclass kcls0;
static struct kclass kcls1;

static void kinit0(struct kact *self) {
	self->f[2] = kn(0);
}

static void kh0_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[0], 7, self, L);
	{ kv v = kget(kread(L[0], "指示"), kn(1), "指示の 1 番目");
	  self->f[0] = v;
	}
	kstep(&KF[0], 8, self, L);
	{ kv v = kget(kread(L[0], "指示"), kn(2), "指示の 2 番目");
	  self->f[1] = v;
	}
	kstep(&KF[0], 9, self, L);
	{ kv v = kget(kread(L[0], "指示"), kn(3), "指示の 3 番目");
	  self->f[3] = v;
	}
	kstep(&KF[0], 10, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "挨拶", a, 0);
	}
}

static void kh0_1(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[1], 13, self, L);
	self->f[2] = kadd(self->f[2], kn(1), "済んだ回数");
	kstep(&KF[1], 14, self, L);
	{ static const int32 lit[7] = { 1, 0, 1, 0, 1, 0, 1 };
	  kv vals[7];
	  vals[0] = ks("[");
	  vals[1] = self->f[0];
	  vals[2] = ks("] hello from Xinu! (");
	  vals[3] = self->f[2];
	  vals[4] = ks("/");
	  vals[5] = self->f[1];
	  vals[6] = ks(")");
	  kdisp(7, lit, vals); }
	kstep(&KF[1], 15, self, L);
	if (klt(self->f[2], self->f[1], "済んだ回数", "回数")) {
		kstep(&KF[1], 16, self, L);
		{ kv a = knone();
		  ksend(kactv(self), "挨拶", a, 0);
		}
	} else {
		kstep(&KF[1], 18, self, L);
		{ kv a = knone();
		  ksend(self->f[3], "終わった", a, 0);
		}
	}
}

static const char *kf0[] = { "呼び名", "回数", "済んだ回数", "報告先" };
static const struct khent kht0[] = { { "始め", kh0_0 }, { "挨拶", kh0_1 } };
static struct kclass kcls0 = { "挨拶係", 4, kf0, kinit0, 2, kht0, 0 };

static void kinit1(struct kact *self) {
	self->f[0] = kn(0);
}

static void kh1_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[2], 29, self, L);
	self->f[0] = kadd(self->f[0], kn(1), "報告数");
	kstep(&KF[2], 30, self, L);
	if (keq(self->f[0], kn(2))) {
		kstep(&KF[2], 31, self, L);
		{ static const int32 lit[1] = { 1 };
		  kv vals[1];
		  vals[0] = ks("=== Sample finished, starting shell ===");
		  kdisp(1, lit, vals); }
	}
}

static const char *kf1[] = { "報告数" };
static const struct khent kht1[] = { { "終わった", kh1_0 } };
static struct kclass kcls1 = { "見届け係", 1, kf1, kinit1, 1, kht1, 0 };

static void kbody(void) {
	struct kact *self = NULL; (void)self;
	kv L[5];
	int32 i;
	(void)L;
	for (i = 0; i < 5; i++) L[i].t = KN_UNSET;
	kstep(&KF[3], 37, self, L);
	{ static const int32 lit[1] = { 1 };
	  kv vals[1];
	  vals[0] = ks("=== Sample: two greeter processes running concurrently ===");
	  kdisp(1, lit, vals); }
	kstep(&KF[3], 38, self, L);
	L[0] = knew(&kcls1);
	kstep(&KF[3], 39, self, L);
	L[1] = knew(&kcls0);
	kstep(&KF[3], 40, self, L);
	L[2] = knew(&kcls0);
	kstep(&KF[3], 41, self, L);
	L[3] = knewarr();
	kstep(&KF[3], 42, self, L);
	{ kv arr = kread(L[3], "甲の指示");
	  kpush(arr, ks("Alice"), "甲の指示");
	  kpush(arr, kn(3), "甲の指示");
	  kpush(arr, kread(L[0], "見届け役"), "甲の指示");
	}
	kstep(&KF[3], 43, self, L);
	{ kv a = kread(L[3], "甲の指示");
	  ksend(kread(L[1], "甲"), "始め", a, 1);
	}
	kstep(&KF[3], 44, self, L);
	L[4] = knewarr();
	kstep(&KF[3], 45, self, L);
	{ kv arr = kread(L[4], "乙の指示");
	  kpush(arr, ks("Bob"), "乙の指示");
	  kpush(arr, kn(3), "乙の指示");
	  kpush(arr, kread(L[0], "見届け役"), "乙の指示");
	}
	kstep(&KF[3], 46, self, L);
	{ kv a = kread(L[4], "乙の指示");
	  ksend(kread(L[2], "乙"), "始め", a, 1);
	}
}

static const char *KS0[] = { "指示" };
static const char *KS1[] = { "" };
static const char *KS2[] = { "" };
static const char *KS3[] = { "見届け役", "甲", "乙", "甲の指示", "乙の指示" };
static struct kfun KF[4] = {
	{ &kp0_prog, 0, "始め", 6, 11, 1, KS0 },
	{ &kp0_prog, 0, "挨拶", 12, 20, 0, KS1 },
	{ &kp0_prog, 1, "終わった", 28, 33, 0, KS2 },
	{ &kp0_prog, -1, "実行部", 36, 47, 5, KS3 },
};

static const char *KL[48] = {
	"「挨拶係」というアクターを定義する。",
	"    状態は 呼び名、回数、済んだ回数、報告先。",
	"    初期状態は",
	"        済んだ回数 は 0。",
	"    以上。",
	"    「始め」と 指示 を受け取ったとき、",
	"        呼び名 は 指示の 1 番目。",
	"        回数 は 指示の 2 番目。",
	"        報告先 は 指示の 3 番目。",
	"        自分 に「挨拶」を送る。",
	"    以上。",
	"    「挨拶」を受け取ったとき、",
	"        済んだ回数 は 済んだ回数 足す 1。",
	"        「[」 と 呼び名 と 「] hello from Xinu! (」 と 済んだ回数 と 「/」 と 回数 と 「)」 を表示する。",
	"        もし 済んだ回数 が 回数 より小さい ならば、",
	"            自分 に「挨拶」を送る。",
	"        そうでなければ、",
	"            報告先 に「終わった」を送る。",
	"        以上。",
	"    以上。",
	"定義を終わる。",
	"",
	"「見届け係」というアクターを定義する。",
	"    状態は 報告数。",
	"    初期状態は",
	"        報告数 は 0。",
	"    以上。",
	"    「終わった」を受け取ったとき、",
	"        報告数 は 報告数 足す 1。",
	"        もし 報告数 が 2 ならば、",
	"            「=== Sample finished, starting shell ===」 を表示する。",
	"        以上。",
	"    以上。",
	"定義を終わる。",
	"",
	"実行を始める。",
	"    「=== Sample: two greeter processes running concurrently ===」 を表示する。",
	"    見届け役 は 「見届け係」の新しいアクター。",
	"    甲 は 「挨拶係」の新しいアクター。",
	"    乙 は 「挨拶係」の新しいアクター。",
	"    甲の指示 は 空の配列。",
	"    甲の指示 に 「Alice」 と 3 と 見届け役 を追加する。",
	"    甲 に「始め」と 甲の指示 を送る。",
	"    乙の指示 は 空の配列。",
	"    乙の指示 に 「Bob」 と 3 と 見届け役 を追加する。",
	"    乙 に「始め」と 乙の指示 を送る。",
	"実行を終わる。",
	"",
};
static const unsigned char KST[49] = { 0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0 };
static unsigned char KBP[49];
static const char *KSRC[35] = {
	"■ 二人の挨拶係（PC Xinu の見本 system/main.c をことのはで書き換えたもの）",
	"※ Xinu では main が greeter プロセスを2つ作り（create）、走らせ（resume）、2.5秒待ってから終わりを告げる。",
	"※ ことのはでは greeter を挨拶係というアクターにし、1回挨拶するたびに自分へ「挨拶」を送り直す。",
	"※ こうすると2人の挨拶が交互に混ざる。待ち時間（sleepms）の代わりに、見届け係が2人の「終わった」を数えてから終わりを告げる。",
	"挨拶係というアクターを定義する。",
	"挨拶係は呼び名と回数と済んだ回数と報告先を持つ。",
	"済んだ回数の初期値は0とする。",
	"",
	"挨拶係が「始め」というメッセージと指示を受け取ったとき、",
	"呼び名を指示の1番目に変更し、回数を指示の2番目に変更し、報告先を指示の3番目に変更する。",
	"自分に「挨拶」というメッセージを送る。",
	"",
	"挨拶係が「挨拶」というメッセージを受け取ったとき、",
	"済んだ回数に1を加え、「[」と呼び名と「] hello from Xinu! (」と済んだ回数と「/」と回数と「)」を表示する。",
	"済んだ回数が回数より小さければ、自分に「挨拶」というメッセージを送る。",
	"そうでなければ、報告先に「終わった」というメッセージを送る。",
	"これで挨拶係の定義を終わる。",
	"",
	"見届け係というアクターを定義する。",
	"見届け係は報告数を持つ。",
	"報告数の初期値は0とする。",
	"",
	"見届け係が「終わった」というメッセージを受け取ったとき、",
	"報告数に1を加える。",
	"報告数が2ならば、「=== Sample finished, starting shell ===」という文字列を表示する。",
	"これで見届け係の定義を終わる。",
	"",
	"実行を始める。",
	"「=== Sample: two greeter processes running concurrently ===」という文字列を表示する。",
	"見届け係というアクターを1つ生成し、見届け役と名付ける。",
	"挨拶係というアクターを1つ生成し、甲と名付ける。",
	"挨拶係というアクターを1つ生成し、乙と名付ける。",
	"空の配列を用意し、甲の指示と名付け、「Alice」と3と見届け役を甲の指示の末尾に追加し、甲に「始め」というメッセージと甲の指示を送る。",
	"空の配列を用意し、乙の指示と名付け、「Bob」と3と見届け役を乙の指示の末尾に追加し、乙に「始め」というメッセージと乙の指示を送る。",
	"これで実行を終わる。",
};
static struct kclass *KC[2] = { &kcls0, &kcls1 };
static const int32 KCL[2] = { 1, 23 };
static const int32 KCE[2] = { 21, 34 };
struct kprogram kp0_prog = { "Xinuの挨拶", 2, KC, KCL, KCE, kbody, 36, 47,
	48, KL, KST, KBP, 35, KSRC, 4, KF };
