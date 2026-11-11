/* kp5.c - ことのはから k2xinu.mjs で生成。手で直さないこと */
/* 元: 哲学者_文章形式.txt */
#include <xinu.h>
#include "krt.h"

extern struct kprogram kp5_prog;
static struct kfun KF[5];
static struct kclass kcls0;
static struct kclass kcls1;

static void kinit0(struct kact *self) {
	self->f[0] = kn(0);
	self->f[1] = kb(0);
	self->f[2] = knewarr();
}

static void kh0_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[0], 9, self, L);
	if (keq(self->f[1], kb(0))) {
		kstep(&KF[0], 10, self, L);
		{ kv v = kb(1);
		  self->f[1] = v;
		}
		kstep(&KF[0], 11, self, L);
		{ kv a = knone();
		  ksend(kread(L[0], "哲学者"), "渡す", a, 0);
		}
	} else {
		kstep(&KF[0], 13, self, L);
		{ kv arr = self->f[2];
		  kpush(arr, kread(L[0], "哲学者"), "待ち行列");
		}
	}
}

static void kh0_1(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[1], 17, self, L);
	if (!keq(self->f[2], knewarr())) {
		kstep(&KF[1], 18, self, L);
		L[0] = kshift(self->f[2], "待ち行列");
		kstep(&KF[1], 19, self, L);
		{ kv a = knone();
		  ksend(kread(L[0], "次の哲学者"), "渡す", a, 0);
		}
	} else {
		kstep(&KF[1], 21, self, L);
		{ kv v = kb(0);
		  self->f[1] = v;
		}
	}
}

static const char *kf0[] = { "番号", "使用中", "待ち行列" };
static const struct khent kht0[] = { { "取りたい", kh0_0 }, { "返す", kh0_1 } };
static struct kclass kcls0 = { "フォーク", 3, kf0, kinit0, 2, kht0, 0 };

static void kinit1(struct kact *self) {
	self->f[0] = kn(0);
	self->f[1] = knone();
	self->f[2] = knone();
	self->f[3] = kn(0);
	self->f[4] = kn(0);
}

static void kh1_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[2], 36, self, L);
	{ static const int32 lit[3] = { 1, 0, 1 };
	  kv vals[3];
	  vals[0] = ks("哲学者");
	  vals[1] = (*kfield(kactv(self), "番号", "自分の番号"));
	  vals[2] = ks("が考えています");
	  kdisp(3, lit, vals); }
	kstep(&KF[2], 37, self, L);
	{ kv v = kn(0);
	  self->f[3] = v;
	}
	kstep(&KF[2], 38, self, L);
	{ kv a = kactv(self);
	  ksend(self->f[1], "取りたい", a, 1);
	}
}

static void kh1_1(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[3], 41, self, L);
	self->f[3] = kadd(self->f[3], kn(1), "持っている本数");
	kstep(&KF[3], 42, self, L);
	if (keq(self->f[3], kn(1))) {
		kstep(&KF[3], 43, self, L);
		{ kv a = kactv(self);
		  ksend(self->f[2], "取りたい", a, 1);
		}
	}
	kstep(&KF[3], 45, self, L);
	if (keq(self->f[3], kn(2))) {
		kstep(&KF[3], 46, self, L);
		{ static const int32 lit[3] = { 1, 0, 1 };
		  kv vals[3];
		  vals[0] = ks("哲学者");
		  vals[1] = (*kfield(kactv(self), "番号", "自分の番号"));
		  vals[2] = ks("が食事しています");
		  kdisp(3, lit, vals); }
		kstep(&KF[3], 47, self, L);
		self->f[4] = kadd(self->f[4], kn(1), "食べた回数");
		kstep(&KF[3], 48, self, L);
		{ kv a = knone();
		  ksend(self->f[1], "返す", a, 0);
		  ksend(self->f[2], "返す", a, 0);
		}
		kstep(&KF[3], 49, self, L);
		if (klt(self->f[4], kn(3), "食べた回数", "3")) {
			kstep(&KF[3], 50, self, L);
			{ kv a = knone();
			  ksend(kactv(self), "開始", a, 0);
			}
		} else {
			kstep(&KF[3], 52, self, L);
			{ static const int32 lit[3] = { 1, 0, 1 };
			  kv vals[3];
			  vals[0] = ks("哲学者");
			  vals[1] = (*kfield(kactv(self), "番号", "自分の番号"));
			  vals[2] = ks("が満腹です");
			  kdisp(3, lit, vals); }
		}
	}
}

static const char *kf1[] = { "番号", "先のフォーク", "後のフォーク", "持っている本数", "食べた回数" };
static const struct khent kht1[] = { { "開始", kh1_0 }, { "渡す", kh1_1 } };
static struct kclass kcls1 = { "哲学者", 5, kf1, kinit1, 2, kht1, 0 };

static void kbody(void) {
	struct kact *self = NULL; (void)self;
	kv L[4];
	int32 i;
	(void)L;
	for (i = 0; i < 4; i++) L[i].t = KN_UNSET;
	kstep(&KF[4], 59, self, L);
	L[0] = knewarr();
	kstep(&KF[4], 60, self, L);
	{ int32 n0, h1 = knum(kn(5), "5");
	  for (n0 = knum(kn(1), "1"); n0 <= h1; n0++) {
		kstep(&KF[4], 61, self, L);
		L[1] = knew(&kcls0);
		kstep(&KF[4], 62, self, L);
		{ kv v = kn(n0);
		  *kfield(kread(L[1], "棒の番号"), "番号", "棒の番号") = v;
		}
		kstep(&KF[4], 63, self, L);
		{ kv arr = kread(L[0], "フォークたち");
		  kpush(arr, kread(L[1], "棒"), "フォークたち");
		}
	} }
	kstep(&KF[4], 65, self, L);
	L[2] = knewarr();
	kstep(&KF[4], 66, self, L);
	{ int32 n2, h3 = knum(kn(5), "5");
	  for (n2 = knum(kn(1), "1"); n2 <= h3; n2++) {
		kstep(&KF[4], 67, self, L);
		L[3] = knew(&kcls1);
		kstep(&KF[4], 68, self, L);
		{ kv v = kn(n2);
		  *kfield(kread(L[3], "人の番号"), "番号", "人の番号") = v;
		}
		kstep(&KF[4], 69, self, L);
		if (keq(kn(n2), kn(5))) {
			kstep(&KF[4], 70, self, L);
			{ kv v = kget(kread(L[0], "フォークたち"), kn(1), "フォークたちの 1 番目");
			  *kfield(kread(L[3], "人の先のフォーク"), "先のフォーク", "人の先のフォーク") = v;
			}
			kstep(&KF[4], 71, self, L);
			{ kv v = kget(kread(L[0], "フォークたち"), kn(5), "フォークたちの 5 番目");
			  *kfield(kread(L[3], "人の後のフォーク"), "後のフォーク", "人の後のフォーク") = v;
			}
		} else {
			kstep(&KF[4], 73, self, L);
			{ kv v = kget(kread(L[0], "フォークたち"), kn(n2), "フォークたちの 現在の番号 番目");
			  *kfield(kread(L[3], "人の先のフォーク"), "先のフォーク", "人の先のフォーク") = v;
			}
			kstep(&KF[4], 74, self, L);
			{ kv v = kget(kread(L[0], "フォークたち"), kadd(kn(n2), kn(1), "（現在の番号 足す 1）"), "フォークたちの （現在の番号 足す 1） 番目");
			  *kfield(kread(L[3], "人の後のフォーク"), "後のフォーク", "人の後のフォーク") = v;
			}
		}
		kstep(&KF[4], 76, self, L);
		{ kv arr = kread(L[2], "哲学者たち");
		  kpush(arr, kread(L[3], "人"), "哲学者たち");
		}
	} }
	kstep(&KF[4], 78, self, L);
	ksendall(kread(L[2], "哲学者たち"), "開始", knone(), 0, "哲学者たち");
}

static const char *KS0[] = { "哲学者" };
static const char *KS1[] = { "次の哲学者" };
static const char *KS2[] = { "" };
static const char *KS3[] = { "" };
static const char *KS4[] = { "フォークたち", "棒", "哲学者たち", "人" };
static struct kfun KF[5] = {
	{ &kp5_prog, 0, "取りたい", 8, 15, 1, KS0 },
	{ &kp5_prog, 0, "返す", 16, 23, 1, KS1 },
	{ &kp5_prog, 1, "開始", 35, 39, 0, KS2 },
	{ &kp5_prog, 1, "渡す", 40, 55, 0, KS3 },
	{ &kp5_prog, -1, "実行部", 58, 79, 4, KS4 },
};

static const char *KL[80] = {
	"「フォーク」というアクターを定義する。",
	"    状態は 番号、使用中、待ち行列。",
	"    初期状態は",
	"        番号 は 0。",
	"        使用中 は いいえ。",
	"        待ち行列 は 空。",
	"    以上。",
	"    「取りたい」と 哲学者 を受け取ったとき、",
	"        もし 使用中 が いいえ ならば、",
	"            使用中 は はい。",
	"            哲学者 に「渡す」を送る。",
	"        そうでなければ、",
	"            待ち行列 に 哲学者 を追加する。",
	"        以上。",
	"    以上。",
	"    「返す」を受け取ったとき、",
	"        もし 待ち行列 が 空 でない ならば、",
	"            次の哲学者 は 待ち行列 の先頭を取り出す。",
	"            次の哲学者 に「渡す」を送る。",
	"        そうでなければ、",
	"            使用中 は いいえ。",
	"        以上。",
	"    以上。",
	"定義を終わる。",
	"",
	"「哲学者」というアクターを定義する。",
	"    状態は 番号、先のフォーク、後のフォーク、持っている本数、食べた回数。",
	"    初期状態は",
	"        番号 は 0。",
	"        先のフォーク は なし。",
	"        後のフォーク は なし。",
	"        持っている本数 は 0。",
	"        食べた回数 は 0。",
	"    以上。",
	"    「開始」を受け取ったとき、",
	"        「哲学者」 と 自分の番号 と 「が考えています」 を表示する。",
	"        持っている本数 は 0。",
	"        先のフォーク に「取りたい」と 自分 を送る。",
	"    以上。",
	"    「渡す」を受け取ったとき、",
	"        持っている本数 は 持っている本数 足す 1。",
	"        もし 持っている本数 が 1 ならば、",
	"            後のフォーク に「取りたい」と 自分 を送る。",
	"        以上。",
	"        もし 持っている本数 が 2 ならば、",
	"            「哲学者」 と 自分の番号 と 「が食事しています」 を表示する。",
	"            食べた回数 は 食べた回数 足す 1。",
	"            先のフォーク と 後のフォーク に それぞれ「返す」を送る。",
	"            もし 食べた回数 が 3 より小さい ならば、",
	"                自分 に「開始」を送る。",
	"            そうでなければ、",
	"                「哲学者」 と 自分の番号 と 「が満腹です」 を表示する。",
	"            以上。",
	"        以上。",
	"    以上。",
	"定義を終わる。",
	"",
	"実行を始める。",
	"    フォークたち は 空の配列。",
	"    1から5まで繰り返す。",
	"        棒 は 「フォーク」の新しいアクター。",
	"        棒の番号 は 現在の番号。",
	"        フォークたち に 棒 を追加する。",
	"    以上。",
	"    哲学者たち は 空の配列。",
	"    1から5まで繰り返す。",
	"        人 は 「哲学者」の新しいアクター。",
	"        人の番号 は 現在の番号。",
	"        もし 現在の番号 が 5 ならば、",
	"            人の先のフォーク は フォークたちの 1 番目。",
	"            人の後のフォーク は フォークたちの 5 番目。",
	"        そうでなければ、",
	"            人の先のフォーク は フォークたちの 現在の番号 番目。",
	"            人の後のフォーク は フォークたちの （現在の番号 足す 1） 番目。",
	"        以上。",
	"        哲学者たち に 人 を追加する。",
	"    以上。",
	"    哲学者たち の全員に「開始」を送る。",
	"実行を終わる。",
	"",
};
static const unsigned char KST[81] = { 0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,0,1,0,0 };
static unsigned char KBP[81];
static const char *KSRC[45] = {
	"■5人の哲学者問題（フォークをアクターとする版）",
	"※フォークは5本、哲学者は5人。哲学者nの左はフォークn、右はフォークn+1（哲学者5の右はフォーク1）。",
	"※番号の小さいフォークから先に取る決まりで、全員が片方を握って待ち合う輪を作らない（デッドロック防止）。",
	"",
	"フォークというアクターを定義する。",
	"フォークは番号と使用中と待ち行列を持つ。",
	"番号の初期値は0とし、使用中の初期値はいいえとし、待ち行列の初期値は空とする。",
	"",
	"フォークが「取りたい」というメッセージと哲学者を受け取ったとき、使用中がいいえならば、使用中をはいに変更し、その哲学者に「渡す」というメッセージを送る。そうでなければ、その哲学者を待ち行列の末尾に追加する。",
	"",
	"フォークが「返す」というメッセージを受け取ったとき、待ち行列が空でなければ、待ち行列の先頭から次の哲学者を取り出し、次の哲学者に「渡す」というメッセージを送る。そうでなければ、使用中をいいえに変更する。",
	"",
	"これでフォークの定義を終わる。",
	"",
	"哲学者というアクターを定義する。",
	"哲学者は番号と先のフォークと後のフォークと持っている本数と食べた回数を持つ。",
	"番号の初期値は0とし、先のフォークと後のフォークの初期値はなしとし、持っている本数と食べた回数の初期値は0とする。",
	"",
	"哲学者が「開始」というメッセージを受け取ったとき、「哲学者」という文字列と自分の番号と「が考えています」という文字列を表示し、持っている本数を0に変更し、先のフォークに「取りたい」というメッセージと自分自身を送る。",
	"",
	"哲学者が「渡す」というメッセージを受け取ったとき、持っている本数に1を加える。",
	"持っている本数が1ならば、後のフォークに「取りたい」というメッセージと自分自身を送る。",
	"持っている本数が2ならば、次のことを行う。",
	"「哲学者」という文字列と自分の番号と「が食事しています」という文字列を表示し、食べた回数に1を加える。",
	"先のフォークと後のフォークにそれぞれ「返す」というメッセージを送る。",
	"食べた回数が3より小さければ、自分自身に「開始」というメッセージを送る。そうでなければ、「哲学者」という文字列と自分の番号と「が満腹です」という文字列を表示する。",
	"以上。",
	"",
	"これで哲学者の定義を終わる。",
	"",
	"実行を始める。",
	"",
	"空の配列を用意し、フォークたちと名付ける。",
	"1から5までの各番号について、フォークというアクターを1つ生成し、棒と名付け、棒の番号を現在の番号に設定し、棒をフォークたちの末尾に追加する。",
	"",
	"空の配列を用意し、哲学者たちと名付ける。",
	"1から5までの各番号について、次のことを行う。",
	"哲学者というアクターを1つ生成し、人と名付け、人の番号を現在の番号に設定する。",
	"現在の番号が5ならば、人の先のフォークをフォークたちの1番目に設定し、人の後のフォークをフォークたちの5番目に設定する。そうでなければ、人の先のフォークをフォークたちの（現在の番号）番目に設定し、人の後のフォークをフォークたちの（現在の番号に1を加えた数）番目に設定する。",
	"人を哲学者たちの末尾に追加する。",
	"以上。",
	"",
	"哲学者たちの全員に「開始」というメッセージを送る。",
	"",
	"これで実行を終わる。",
};
static struct kclass *KC[2] = { &kcls0, &kcls1 };
static const int32 KCL[2] = { 1, 26 };
static const int32 KCE[2] = { 24, 56 };
struct kprogram kp5_prog = { "5人の哲学者", 2, KC, KCL, KCE, kbody, 58, 79,
	80, KL, KST, KBP, 45, KSRC, 5, KF };
