/* kp4.c - ことのはから k2xinu.mjs で生成。手で直さないこと */
/* 元: クイックソート.txt */
#include <xinu.h>
#include "krt.h"

extern struct kprogram kp4_prog;
static struct kfun KF[4];
static struct kclass kcls0;
static struct kclass kcls1;

static void kinit0(struct kact *self) {
}

static void kh0_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[0], 4, self, L);
	{ kv v = kget(kread(L[0], "仕事"), kn(1), "仕事の 1 番目");
	  self->f[0] = v;
	}
	kstep(&KF[0], 5, self, L);
	{ kv v = kget(kread(L[0], "仕事"), kn(2), "仕事の 2 番目");
	  self->f[4] = v;
	}
	kstep(&KF[0], 6, self, L);
	{ kv v = kget(kread(L[0], "仕事"), kn(3), "仕事の 3 番目");
	  self->f[5] = v;
	}
	kstep(&KF[0], 7, self, L);
	if (klt(klen(self->f[0], "列 の要素数"), kn(2), "列 の要素数", "2")) {
		kstep(&KF[0], 8, self, L);
		{ kv v = knewarr();
		  self->f[13] = v;
		}
		kstep(&KF[0], 9, self, L);
		{ kv arr = self->f[13];
		  kpush(arr, self->f[5], "答え");
		  kpush(arr, self->f[0], "答え");
		}
		kstep(&KF[0], 10, self, L);
		{ kv a = self->f[13];
		  ksend(self->f[4], "並んだ", a, 1);
		}
	} else {
		kstep(&KF[0], 12, self, L);
		{ static const int32 lit[3] = { 0, 1, 0 };
		  kv vals[3];
		  vals[0] = kactv(self);
		  vals[1] = ks("が受け持つ：");
		  vals[2] = self->f[0];
		  kdisp(3, lit, vals); }
		kstep(&KF[0], 13, self, L);
		self->f[1] = kshift(self->f[0], "列");
		kstep(&KF[0], 14, self, L);
		{ kv v = knewarr();
		  self->f[2] = v;
		}
		kstep(&KF[0], 15, self, L);
		{ kv v = knewarr();
		  self->f[3] = v;
		}
		kstep(&KF[0], 16, self, L);
		{ int32 n0, h1 = knum(klen(self->f[0], "列 の要素数"), "（列 の要素数）");
		  for (n0 = knum(kn(1), "1"); n0 <= h1; n0++) {
			kstep(&KF[0], 17, self, L);
			if (klt(kget(self->f[0], kn(n0), "列の 現在の番号 番目"), self->f[1], "列の 現在の番号 番目", "軸")) {
				kstep(&KF[0], 18, self, L);
				{ kv arr = self->f[2];
				  kpush(arr, kget(self->f[0], kn(n0), "列の 現在の番号 番目"), "小さい組");
				}
			} else {
				kstep(&KF[0], 20, self, L);
				{ kv arr = self->f[3];
				  kpush(arr, kget(self->f[0], kn(n0), "列の 現在の番号 番目"), "大きい組");
				}
			}
		} }
		kstep(&KF[0], 23, self, L);
		{ kv v = kn(0);
		  self->f[8] = v;
		}
		kstep(&KF[0], 24, self, L);
		self->f[10] = knew(&kcls0);
		kstep(&KF[0], 25, self, L);
		self->f[11] = knew(&kcls0);
		kstep(&KF[0], 26, self, L);
		{ kv v = knewarr();
		  self->f[12] = v;
		}
		kstep(&KF[0], 27, self, L);
		{ kv arr = self->f[12];
		  kpush(arr, self->f[2], "依頼");
		  kpush(arr, kactv(self), "依頼");
		  kpush(arr, ks("左"), "依頼");
		}
		kstep(&KF[0], 28, self, L);
		{ kv a = self->f[12];
		  ksend(self->f[10], "並べよ", a, 1);
		}
		kstep(&KF[0], 29, self, L);
		{ kv v = knewarr();
		  self->f[12] = v;
		}
		kstep(&KF[0], 30, self, L);
		{ kv arr = self->f[12];
		  kpush(arr, self->f[3], "依頼");
		  kpush(arr, kactv(self), "依頼");
		  kpush(arr, ks("右"), "依頼");
		}
		kstep(&KF[0], 31, self, L);
		{ kv a = self->f[12];
		  ksend(self->f[11], "並べよ", a, 1);
		}
	}
}

static void kh0_1(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[1], 35, self, L);
	if (keq(kget(kread(L[0], "返事"), kn(1), "返事の 1 番目"), ks("左"))) {
		kstep(&KF[1], 36, self, L);
		{ kv v = kget(kread(L[0], "返事"), kn(2), "返事の 2 番目");
		  self->f[6] = v;
		}
	} else {
		kstep(&KF[1], 38, self, L);
		{ kv v = kget(kread(L[0], "返事"), kn(2), "返事の 2 番目");
		  self->f[7] = v;
		}
	}
	kstep(&KF[1], 40, self, L);
	self->f[8] = kadd(self->f[8], kn(1), "届いた数");
	kstep(&KF[1], 41, self, L);
	if (keq(self->f[8], kn(2))) {
		kstep(&KF[1], 42, self, L);
		{ kv v = knewarr();
		  self->f[9] = v;
		}
		kstep(&KF[1], 43, self, L);
		{ int32 n2, h3 = knum(klen(self->f[6], "左 の要素数"), "（左 の要素数）");
		  for (n2 = knum(kn(1), "1"); n2 <= h3; n2++) {
			kstep(&KF[1], 44, self, L);
			{ kv arr = self->f[9];
			  kpush(arr, kget(self->f[6], kn(n2), "左の 現在の番号 番目"), "結果");
			}
		} }
		kstep(&KF[1], 46, self, L);
		{ kv arr = self->f[9];
		  kpush(arr, self->f[1], "結果");
		}
		kstep(&KF[1], 47, self, L);
		{ int32 n4, h5 = knum(klen(self->f[7], "右 の要素数"), "（右 の要素数）");
		  for (n4 = knum(kn(1), "1"); n4 <= h5; n4++) {
			kstep(&KF[1], 48, self, L);
			{ kv arr = self->f[9];
			  kpush(arr, kget(self->f[7], kn(n4), "右の 現在の番号 番目"), "結果");
			}
		} }
		kstep(&KF[1], 50, self, L);
		{ static const int32 lit[3] = { 0, 1, 0 };
		  kv vals[3];
		  vals[0] = kactv(self);
		  vals[1] = ks("がつなげた：");
		  vals[2] = self->f[9];
		  kdisp(3, lit, vals); }
		kstep(&KF[1], 51, self, L);
		{ kv v = knewarr();
		  self->f[13] = v;
		}
		kstep(&KF[1], 52, self, L);
		{ kv arr = self->f[13];
		  kpush(arr, self->f[5], "答え");
		  kpush(arr, self->f[9], "答え");
		}
		kstep(&KF[1], 53, self, L);
		{ kv a = self->f[13];
		  ksend(self->f[4], "並んだ", a, 1);
		}
	}
}

static const char *kf0[] = { "列", "軸", "小さい組", "大きい組", "依頼主", "印", "左", "右", "届いた数", "結果", "左係", "右係", "依頼", "答え" };
static const struct khent kht0[] = { { "並べよ", kh0_0 }, { "並んだ", kh0_1 } };
static struct kclass kcls0 = { "並べ係", 14, kf0, kinit0, 2, kht0, 0 };

static void kinit1(struct kact *self) {
}

static void kh1_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[2], 61, self, L);
	{ static const int32 lit[2] = { 1, 0 };
	  kv vals[2];
	  vals[0] = ks("並べた結果：");
	  vals[1] = kget(kread(L[0], "返事"), kn(2), "返事の 2 番目");
	  kdisp(2, lit, vals); }
}

static const char *kf1[] = { "並び" };
static const struct khent kht1[] = { { "並んだ", kh1_0 } };
static struct kclass kcls1 = { "見届け係", 1, kf1, kinit1, 1, kht1, 0 };

static void kbody(void) {
	struct kact *self = NULL; (void)self;
	kv L[4];
	int32 i;
	(void)L;
	for (i = 0; i < 4; i++) L[i].t = KN_UNSET;
	kstep(&KF[3], 66, self, L);
	L[0] = knew(&kcls1);
	kstep(&KF[3], 67, self, L);
	L[1] = knew(&kcls0);
	kstep(&KF[3], 68, self, L);
	L[2] = knewarr();
	kstep(&KF[3], 69, self, L);
	{ kv arr = kread(L[2], "並び");
	  kpush(arr, kn(5), "並び");
	  kpush(arr, kn(2), "並び");
	  kpush(arr, kn(9), "並び");
	  kpush(arr, kn(1), "並び");
	  kpush(arr, kn(7), "並び");
	  kpush(arr, kn(3), "並び");
	  kpush(arr, kn(8), "並び");
	  kpush(arr, kn(6), "並び");
	  kpush(arr, kn(4), "並び");
	}
	kstep(&KF[3], 70, self, L);
	L[3] = knewarr();
	kstep(&KF[3], 71, self, L);
	{ kv arr = kread(L[3], "依頼");
	  kpush(arr, kread(L[2], "並び"), "依頼");
	  kpush(arr, kread(L[0], "見届け役"), "依頼");
	  kpush(arr, ks("全体"), "依頼");
	}
	kstep(&KF[3], 72, self, L);
	{ kv a = kread(L[3], "依頼");
	  ksend(kread(L[1], "根"), "並べよ", a, 1);
	}
}

static const char *KS0[] = { "仕事" };
static const char *KS1[] = { "返事" };
static const char *KS2[] = { "返事" };
static const char *KS3[] = { "見届け役", "根", "並び", "依頼" };
static struct kfun KF[4] = {
	{ &kp4_prog, 0, "並べよ", 3, 33, 1, KS0 },
	{ &kp4_prog, 0, "並んだ", 34, 55, 1, KS1 },
	{ &kp4_prog, 1, "並んだ", 60, 62, 1, KS2 },
	{ &kp4_prog, -1, "実行部", 65, 73, 4, KS3 },
};

static const char *KL[74] = {
	"「並べ係」というアクターを定義する。",
	"    状態は 列、軸、小さい組、大きい組、依頼主、印、左、右、届いた数、結果、左係、右係、依頼、答え。",
	"    「並べよ」と 仕事 を受け取ったとき、",
	"        列 は 仕事の 1 番目。",
	"        依頼主 は 仕事の 2 番目。",
	"        印 は 仕事の 3 番目。",
	"        もし 列 の要素数 が 2 より小さい ならば、",
	"            答え は 空の配列。",
	"            答え に 印 と 列 を追加する。",
	"            依頼主 に「並んだ」と 答え を送る。",
	"        そうでなければ、",
	"            自分 と 「が受け持つ：」 と 列 を表示する。",
	"            軸 は 列 の先頭を取り出す。",
	"            小さい組 は 空の配列。",
	"            大きい組 は 空の配列。",
	"            1から（列 の要素数）まで繰り返す。",
	"                もし 列の 現在の番号 番目 が 軸 より小さい ならば、",
	"                    小さい組 に 列の 現在の番号 番目 を追加する。",
	"                そうでなければ、",
	"                    大きい組 に 列の 現在の番号 番目 を追加する。",
	"                以上。",
	"            以上。",
	"            届いた数 は 0。",
	"            左係 は 「並べ係」の新しいアクター。",
	"            右係 は 「並べ係」の新しいアクター。",
	"            依頼 は 空の配列。",
	"            依頼 に 小さい組 と 自分 と 「左」 を追加する。",
	"            左係 に「並べよ」と 依頼 を送る。",
	"            依頼 は 空の配列。",
	"            依頼 に 大きい組 と 自分 と 「右」 を追加する。",
	"            右係 に「並べよ」と 依頼 を送る。",
	"        以上。",
	"    以上。",
	"    「並んだ」と 返事 を受け取ったとき、",
	"        もし 返事の 1 番目 が 「左」 ならば、",
	"            左 は 返事の 2 番目。",
	"        そうでなければ、",
	"            右 は 返事の 2 番目。",
	"        以上。",
	"        届いた数 は 届いた数 足す 1。",
	"        もし 届いた数 が 2 ならば、",
	"            結果 は 空の配列。",
	"            1から（左 の要素数）まで繰り返す。",
	"                結果 に 左の 現在の番号 番目 を追加する。",
	"            以上。",
	"            結果 に 軸 を追加する。",
	"            1から（右 の要素数）まで繰り返す。",
	"                結果 に 右の 現在の番号 番目 を追加する。",
	"            以上。",
	"            自分 と 「がつなげた：」 と 結果 を表示する。",
	"            答え は 空の配列。",
	"            答え に 印 と 結果 を追加する。",
	"            依頼主 に「並んだ」と 答え を送る。",
	"        以上。",
	"    以上。",
	"定義を終わる。",
	"",
	"「見届け係」というアクターを定義する。",
	"    状態は 並び。",
	"    「並んだ」と 返事 を受け取ったとき、",
	"        「並べた結果：」 と 返事の 2 番目 を表示する。",
	"    以上。",
	"定義を終わる。",
	"",
	"実行を始める。",
	"    見届け役 は 「見届け係」の新しいアクター。",
	"    根 は 「並べ係」の新しいアクター。",
	"    並び は 空の配列。",
	"    並び に 5 と 2 と 9 と 1 と 7 と 3 と 8 と 6 と 4 を追加する。",
	"    依頼 は 空の配列。",
	"    依頼 に 並び と 見届け役 と 「全体」 を追加する。",
	"    根 に「並べよ」と 依頼 を送る。",
	"実行を終わる。",
	"",
};
static const unsigned char KST[75] = { 0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0 };
static unsigned char KBP[75];
static const char *KSRC[49] = {
	"■ クイックソート（アクターで並列に分ける）",
	"※ 並べ係は、受け取った列の先頭を軸に取り、軸より小さい数と、そうでない数の2組に分ける。",
	"※ 2組はそれぞれ新しい並べ係（左係・右係）に任せ、2つの返事がそろったら「小さい組・軸・大きい組」の順につなげて依頼主に返す。",
	"※ 左右の係は同時に動くので、途中の表示の順番は「動く順」の種によって変わる。最後の結果は変わらない。",
	"並べ係というアクターを定義する。",
	"並べ係は列と軸と小さい組と大きい組と依頼主と印と左と右と届いた数と結果と左係と右係と依頼と答えを持つ。",
	"",
	"並べ係が「並べよ」というメッセージと仕事を受け取ったとき、",
	"列を仕事の1番目に変更し、依頼主を仕事の2番目に変更し、印を仕事の3番目に変更する。",
	"列の要素数が2より小さければ、空の配列を用意し、答えと名付け、印と列を答えの末尾に追加し、依頼主に「並んだ」というメッセージと答えを送る。",
	"そうでなければ、次のことを行う。",
	"自分自身と「が受け持つ：」と列を表示する。",
	"列の先頭から軸を取り出し、空の配列を用意し、小さい組と名付け、空の配列を用意し、大きい組と名付ける。",
	"1から列の要素数までの各番号について、次のことを行う。",
	"列の（現在の番号）番目が軸より小さければ、列の（現在の番号）番目を小さい組の末尾に追加する。",
	"そうでなければ、列の（現在の番号）番目を大きい組の末尾に追加する。",
	"以上。",
	"届いた数を0に変更し、並べ係というアクターを1つ生成し、左係と名付け、並べ係というアクターを1つ生成し、右係と名付ける。",
	"空の配列を用意し、依頼と名付け、小さい組と自分自身と「左」を依頼の末尾に追加し、左係に「並べよ」というメッセージと依頼を送る。",
	"空の配列を用意し、依頼と名付け、大きい組と自分自身と「右」を依頼の末尾に追加し、右係に「並べよ」というメッセージと依頼を送る。",
	"以上。",
	"",
	"並べ係が「並んだ」というメッセージと返事を受け取ったとき、",
	"返事の1番目が「左」ならば、左を返事の2番目に変更する。",
	"そうでなければ、右を返事の2番目に変更する。",
	"届いた数に1を加える。",
	"届いた数が2ならば、次のことを行う。",
	"空の配列を用意し、結果と名付ける。",
	"1から左の要素数までの各番号について、左の（現在の番号）番目を結果の末尾に追加する。",
	"軸を結果の末尾に追加する。",
	"1から右の要素数までの各番号について、右の（現在の番号）番目を結果の末尾に追加する。",
	"自分自身と「がつなげた：」と結果を表示する。",
	"空の配列を用意し、答えと名付け、印と結果を答えの末尾に追加し、依頼主に「並んだ」というメッセージと答えを送る。",
	"以上。",
	"これで並べ係の定義を終わる。",
	"",
	"見届け係というアクターを定義する。",
	"見届け係は並びを持つ。",
	"",
	"見届け係が「並んだ」というメッセージと返事を受け取ったとき、",
	"「並べた結果：」と返事の2番目を表示する。",
	"これで見届け係の定義を終わる。",
	"",
	"実行を始める。",
	"見届け係というアクターを1つ生成し、見届け役と名付ける。",
	"並べ係というアクターを1つ生成し、根と名付ける。",
	"空の配列を用意し、並びと名付け、5と2と9と1と7と3と8と6と4を並びの末尾に追加する。",
	"空の配列を用意し、依頼と名付け、並びと見届け役と「全体」を依頼の末尾に追加し、根に「並べよ」というメッセージと依頼を送る。",
	"これで実行を終わる。",
};
static struct kclass *KC[2] = { &kcls0, &kcls1 };
static const int32 KCL[2] = { 1, 58 };
static const int32 KCE[2] = { 56, 63 };
struct kprogram kp4_prog = { "クイックソート", 2, KC, KCL, KCE, kbody, 65, 73,
	74, KL, KST, KBP, 49, KSRC, 4, KF };
