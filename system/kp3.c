/* kp3.c - ことのはから k2xinu.mjs で生成。手で直さないこと */
/* 元: バブルソート.txt */
#include <xinu.h>
#include "krt.h"

extern struct kprogram kp3_prog;
static struct kfun KF[2];
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
	{ kv v = kread(L[0], "並び");
	  self->f[0] = v;
	}
	kstep(&KF[0], 5, self, L);
	{ static const int32 lit[2] = { 1, 0 };
	  kv vals[2];
	  vals[0] = ks("並べる前：");
	  vals[1] = self->f[0];
	  kdisp(2, lit, vals); }
	kstep(&KF[0], 6, self, L);
	{ int32 n0, h1 = knum(ksub(klen(self->f[0], "列 の要素数"), kn(1), "（列 の要素数 引く 1）"), "（列 の要素数 引く 1）");
	  for (n0 = knum(kn(1), "1"); n0 <= h1; n0++) {
		kstep(&KF[0], 7, self, L);
		{ int32 n2, h3 = knum(ksub(klen(self->f[0], "列 の要素数"), kn(n0), "（列 の要素数 引く 現在の番号）"), "（列 の要素数 引く 現在の番号）");
		  for (n2 = knum(kn(1), "1"); n2 <= h3; n2++) {
			kstep(&KF[0], 8, self, L);
			if (klt(kget(self->f[0], kadd(kn(n2), kn(1), "（現在の番号 足す 1）"), "列の （現在の番号 足す 1） 番目"), kget(self->f[0], kn(n2), "列の 現在の番号 番目"), "列の （現在の番号 足す 1） 番目", "列の 現在の番号 番目")) {
				kstep(&KF[0], 9, self, L);
				{ kv v = kget(self->f[0], kn(n2), "列の 現在の番号 番目");
				  self->f[1] = v;
				}
				kstep(&KF[0], 10, self, L);
				{ kv v = kget(self->f[0], kadd(kn(n2), kn(1), "（現在の番号 足す 1）"), "列の （現在の番号 足す 1） 番目");
				  kset(self->f[0], kn(n2), v, "列の 現在の番号 番目");
				}
				kstep(&KF[0], 11, self, L);
				{ kv v = self->f[1];
				  kset(self->f[0], kadd(kn(n2), kn(1), "（現在の番号 足す 1）"), v, "列の （現在の番号 足す 1） 番目");
				}
			}
		} }
		kstep(&KF[0], 14, self, L);
		{ static const int32 lit[3] = { 0, 1, 0 };
		  kv vals[3];
		  vals[0] = kn(n0);
		  vals[1] = ks("回目：");
		  vals[2] = self->f[0];
		  kdisp(3, lit, vals); }
	} }
	kstep(&KF[0], 16, self, L);
	{ static const int32 lit[2] = { 1, 0 };
	  kv vals[2];
	  vals[0] = ks("並べた後：");
	  vals[1] = self->f[0];
	  kdisp(2, lit, vals); }
}

static const char *kf0[] = { "列", "一時" };
static const struct khent kht0[] = { { "並べよ", kh0_0 } };
static struct kclass kcls0 = { "並べ係", 2, kf0, kinit0, 1, kht0, 0 };

static void kbody(void) {
	struct kact *self = NULL; (void)self;
	kv L[2];
	int32 i;
	(void)L;
	for (i = 0; i < 2; i++) L[i].t = KN_UNSET;
	kstep(&KF[1], 21, self, L);
	L[0] = knew(&kcls0);
	kstep(&KF[1], 22, self, L);
	L[1] = knewarr();
	kstep(&KF[1], 23, self, L);
	{ kv arr = kread(L[1], "並び");
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
	kstep(&KF[1], 24, self, L);
	{ kv a = kread(L[1], "並び");
	  ksend(kread(L[0], "係"), "並べよ", a, 1);
	}
}

static const char *KS0[] = { "並び" };
static const char *KS1[] = { "係", "並び" };
static struct kfun KF[2] = {
	{ &kp3_prog, 0, "並べよ", 3, 17, 1, KS0 },
	{ &kp3_prog, -1, "実行部", 20, 25, 2, KS1 },
};

static const char *KL[26] = {
	"「並べ係」というアクターを定義する。",
	"    状態は 列、一時。",
	"    「並べよ」と 並び を受け取ったとき、",
	"        列 は 並び。",
	"        「並べる前：」 と 列 を表示する。",
	"        1から（列 の要素数 引く 1）まで繰り返す。",
	"            1から（列 の要素数 引く 現在の番号）まで繰り返す。",
	"                もし 列の （現在の番号 足す 1） 番目 が 列の 現在の番号 番目 より小さい ならば、",
	"                    一時 は 列の 現在の番号 番目。",
	"                    列の 現在の番号 番目 は 列の （現在の番号 足す 1） 番目。",
	"                    列の （現在の番号 足す 1） 番目 は 一時。",
	"                以上。",
	"            以上。",
	"            現在の番号 と 「回目：」 と 列 を表示する。",
	"        以上。",
	"        「並べた後：」 と 列 を表示する。",
	"    以上。",
	"定義を終わる。",
	"",
	"実行を始める。",
	"    係 は 「並べ係」の新しいアクター。",
	"    並び は 空の配列。",
	"    並び に 5 と 2 と 9 と 1 と 7 と 3 と 8 と 6 と 4 を追加する。",
	"    係 に「並べよ」と 並び を送る。",
	"実行を終わる。",
	"",
};
static const unsigned char KST[27] = { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0,1,0,0,0,0,1,1,1,1,0,0 };
static unsigned char KBP[27];
static const char *KSRC[22] = {
	"■ バブルソート",
	"※ 隣どうしを比べて、順番が逆なら入れ替える。これを1回やるごとに、いちばん大きい数が右端に寄る。",
	"※ 内側の繰り返しの範囲「1から（列の要素数から現在の番号を引いた数）まで」は、入る前に一度だけ計算する。",
	"※ そのときの「現在の番号」は外側の番号（何回目か）なので、回を重ねるごとに比べる範囲が1つずつ縮む。",
	"並べ係というアクターを定義する。",
	"並べ係は列と一時を持つ。",
	"",
	"並べ係が「並べよ」というメッセージと並びを受け取ったとき、",
	"列を並びに変更し、「並べる前：」と列を表示する。",
	"1から（列の要素数から1を引いた数）までの各番号について、次のことを行う。",
	"1から（列の要素数から現在の番号を引いた数）までの各番号について、次のことを行う。",
	"列の（現在の番号に1を加えた数）番目が列の（現在の番号）番目より小さければ、一時を列の（現在の番号）番目に変更し、列の（現在の番号）番目を列の（現在の番号に1を加えた数）番目に設定し、列の（現在の番号に1を加えた数）番目を一時に設定する。",
	"以上。",
	"現在の番号と「回目：」と列を表示する。",
	"以上。",
	"「並べた後：」と列を表示する。",
	"これで並べ係の定義を終わる。",
	"",
	"実行を始める。",
	"並べ係というアクターを1つ生成し、係と名付ける。",
	"空の配列を用意し、並びと名付け、5と2と9と1と7と3と8と6と4を並びの末尾に追加し、係に「並べよ」というメッセージと並びを送る。",
	"これで実行を終わる。",
};
static struct kclass *KC[1] = { &kcls0 };
static const int32 KCL[1] = { 1 };
static const int32 KCE[1] = { 18 };
struct kprogram kp3_prog = { "バブルソート", 1, KC, KCL, KCE, kbody, 20, 25,
	26, KL, KST, KBP, 22, KSRC, 2, KF };
