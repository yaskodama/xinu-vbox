/* kp7.c - ことのはから k2xinu.mjs で生成。手で直さないこと */
/* 元: Xinu_挨拶.txt */
#include <xinu.h>
#include "krt.h"

extern struct kprogram kp7_prog;
static struct kfun KF[26];
static struct kclass kcls0;
static struct kclass kcls1;
static struct kclass kcls2;
static struct kclass kcls3;

static void kinit0(struct kact *self) {
	self->f[0] = knewarr();
	self->f[1] = knewarr();
	self->f[2] = knewarr();
	self->f[3] = knewarr();
	self->f[4] = knewarr();
	self->f[5] = knewarr();
	self->f[6] = knewarr();
	self->f[10] = knewarr();
	self->f[11] = knewarr();
	self->f[12] = knewarr();
	self->f[16] = knewarr();
	self->f[17] = knewarr();
	self->f[18] = knewarr();
	self->f[7] = kn(1);
	self->f[8] = kn(0);
	self->f[9] = kn(1);
	self->f[14] = kn(0);
	self->f[13] = kn(2);
	self->f[15] = kb(0);
	self->f[31] = kb(0);
}

static void kh0_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[0], 26, self, L);
	{ int32 n0, h1 = knum(kn(8), "8");
	  for (n0 = knum(kn(1), "1"); n0 <= h1; n0++) {
		kstep(&KF[0], 27, self, L);
		{ kv arr = self->f[0];
		  kpush(arr, ks("FREE"), "状態表");
		}
		kstep(&KF[0], 28, self, L);
		{ kv arr = self->f[1];
		  kpush(arr, kn(0), "優先度表");
		}
		kstep(&KF[0], 29, self, L);
		{ kv arr = self->f[2];
		  kpush(arr, ks("-"), "名前表");
		}
		kstep(&KF[0], 30, self, L);
		{ kv arr = self->f[3];
		  kpush(arr, knone(), "本体表");
		}
		kstep(&KF[0], 31, self, L);
		{ kv arr = self->f[4];
		  kpush(arr, kn(0), "戻り値表");
		}
		kstep(&KF[0], 32, self, L);
		{ kv arr = self->f[5];
		  kpush(arr, kn(0), "伝言表");
		}
		kstep(&KF[0], 33, self, L);
		{ kv arr = self->f[6];
		  kpush(arr, kb(0), "伝言あり表");
		}
		kstep(&KF[0], 34, self, L);
		{ kv arr = self->f[16];
		  kpush(arr, ks("FREE"), "セマフォ状態表");
		}
		kstep(&KF[0], 35, self, L);
		{ kv arr = self->f[17];
		  kpush(arr, kn(0), "セマフォ数表");
		}
		kstep(&KF[0], 36, self, L);
		{ kv v = knewarr();
		  self->f[27] = v;
		}
		kstep(&KF[0], 37, self, L);
		{ kv arr = self->f[18];
		  kpush(arr, self->f[27], "セマフォ待ち表");
		}
	} }
	kstep(&KF[0], 39, self, L);
	{ kv v = ks("CURR");
	  kset(self->f[0], kn(1), v, "状態表の 1 番目");
	}
	kstep(&KF[0], 40, self, L);
	{ kv v = ks("prnull");
	  kset(self->f[2], kn(1), v, "名前表の 1 番目");
	}
	kstep(&KF[0], 41, self, L);
	{ kv v = kget(kread(L[0], "起動"), kn(1), "起動の 1 番目");
	  kset(self->f[3], kn(1), v, "本体表の 1 番目");
	}
	kstep(&KF[0], 42, self, L);
	{ kv v = kn(1);
	  self->f[8] = v;
	}
	kstep(&KF[0], 43, self, L);
	{ kv v = kn(1);
	  self->f[7] = v;
	}
	kstep(&KF[0], 44, self, L);
	{ static const int32 lit[1] = { 1 };
	  kv vals[1];
	  vals[0] = ks("Xinu（ことのは版）: 核を初期化した。NPROC 8、NSEM 8、1刻み 100 ミリ秒");
	  kdisp(1, lit, vals); }
	kstep(&KF[0], 45, self, L);
	{ kv v = knewarr();
	  self->f[21] = v;
	}
	kstep(&KF[0], 46, self, L);
	{ kv arr = self->f[21];
	  kpush(arr, kactv(self), "相手");
	  kpush(arr, kn(1), "相手");
	  kpush(arr, kget(kread(L[0], "起動"), kn(2), "起動の 2 番目"), "相手");
	}
	kstep(&KF[0], 47, self, L);
	{ kv a = self->f[21];
	  ksend(kget(kread(L[0], "起動"), kn(1), "起動の 1 番目"), "生まれた", a, 1);
	}
	kstep(&KF[0], 48, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "戻る", a, 0);
	}
}

static void kh0_1(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[1], 51, self, L);
	{ kv v = knone();
	  self->f[19] = v;
	}
	kstep(&KF[1], 52, self, L);
	{ int32 n2, h3 = knum(kn(8), "8");
	  for (n2 = knum(kn(1), "1"); n2 <= h3; n2++) {
		kstep(&KF[1], 53, self, L);
		if (keq(self->f[19], knone())) {
			kstep(&KF[1], 54, self, L);
			{ kv v = kmod(self->f[9], kn(8), "（次pid を 8 で割った余り）");
			  self->f[9] = v;
			}
			kstep(&KF[1], 55, self, L);
			self->f[9] = kadd(self->f[9], kn(1), "次pid");
			kstep(&KF[1], 56, self, L);
			if (keq(kget(self->f[0], self->f[9], "状態表の 次pid 番目"), ks("FREE"))) {
				kstep(&KF[1], 57, self, L);
				{ kv v = self->f[9];
				  self->f[19] = v;
				}
			}
		}
	} }
	kstep(&KF[1], 61, self, L);
	if (keq(self->f[19], knone())) {
		kstep(&KF[1], 62, self, L);
		{ kv v = ks("SYSERR");
		  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
		}
	} else {
		kstep(&KF[1], 64, self, L);
		{ kv v = ks("SUSP");
		  kset(self->f[0], self->f[19], v, "状態表の 新番号 番目");
		}
		kstep(&KF[1], 65, self, L);
		{ kv v = kget(kread(L[0], "依頼"), kn(3), "依頼の 3 番目");
		  kset(self->f[1], self->f[19], v, "優先度表の 新番号 番目");
		}
		kstep(&KF[1], 66, self, L);
		{ kv v = kget(kread(L[0], "依頼"), kn(4), "依頼の 4 番目");
		  kset(self->f[2], self->f[19], v, "名前表の 新番号 番目");
		}
		kstep(&KF[1], 67, self, L);
		{ kv v = kget(kread(L[0], "依頼"), kn(1), "依頼の 1 番目");
		  kset(self->f[3], self->f[19], v, "本体表の 新番号 番目");
		}
		kstep(&KF[1], 68, self, L);
		{ kv v = kb(0);
		  kset(self->f[6], self->f[19], v, "伝言あり表の 新番号 番目");
		}
		kstep(&KF[1], 69, self, L);
		self->f[8] = kadd(self->f[8], kn(1), "プロセス数");
		kstep(&KF[1], 70, self, L);
		{ kv v = knewarr();
		  self->f[21] = v;
		}
		kstep(&KF[1], 71, self, L);
		{ kv arr = self->f[21];
		  kpush(arr, kactv(self), "相手");
		  kpush(arr, self->f[19], "相手");
		  kpush(arr, kget(kread(L[0], "依頼"), kn(5), "依頼の 5 番目"), "相手");
		}
		kstep(&KF[1], 72, self, L);
		{ kv a = self->f[21];
		  ksend(kget(kread(L[0], "依頼"), kn(1), "依頼の 1 番目"), "生まれた", a, 1);
		}
		kstep(&KF[1], 73, self, L);
		{ kv v = self->f[19];
		  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
		}
	}
	kstep(&KF[1], 75, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "clkhandler", a, 0);
	}
}

static void kh0_2(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[2], 78, self, L);
	if (!keq(kget(self->f[0], kread(L[0], "pid"), "状態表の pid 番目"), ks("SUSP"))) {
		kstep(&KF[2], 79, self, L);
		{ kv v = ks("SYSERR");
		  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
		}
	} else {
		kstep(&KF[2], 81, self, L);
		{ kv v = kget(self->f[1], kread(L[0], "pid"), "優先度表の pid 番目");
		  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
		}
		kstep(&KF[2], 82, self, L);
		{ kv a = kread(L[0], "pid");
		  ksend(kactv(self), "ready", a, 1);
		}
	}
	kstep(&KF[2], 84, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "clkhandler", a, 0);
	}
}

static void kh0_3(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[3], 87, self, L);
	{ kv v = ks("READY");
	  kset(self->f[0], kread(L[0], "pid"), v, "状態表の pid 番目");
	}
	kstep(&KF[3], 88, self, L);
	{ kv v = kb(1);
	  self->f[15] = v;
	}
	kstep(&KF[3], 89, self, L);
	{ kv arr = self->f[10];
	  kpush(arr, kread(L[0], "pid"), "準備リスト");
	}
	kstep(&KF[3], 90, self, L);
	{ kv v = kb(0);
	  self->f[29] = v;
	}
	kstep(&KF[3], 91, self, L);
	{ int32 n4, h5 = knum(ksub(klen(self->f[10], "準備リスト の要素数"), kn(1), "（準備リスト の要素数 引く 1）"), "（準備リスト の要素数 引く 1）");
	  for (n4 = knum(kn(1), "1"); n4 <= h5; n4++) {
		kstep(&KF[3], 92, self, L);
		if (keq(self->f[29], kb(0))) {
			kstep(&KF[3], 93, self, L);
			{ kv v = ksub(klen(self->f[10], "準備リスト の要素数"), kn(n4), "（準備リスト の要素数 引く 現在の番号）");
			  self->f[30] = v;
			}
			kstep(&KF[3], 94, self, L);
			if (klt(kget(self->f[1], kget(self->f[10], self->f[30], "準備リストの 位置 番目"), "優先度表の 準備リストの 位置 番目 番目"), kget(self->f[1], kread(L[0], "pid"), "優先度表の pid 番目"), "優先度表の 準備リストの 位置 番目 番目", "優先度表の pid 番目")) {
				kstep(&KF[3], 95, self, L);
				{ kv v = kget(self->f[10], self->f[30], "準備リストの 位置 番目");
				  kset(self->f[10], kadd(self->f[30], kn(1), "（位置 足す 1）"), v, "準備リストの （位置 足す 1） 番目");
				}
				kstep(&KF[3], 96, self, L);
				{ kv v = kread(L[0], "pid");
				  kset(self->f[10], self->f[30], v, "準備リストの 位置 番目");
				}
			} else {
				kstep(&KF[3], 98, self, L);
				{ kv v = kb(1);
				  self->f[29] = v;
				}
			}
		}
	} }
}

static void kh0_4(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[4], 104, self, L);
	{ kv v = kb(0);
	  self->f[15] = v;
	}
	kstep(&KF[4], 105, self, L);
	{ kv v = kn(2);
	  self->f[13] = v;
	}
	kstep(&KF[4], 106, self, L);
	{ kv v = kb(0);
	  self->f[29] = v;
	}
	kstep(&KF[4], 107, self, L);
	if (keq(kget(self->f[0], self->f[7], "状態表の 実行中 番目"), ks("CURR"))) {
		kstep(&KF[4], 108, self, L);
		if (keq(self->f[10], knewarr())) {
			kstep(&KF[4], 109, self, L);
			{ kv v = kb(1);
			  self->f[29] = v;
			}
		} else {
			kstep(&KF[4], 111, self, L);
			if (klt(kget(self->f[1], kget(self->f[10], kn(1), "準備リストの 1 番目"), "優先度表の 準備リストの 1 番目 番目"), kget(self->f[1], self->f[7], "優先度表の 実行中 番目"), "優先度表の 準備リストの 1 番目 番目", "優先度表の 実行中 番目")) {
				kstep(&KF[4], 112, self, L);
				{ kv v = kb(1);
				  self->f[29] = v;
				}
			}
		}
		kstep(&KF[4], 115, self, L);
		if (keq(self->f[29], kb(1))) {
			kstep(&KF[4], 116, self, L);
			{ kv a = knone();
			  ksend(kactv(self), "戻る", a, 0);
			}
		} else {
			kstep(&KF[4], 118, self, L);
			{ kv a = self->f[7];
			  ksend(kactv(self), "ready", a, 1);
			}
			kstep(&KF[4], 119, self, L);
			{ kv a = knone();
			  ksend(kactv(self), "resched", a, 0);
			}
		}
	} else {
		kstep(&KF[4], 122, self, L);
		{ kv v = self->f[7];
		  self->f[20] = v;
		}
		kstep(&KF[4], 123, self, L);
		self->f[7] = kshift(self->f[10], "準備リスト");
		kstep(&KF[4], 124, self, L);
		{ kv v = ks("CURR");
		  kset(self->f[0], self->f[7], v, "状態表の 実行中 番目");
		}
		kstep(&KF[4], 125, self, L);
		{ kv a = self->f[20];
		  ksend(kactv(self), "ctxsw", a, 1);
		}
	}
}

static void kh0_5(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[5], 129, self, L);
	if (keq(self->f[31], kb(1))) {
		kstep(&KF[5], 130, self, L);
		{ static const int32 lit[4] = { 1, 0, 1, 0 };
		  kv vals[4];
		  vals[0] = ks("〔ctxsw〕");
		  vals[1] = kget(self->f[2], kread(L[0], "前"), "名前表の 前 番目");
		  vals[2] = ks("→");
		  vals[3] = kget(self->f[2], self->f[7], "名前表の 実行中 番目");
		  kdisp(4, lit, vals); }
	}
	kstep(&KF[5], 132, self, L);
	{ kv a = kget(self->f[4], self->f[7], "戻り値表の 実行中 番目");
	  ksend(kget(self->f[3], self->f[7], "本体表の 実行中 番目"), "走れ", a, 1);
	}
}

static void kh0_6(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[6], 135, self, L);
	{ kv a = kget(self->f[4], self->f[7], "戻り値表の 実行中 番目");
	  ksend(kget(self->f[3], self->f[7], "本体表の 実行中 番目"), "走れ", a, 1);
	}
}

static void kh0_7(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[7], 138, self, L);
	self->f[14] = kadd(self->f[14], kn(100), "時刻");
	kstep(&KF[7], 139, self, L);
	{ kv v = ksub(self->f[13], kn(1), "（刻み残り 引く 1）");
	  self->f[13] = v;
	}
	kstep(&KF[7], 140, self, L);
	{ kv v = kb(0);
	  self->f[28] = v;
	}
	kstep(&KF[7], 141, self, L);
	if (!keq(kget(self->f[0], self->f[7], "状態表の 実行中 番目"), ks("CURR"))) {
		kstep(&KF[7], 142, self, L);
		{ kv v = kb(1);
		  self->f[15] = v;
		}
	}
	kstep(&KF[7], 144, self, L);
	if (klt(self->f[13], kn(1), "刻み残り", "1")) {
		kstep(&KF[7], 145, self, L);
		{ kv v = kb(1);
		  self->f[15] = v;
		}
	}
	kstep(&KF[7], 147, self, L);
	if (!keq(self->f[11], knewarr())) {
		kstep(&KF[7], 148, self, L);
		{ kv v = ksub(kget(self->f[12], kn(1), "眠り鍵の 1 番目"), kn(100), "（眠り鍵の 1 番目 引く 100）");
		  kset(self->f[12], kn(1), v, "眠り鍵の 1 番目");
		}
		kstep(&KF[7], 149, self, L);
		if (klt(kget(self->f[12], kn(1), "眠り鍵の 1 番目"), kn(1), "眠り鍵の 1 番目", "1")) {
			kstep(&KF[7], 150, self, L);
			{ kv v = kb(1);
			  self->f[28] = v;
			}
		}
	}
	kstep(&KF[7], 153, self, L);
	if (keq(self->f[28], kb(1))) {
		kstep(&KF[7], 154, self, L);
		{ kv a = knone();
		  ksend(kactv(self), "wakeup", a, 0);
		}
	} else {
		kstep(&KF[7], 156, self, L);
		if (keq(self->f[15], kb(1))) {
			kstep(&KF[7], 157, self, L);
			{ kv a = knone();
			  ksend(kactv(self), "resched", a, 0);
			}
		} else {
			kstep(&KF[7], 159, self, L);
			{ kv a = knone();
			  ksend(kactv(self), "戻る", a, 0);
			}
		}
	}
}

static void kh0_8(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[8], 164, self, L);
	{ int32 n6, h7 = knum(kn(8), "8");
	  for (n6 = knum(kn(1), "1"); n6 <= h7; n6++) {
		kstep(&KF[8], 165, self, L);
		if (!keq(self->f[11], knewarr())) {
			kstep(&KF[8], 166, self, L);
			if (klt(kget(self->f[12], kn(1), "眠り鍵の 1 番目"), kn(1), "眠り鍵の 1 番目", "1")) {
				kstep(&KF[8], 167, self, L);
				L[0] = kshift(self->f[11], "眠りリスト");
				kstep(&KF[8], 168, self, L);
				self->f[22] = kshift(self->f[12], "眠り鍵");
				kstep(&KF[8], 169, self, L);
				if (!keq(self->f[11], knewarr())) {
					kstep(&KF[8], 170, self, L);
					{ kv v = kadd(kget(self->f[12], kn(1), "眠り鍵の 1 番目"), self->f[22], "（眠り鍵の 1 番目 足す 鍵）");
					  kset(self->f[12], kn(1), v, "眠り鍵の 1 番目");
					}
				}
				kstep(&KF[8], 172, self, L);
				{ kv a = kread(L[0], "起こすpid");
				  ksend(kactv(self), "ready", a, 1);
				}
			}
		}
	} }
	kstep(&KF[8], 176, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "resched", a, 0);
	}
}

static void kh0_9(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[9], 179, self, L);
	{ kv v = ks("OK");
	  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
	}
	kstep(&KF[9], 180, self, L);
	if (klt(kread(L[0], "長さ"), kn(1), "長さ", "1")) {
		kstep(&KF[9], 181, self, L);
		{ kv a = knone();
		  ksend(kactv(self), "clkhandler", a, 0);
		}
	} else {
		kstep(&KF[9], 183, self, L);
		{ kv v = kread(L[0], "長さ");
		  self->f[23] = v;
		}
		kstep(&KF[9], 184, self, L);
		{ kv v = kb(0);
		  self->f[24] = v;
		}
		kstep(&KF[9], 185, self, L);
		{ kv v = knewarr();
		  self->f[25] = v;
		}
		kstep(&KF[9], 186, self, L);
		{ kv v = knewarr();
		  self->f[26] = v;
		}
		kstep(&KF[9], 187, self, L);
		{ int32 n8, h9 = knum(klen(self->f[11], "眠りリスト の要素数"), "（眠りリスト の要素数）");
		  for (n8 = knum(kn(1), "1"); n8 <= h9; n8++) {
			kstep(&KF[9], 188, self, L);
			if (keq(self->f[24], kb(0))) {
				kstep(&KF[9], 189, self, L);
				if (klt(self->f[23], kget(self->f[12], kn(n8), "眠り鍵の 現在の番号 番目"), "残り", "眠り鍵の 現在の番号 番目")) {
					kstep(&KF[9], 190, self, L);
					{ kv arr = self->f[25];
					  kpush(arr, self->f[7], "新リスト");
					}
					kstep(&KF[9], 191, self, L);
					{ kv arr = self->f[26];
					  kpush(arr, self->f[23], "新鍵");
					}
					kstep(&KF[9], 192, self, L);
					{ kv v = kb(1);
					  self->f[24] = v;
					}
					kstep(&KF[9], 193, self, L);
					{ kv arr = self->f[25];
					  kpush(arr, kget(self->f[11], kn(n8), "眠りリストの 現在の番号 番目"), "新リスト");
					}
					kstep(&KF[9], 194, self, L);
					{ kv arr = self->f[26];
					  kpush(arr, ksub(kget(self->f[12], kn(n8), "眠り鍵の 現在の番号 番目"), self->f[23], "（眠り鍵の 現在の番号 番目 引く 残り）"), "新鍵");
					}
				} else {
					kstep(&KF[9], 196, self, L);
					{ kv v = ksub(self->f[23], kget(self->f[12], kn(n8), "眠り鍵の 現在の番号 番目"), "（残り 引く 眠り鍵の 現在の番号 番目）");
					  self->f[23] = v;
					}
					kstep(&KF[9], 197, self, L);
					{ kv arr = self->f[25];
					  kpush(arr, kget(self->f[11], kn(n8), "眠りリストの 現在の番号 番目"), "新リスト");
					}
					kstep(&KF[9], 198, self, L);
					{ kv arr = self->f[26];
					  kpush(arr, kget(self->f[12], kn(n8), "眠り鍵の 現在の番号 番目"), "新鍵");
					}
				}
			} else {
				kstep(&KF[9], 201, self, L);
				{ kv arr = self->f[25];
				  kpush(arr, kget(self->f[11], kn(n8), "眠りリストの 現在の番号 番目"), "新リスト");
				}
				kstep(&KF[9], 202, self, L);
				{ kv arr = self->f[26];
				  kpush(arr, kget(self->f[12], kn(n8), "眠り鍵の 現在の番号 番目"), "新鍵");
				}
			}
		} }
		kstep(&KF[9], 205, self, L);
		if (keq(self->f[24], kb(0))) {
			kstep(&KF[9], 206, self, L);
			{ kv arr = self->f[25];
			  kpush(arr, self->f[7], "新リスト");
			}
			kstep(&KF[9], 207, self, L);
			{ kv arr = self->f[26];
			  kpush(arr, self->f[23], "新鍵");
			}
		}
		kstep(&KF[9], 209, self, L);
		{ kv v = self->f[25];
		  self->f[11] = v;
		}
		kstep(&KF[9], 210, self, L);
		{ kv v = self->f[26];
		  self->f[12] = v;
		}
		kstep(&KF[9], 211, self, L);
		{ kv v = ks("SLEEP");
		  kset(self->f[0], self->f[7], v, "状態表の 実行中 番目");
		}
		kstep(&KF[9], 212, self, L);
		{ kv a = knone();
		  ksend(kactv(self), "clkhandler", a, 0);
		}
	}
}

static void kh0_10(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[10], 216, self, L);
	{ kv v = knone();
	  self->f[19] = v;
	}
	kstep(&KF[10], 217, self, L);
	{ int32 n10, h11 = knum(kn(8), "8");
	  for (n10 = knum(kn(1), "1"); n10 <= h11; n10++) {
		kstep(&KF[10], 218, self, L);
		if (keq(self->f[19], knone())) {
			kstep(&KF[10], 219, self, L);
			if (keq(kget(self->f[16], kn(n10), "セマフォ状態表の 現在の番号 番目"), ks("FREE"))) {
				kstep(&KF[10], 220, self, L);
				{ kv v = kn(n10);
				  self->f[19] = v;
				}
			}
		}
	} }
	kstep(&KF[10], 224, self, L);
	if (keq(self->f[19], knone())) {
		kstep(&KF[10], 225, self, L);
		{ kv v = ks("SYSERR");
		  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
		}
	} else {
		kstep(&KF[10], 227, self, L);
		{ kv v = ks("USED");
		  kset(self->f[16], self->f[19], v, "セマフォ状態表の 新番号 番目");
		}
		kstep(&KF[10], 228, self, L);
		{ kv v = kread(L[0], "個数");
		  kset(self->f[17], self->f[19], v, "セマフォ数表の 新番号 番目");
		}
		kstep(&KF[10], 229, self, L);
		{ kv v = self->f[19];
		  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
		}
	}
	kstep(&KF[10], 231, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "clkhandler", a, 0);
	}
}

static void kh0_11(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[11], 234, self, L);
	{ kv v = ks("OK");
	  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
	}
	kstep(&KF[11], 235, self, L);
	{ kv v = ksub(kget(self->f[17], kread(L[0], "セマフォ"), "セマフォ数表の セマフォ 番目"), kn(1), "（セマフォ数表の セマフォ 番目 引く 1）");
	  kset(self->f[17], kread(L[0], "セマフォ"), v, "セマフォ数表の セマフォ 番目");
	}
	kstep(&KF[11], 236, self, L);
	if (klt(kget(self->f[17], kread(L[0], "セマフォ"), "セマフォ数表の セマフォ 番目"), kn(0), "セマフォ数表の セマフォ 番目", "0")) {
		kstep(&KF[11], 237, self, L);
		{ kv v = ks("WAIT");
		  kset(self->f[0], self->f[7], v, "状態表の 実行中 番目");
		}
		kstep(&KF[11], 238, self, L);
		{ kv arr = kget(self->f[18], kread(L[0], "セマフォ"), "セマフォ待ち表の セマフォ 番目");
		  kpush(arr, self->f[7], "セマフォ待ち表の セマフォ 番目");
		}
	}
	kstep(&KF[11], 240, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "clkhandler", a, 0);
	}
}

static void kh0_12(struct kact *self, kv arg) {
	kv L[2];
	int32 i;
	(void)L;
	for (i = 0; i < 2; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[12], 243, self, L);
	{ kv v = ks("OK");
	  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
	}
	kstep(&KF[12], 244, self, L);
	if (klt(kget(self->f[17], kread(L[0], "セマフォ"), "セマフォ数表の セマフォ 番目"), kn(0), "セマフォ数表の セマフォ 番目", "0")) {
		kstep(&KF[12], 245, self, L);
		L[1] = kshift(kget(self->f[18], kread(L[0], "セマフォ"), "セマフォ待ち表の セマフォ 番目"), "セマフォ待ち表の セマフォ 番目");
		kstep(&KF[12], 246, self, L);
		{ kv a = kread(L[1], "起こすpid");
		  ksend(kactv(self), "ready", a, 1);
		}
	}
	kstep(&KF[12], 248, self, L);
	{ kv v = kadd(kget(self->f[17], kread(L[0], "セマフォ"), "セマフォ数表の セマフォ 番目"), kn(1), "（セマフォ数表の セマフォ 番目 足す 1）");
	  kset(self->f[17], kread(L[0], "セマフォ"), v, "セマフォ数表の セマフォ 番目");
	}
	kstep(&KF[12], 249, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "clkhandler", a, 0);
	}
}

static void kh0_13(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[13], 252, self, L);
	{ kv v = kget(kread(L[0], "依頼"), kn(1), "依頼の 1 番目");
	  self->f[21] = v;
	}
	kstep(&KF[13], 253, self, L);
	{ kv v = ks("OK");
	  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
	}
	kstep(&KF[13], 254, self, L);
	if (keq(kget(self->f[6], self->f[21], "伝言あり表の 相手 番目"), kb(1))) {
		kstep(&KF[13], 255, self, L);
		{ kv v = ks("SYSERR");
		  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
		}
	} else {
		kstep(&KF[13], 257, self, L);
		{ kv v = kget(kread(L[0], "依頼"), kn(2), "依頼の 2 番目");
		  kset(self->f[5], self->f[21], v, "伝言表の 相手 番目");
		}
		kstep(&KF[13], 258, self, L);
		{ kv v = kb(1);
		  kset(self->f[6], self->f[21], v, "伝言あり表の 相手 番目");
		}
		kstep(&KF[13], 259, self, L);
		if (keq(kget(self->f[0], self->f[21], "状態表の 相手 番目"), ks("RECV"))) {
			kstep(&KF[13], 260, self, L);
			{ kv v = kget(kread(L[0], "依頼"), kn(2), "依頼の 2 番目");
			  kset(self->f[4], self->f[21], v, "戻り値表の 相手 番目");
			}
			kstep(&KF[13], 261, self, L);
			{ kv v = kb(0);
			  kset(self->f[6], self->f[21], v, "伝言あり表の 相手 番目");
			}
			kstep(&KF[13], 262, self, L);
			{ kv a = self->f[21];
			  ksend(kactv(self), "ready", a, 1);
			}
		}
	}
	kstep(&KF[13], 265, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "clkhandler", a, 0);
	}
}

static void kh0_14(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[14], 268, self, L);
	if (keq(kget(self->f[6], self->f[7], "伝言あり表の 実行中 番目"), kb(1))) {
		kstep(&KF[14], 269, self, L);
		{ kv v = kget(self->f[5], self->f[7], "伝言表の 実行中 番目");
		  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
		}
		kstep(&KF[14], 270, self, L);
		{ kv v = kb(0);
		  kset(self->f[6], self->f[7], v, "伝言あり表の 実行中 番目");
		}
	} else {
		kstep(&KF[14], 272, self, L);
		{ kv v = ks("RECV");
		  kset(self->f[0], self->f[7], v, "状態表の 実行中 番目");
		}
	}
	kstep(&KF[14], 274, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "clkhandler", a, 0);
	}
}

static void kh0_15(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[15], 277, self, L);
	{ kv v = self->f[7];
	  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
	}
	kstep(&KF[15], 278, self, L);
	{ kv a = knone();
	  ksend(kactv(self), "clkhandler", a, 0);
	}
}

static void kh0_16(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[16], 281, self, L);
	{ kv v = kb(0);
	  self->f[29] = v;
	}
	kstep(&KF[16], 282, self, L);
	if (keq(kread(L[0], "pid"), kn(1))) {
		kstep(&KF[16], 283, self, L);
		{ kv v = kb(1);
		  self->f[29] = v;
		}
	}
	kstep(&KF[16], 285, self, L);
	if (keq(kget(self->f[0], kread(L[0], "pid"), "状態表の pid 番目"), ks("FREE"))) {
		kstep(&KF[16], 286, self, L);
		{ kv v = kb(1);
		  self->f[29] = v;
		}
	}
	kstep(&KF[16], 288, self, L);
	if (keq(self->f[29], kb(1))) {
		kstep(&KF[16], 289, self, L);
		{ kv v = ks("SYSERR");
		  kset(self->f[4], self->f[7], v, "戻り値表の 実行中 番目");
		}
		kstep(&KF[16], 290, self, L);
		{ kv a = knone();
		  ksend(kactv(self), "clkhandler", a, 0);
		}
	} else {
		kstep(&KF[16], 292, self, L);
		{ kv v = ksub(self->f[8], kn(1), "（プロセス数 引く 1）");
		  self->f[8] = v;
		}
		kstep(&KF[16], 293, self, L);
		{ kv v = knewarr();
		  self->f[25] = v;
		}
		kstep(&KF[16], 294, self, L);
		{ int32 n12, h13 = knum(klen(self->f[10], "準備リスト の要素数"), "（準備リスト の要素数）");
		  for (n12 = knum(kn(1), "1"); n12 <= h13; n12++) {
			kstep(&KF[16], 295, self, L);
			if (!keq(kget(self->f[10], kn(n12), "準備リストの 現在の番号 番目"), kread(L[0], "pid"))) {
				kstep(&KF[16], 296, self, L);
				{ kv arr = self->f[25];
				  kpush(arr, kget(self->f[10], kn(n12), "準備リストの 現在の番号 番目"), "新リスト");
				}
			}
		} }
		kstep(&KF[16], 299, self, L);
		{ kv v = self->f[25];
		  self->f[10] = v;
		}
		kstep(&KF[16], 300, self, L);
		{ kv v = ks("FREE");
		  kset(self->f[0], kread(L[0], "pid"), v, "状態表の pid 番目");
		}
		kstep(&KF[16], 301, self, L);
		{ kv v = kb(0);
		  kset(self->f[6], kread(L[0], "pid"), v, "伝言あり表の pid 番目");
		}
		kstep(&KF[16], 302, self, L);
		if (klt(self->f[8], kn(2), "プロセス数", "2")) {
			kstep(&KF[16], 303, self, L);
			{ kv a = knone();
			  ksend(kactv(self), "xdone", a, 0);
			}
		} else {
			kstep(&KF[16], 305, self, L);
			{ kv a = knone();
			  ksend(kactv(self), "clkhandler", a, 0);
			}
		}
	}
}

static void kh0_17(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[17], 310, self, L);
	{ kv a = self->f[7];
	  ksend(kactv(self), "kill", a, 1);
	}
}

static void kh0_18(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	kstep(&KF[18], 313, self, L);
	{ static const int32 lit[1] = { 1 };
	  kv vals[1];
	  vals[0] = ks("All user processes have completed.");
	  kdisp(1, lit, vals); }
}

static const char *kf0[] = { "状態表", "優先度表", "名前表", "本体表", "戻り値表", "伝言表", "伝言あり表", "実行中", "プロセス数", "次pid", "準備リスト", "眠りリスト", "眠り鍵", "刻み残り", "時刻", "要再スケジュール", "セマフォ状態表", "セマフォ数表", "セマフォ待ち表", "新番号", "古", "相手", "鍵", "残り", "入れた", "新リスト", "新鍵", "待ち列", "起こす", "止め", "位置", "切替表示" };
static const struct khent kht0[] = { { "nulluser", kh0_0 }, { "create", kh0_1 }, { "resume", kh0_2 }, { "ready", kh0_3 }, { "resched", kh0_4 }, { "ctxsw", kh0_5 }, { "戻る", kh0_6 }, { "clkhandler", kh0_7 }, { "wakeup", kh0_8 }, { "sleepms", kh0_9 }, { "semcreate", kh0_10 }, { "wait", kh0_11 }, { "signal", kh0_12 }, { "send", kh0_13 }, { "receive", kh0_14 }, { "getpid", kh0_15 }, { "kill", kh0_16 }, { "exit", kh0_17 }, { "xdone", kh0_18 } };
static struct kclass kcls0 = { "カーネル", 32, kf0, kinit0, 19, kht0, 0 };

static void kinit1(struct kact *self) {
	self->f[3] = kn(0);
}

static void kh1_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[19], 323, self, L);
	{ kv v = kget(kread(L[0], "組"), kn(1), "組の 1 番目");
	  self->f[0] = v;
	}
	kstep(&KF[19], 324, self, L);
	{ kv v = kget(kread(L[0], "組"), kn(2), "組の 2 番目");
	  self->f[1] = v;
	}
	kstep(&KF[19], 325, self, L);
	{ kv v = kget(kread(L[0], "組"), kn(3), "組の 3 番目");
	  self->f[2] = v;
	}
}

static void kh1_1(struct kact *self, kv arg) {
	kv L[2];
	int32 i;
	(void)L;
	for (i = 0; i < 2; i++) L[i].t = KN_UNSET;
	L[1] = arg;
	kstep(&KF[20], 328, self, L);
	if (keq(self->f[3], kn(0))) {
		kstep(&KF[20], 329, self, L);
		{ kv v = kn(1);
		  self->f[3] = v;
		}
		kstep(&KF[20], 330, self, L);
		L[0] = knewarr();
		kstep(&KF[20], 331, self, L);
		{ kv arr = kread(L[0], "組");
		  kpush(arr, self->f[2], "組");
		  kpush(arr, kn(65536), "組");
		  kpush(arr, kn(20), "組");
		  kpush(arr, ks("Main process"), "組");
		  kpush(arr, knewarr(), "組");
		}
		kstep(&KF[20], 332, self, L);
		{ kv a = kread(L[0], "組");
		  ksend(self->f[0], "create", a, 1);
		}
	} else {
		kstep(&KF[20], 334, self, L);
		if (keq(self->f[3], kn(1))) {
			kstep(&KF[20], 335, self, L);
			{ kv v = kn(2);
			  self->f[3] = v;
			}
			kstep(&KF[20], 336, self, L);
			{ kv a = kread(L[1], "戻り値");
			  ksend(self->f[0], "resume", a, 1);
			}
		} else {
			kstep(&KF[20], 338, self, L);
			{ kv a = knone();
			  ksend(self->f[0], "clkhandler", a, 0);
			}
		}
	}
}

static const char *kf1[] = { "核", "pid", "メイン", "段階" };
static const struct khent kht1[] = { { "生まれた", kh1_0 }, { "走れ", kh1_1 } };
static struct kclass kcls1 = { "ヌル係", 4, kf1, kinit1, 2, kht1, 0 };

static void kinit2(struct kact *self) {
	self->f[2] = kn(0);
}

static void kh2_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[21], 350, self, L);
	{ kv v = kget(kread(L[0], "組"), kn(1), "組の 1 番目");
	  self->f[0] = v;
	}
	kstep(&KF[21], 351, self, L);
	{ kv v = kget(kread(L[0], "組"), kn(2), "組の 2 番目");
	  self->f[1] = v;
	}
}

static void kh2_1(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[22], 354, self, L);
	self->f[2] = kadd(self->f[2], kn(1), "段階");
	kstep(&KF[22], 355, self, L);
	if (keq(self->f[2], kn(1))) {
		kstep(&KF[22], 356, self, L);
		{ static const int32 lit[1] = { 1 };
		  kv vals[1];
		  vals[0] = ks("=== Sample: two greeter processes running concurrently ===");
		  kdisp(1, lit, vals); }
		kstep(&KF[22], 357, self, L);
		self->f[3] = knew(&kcls3);
		kstep(&KF[22], 358, self, L);
		{ kv v = knewarr();
		  self->f[8] = v;
		}
		kstep(&KF[22], 359, self, L);
		{ kv arr = self->f[8];
		  kpush(arr, ks("Alice"), "引数");
		  kpush(arr, kn(3), "引数");
		}
		kstep(&KF[22], 360, self, L);
		{ kv v = knewarr();
		  self->f[7] = v;
		}
		kstep(&KF[22], 361, self, L);
		{ kv arr = self->f[7];
		  kpush(arr, self->f[3], "組");
		  kpush(arr, kn(4096), "組");
		  kpush(arr, kn(50), "組");
		  kpush(arr, ks("greeter-A"), "組");
		  kpush(arr, self->f[8], "組");
		}
		kstep(&KF[22], 362, self, L);
		{ kv a = self->f[7];
		  ksend(self->f[0], "create", a, 1);
		}
	}
	kstep(&KF[22], 364, self, L);
	if (keq(self->f[2], kn(2))) {
		kstep(&KF[22], 365, self, L);
		{ kv v = kread(L[0], "戻り値");
		  self->f[5] = v;
		}
		kstep(&KF[22], 366, self, L);
		self->f[4] = knew(&kcls3);
		kstep(&KF[22], 367, self, L);
		{ kv v = knewarr();
		  self->f[8] = v;
		}
		kstep(&KF[22], 368, self, L);
		{ kv arr = self->f[8];
		  kpush(arr, ks("Bob"), "引数");
		  kpush(arr, kn(3), "引数");
		}
		kstep(&KF[22], 369, self, L);
		{ kv v = knewarr();
		  self->f[7] = v;
		}
		kstep(&KF[22], 370, self, L);
		{ kv arr = self->f[7];
		  kpush(arr, self->f[4], "組");
		  kpush(arr, kn(4096), "組");
		  kpush(arr, kn(50), "組");
		  kpush(arr, ks("greeter-B"), "組");
		  kpush(arr, self->f[8], "組");
		}
		kstep(&KF[22], 371, self, L);
		{ kv a = self->f[7];
		  ksend(self->f[0], "create", a, 1);
		}
	}
	kstep(&KF[22], 373, self, L);
	if (keq(self->f[2], kn(3))) {
		kstep(&KF[22], 374, self, L);
		{ kv v = kread(L[0], "戻り値");
		  self->f[6] = v;
		}
		kstep(&KF[22], 375, self, L);
		{ kv a = self->f[5];
		  ksend(self->f[0], "resume", a, 1);
		}
	}
	kstep(&KF[22], 377, self, L);
	if (keq(self->f[2], kn(4))) {
		kstep(&KF[22], 378, self, L);
		{ kv a = self->f[6];
		  ksend(self->f[0], "resume", a, 1);
		}
	}
	kstep(&KF[22], 380, self, L);
	if (keq(self->f[2], kn(5))) {
		kstep(&KF[22], 381, self, L);
		{ kv a = kn(2500);
		  ksend(self->f[0], "sleepms", a, 1);
		}
	}
	kstep(&KF[22], 383, self, L);
	if (keq(self->f[2], kn(6))) {
		kstep(&KF[22], 384, self, L);
		{ static const int32 lit[1] = { 1 };
		  kv vals[1];
		  vals[0] = ks("=== Sample finished, starting shell ===");
		  kdisp(1, lit, vals); }
		kstep(&KF[22], 385, self, L);
		{ kv a = knone();
		  ksend(self->f[0], "exit", a, 0);
		}
	}
}

static const char *kf2[] = { "核", "pid", "段階", "甲", "乙", "g1", "g2", "組", "引数" };
static const struct khent kht2[] = { { "生まれた", kh2_0 }, { "走れ", kh2_1 } };
static struct kclass kcls2 = { "メイン係", 9, kf2, kinit2, 2, kht2, 0 };

static void kinit3(struct kact *self) {
	self->f[4] = kn(0);
}

static void kh3_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[23], 396, self, L);
	{ kv v = kget(kread(L[0], "組"), kn(1), "組の 1 番目");
	  self->f[0] = v;
	}
	kstep(&KF[23], 397, self, L);
	{ kv v = kget(kread(L[0], "組"), kn(2), "組の 2 番目");
	  self->f[1] = v;
	}
	kstep(&KF[23], 398, self, L);
	{ kv v = kget(kread(L[0], "組"), kn(3), "組の 3 番目");
	  self->f[5] = v;
	}
	kstep(&KF[23], 399, self, L);
	{ kv v = kget(self->f[5], kn(1), "引数の 1 番目");
	  self->f[2] = v;
	}
	kstep(&KF[23], 400, self, L);
	{ kv v = kget(self->f[5], kn(2), "引数の 2 番目");
	  self->f[3] = v;
	}
}

static void kh3_1(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	kstep(&KF[24], 403, self, L);
	self->f[4] = kadd(self->f[4], kn(1), "回目");
	kstep(&KF[24], 404, self, L);
	if (klt(self->f[4], kadd(self->f[3], kn(1), "（回数 足す 1）"), "回目", "（回数 足す 1）")) {
		kstep(&KF[24], 405, self, L);
		{ static const int32 lit[7] = { 1, 0, 1, 0, 1, 0, 1 };
		  kv vals[7];
		  vals[0] = ks("[");
		  vals[1] = self->f[2];
		  vals[2] = ks("] hello from Xinu! (");
		  vals[3] = self->f[4];
		  vals[4] = ks("/");
		  vals[5] = self->f[3];
		  vals[6] = ks(")");
		  kdisp(7, lit, vals); }
		kstep(&KF[24], 406, self, L);
		{ kv a = kn(300);
		  ksend(self->f[0], "sleepms", a, 1);
		}
	} else {
		kstep(&KF[24], 408, self, L);
		{ kv a = knone();
		  ksend(self->f[0], "exit", a, 0);
		}
	}
}

static const char *kf3[] = { "核", "pid", "呼び名", "回数", "回目", "引数" };
static const struct khent kht3[] = { { "生まれた", kh3_0 }, { "走れ", kh3_1 } };
static struct kclass kcls3 = { "挨拶係", 6, kf3, kinit3, 2, kht3, 0 };

static void kbody(void) {
	struct kact *self = NULL; (void)self;
	kv L[4];
	int32 i;
	(void)L;
	for (i = 0; i < 4; i++) L[i].t = KN_UNSET;
	kstep(&KF[25], 414, self, L);
	L[0] = knew(&kcls0);
	kstep(&KF[25], 415, self, L);
	L[1] = knew(&kcls1);
	kstep(&KF[25], 416, self, L);
	L[2] = knew(&kcls2);
	kstep(&KF[25], 417, self, L);
	L[3] = knewarr();
	kstep(&KF[25], 418, self, L);
	{ kv arr = kread(L[3], "起動");
	  kpush(arr, kread(L[1], "ヌル"), "起動");
	  kpush(arr, kread(L[2], "メイン"), "起動");
	}
	kstep(&KF[25], 419, self, L);
	{ kv a = kread(L[3], "起動");
	  ksend(kread(L[0], "核"), "nulluser", a, 1);
	}
}

static const char *KS0[] = { "起動" };
static const char *KS1[] = { "依頼" };
static const char *KS2[] = { "pid" };
static const char *KS3[] = { "pid" };
static const char *KS4[] = { "" };
static const char *KS5[] = { "前" };
static const char *KS6[] = { "" };
static const char *KS7[] = { "" };
static const char *KS8[] = { "起こすpid" };
static const char *KS9[] = { "長さ" };
static const char *KS10[] = { "個数" };
static const char *KS11[] = { "セマフォ" };
static const char *KS12[] = { "セマフォ", "起こすpid" };
static const char *KS13[] = { "依頼" };
static const char *KS14[] = { "" };
static const char *KS15[] = { "" };
static const char *KS16[] = { "pid" };
static const char *KS17[] = { "" };
static const char *KS18[] = { "" };
static const char *KS19[] = { "組" };
static const char *KS20[] = { "組", "戻り値" };
static const char *KS21[] = { "組" };
static const char *KS22[] = { "戻り値" };
static const char *KS23[] = { "組" };
static const char *KS24[] = { "" };
static const char *KS25[] = { "核", "ヌル", "メイン", "起動" };
static struct kfun KF[26] = {
	{ &kp7_prog, 0, "nulluser", 25, 49, 1, KS0 },
	{ &kp7_prog, 0, "create", 50, 76, 1, KS1 },
	{ &kp7_prog, 0, "resume", 77, 85, 1, KS2 },
	{ &kp7_prog, 0, "ready", 86, 102, 1, KS3 },
	{ &kp7_prog, 0, "resched", 103, 127, 0, KS4 },
	{ &kp7_prog, 0, "ctxsw", 128, 133, 1, KS5 },
	{ &kp7_prog, 0, "戻る", 134, 136, 0, KS6 },
	{ &kp7_prog, 0, "clkhandler", 137, 162, 0, KS7 },
	{ &kp7_prog, 0, "wakeup", 163, 177, 1, KS8 },
	{ &kp7_prog, 0, "sleepms", 178, 214, 1, KS9 },
	{ &kp7_prog, 0, "semcreate", 215, 232, 1, KS10 },
	{ &kp7_prog, 0, "wait", 233, 241, 1, KS11 },
	{ &kp7_prog, 0, "signal", 242, 250, 2, KS12 },
	{ &kp7_prog, 0, "send", 251, 266, 1, KS13 },
	{ &kp7_prog, 0, "receive", 267, 275, 0, KS14 },
	{ &kp7_prog, 0, "getpid", 276, 279, 0, KS15 },
	{ &kp7_prog, 0, "kill", 280, 308, 1, KS16 },
	{ &kp7_prog, 0, "exit", 309, 311, 0, KS17 },
	{ &kp7_prog, 0, "xdone", 312, 314, 0, KS18 },
	{ &kp7_prog, 1, "生まれた", 322, 326, 1, KS19 },
	{ &kp7_prog, 1, "走れ", 327, 341, 2, KS20 },
	{ &kp7_prog, 2, "生まれた", 349, 352, 1, KS21 },
	{ &kp7_prog, 2, "走れ", 353, 387, 1, KS22 },
	{ &kp7_prog, 3, "生まれた", 395, 401, 1, KS23 },
	{ &kp7_prog, 3, "走れ", 402, 410, 0, KS24 },
	{ &kp7_prog, -1, "実行部", 413, 420, 4, KS25 },
};

static const char *KL[421] = {
	"「カーネル」というアクターを定義する。",
	"    状態は 状態表、優先度表、名前表、本体表、戻り値表、伝言表、伝言あり表、実行中、プロセス数、次pid、準備リスト、眠りリスト、眠り鍵、刻み残り、時刻、要再スケジュール、セマフォ状態表、セマフォ数表、セマフォ待ち表、新番号、古、相手、鍵、残り、入れた、新リスト、新鍵、待ち列、起こす、止め、位置、切替表示。",
	"    初期状態は",
	"        状態表 は 空。",
	"        優先度表 は 空。",
	"        名前表 は 空。",
	"        本体表 は 空。",
	"        戻り値表 は 空。",
	"        伝言表 は 空。",
	"        伝言あり表 は 空。",
	"        準備リスト は 空。",
	"        眠りリスト は 空。",
	"        眠り鍵 は 空。",
	"        セマフォ状態表 は 空。",
	"        セマフォ数表 は 空。",
	"        セマフォ待ち表 は 空。",
	"        実行中 は 1。",
	"        プロセス数 は 0。",
	"        次pid は 1。",
	"        時刻 は 0。",
	"        刻み残り は 2。",
	"        要再スケジュール は いいえ。",
	"        切替表示 は いいえ。",
	"    以上。",
	"    「nulluser」と 起動 を受け取ったとき、",
	"        1から8まで繰り返す。",
	"            状態表 に 「FREE」 を追加する。",
	"            優先度表 に 0 を追加する。",
	"            名前表 に 「-」 を追加する。",
	"            本体表 に なし を追加する。",
	"            戻り値表 に 0 を追加する。",
	"            伝言表 に 0 を追加する。",
	"            伝言あり表 に いいえ を追加する。",
	"            セマフォ状態表 に 「FREE」 を追加する。",
	"            セマフォ数表 に 0 を追加する。",
	"            待ち列 は 空の配列。",
	"            セマフォ待ち表 に 待ち列 を追加する。",
	"        以上。",
	"        状態表の 1 番目 は 「CURR」。",
	"        名前表の 1 番目 は 「prnull」。",
	"        本体表の 1 番目 は 起動の 1 番目。",
	"        プロセス数 は 1。",
	"        実行中 は 1。",
	"        「Xinu（ことのは版）: 核を初期化した。NPROC 8、NSEM 8、1刻み 100 ミリ秒」 を表示する。",
	"        相手 は 空の配列。",
	"        相手 に 自分 と 1 と 起動の 2 番目 を追加する。",
	"        起動の 1 番目 に「生まれた」と 相手 を送る。",
	"        自分 に「戻る」を送る。",
	"    以上。",
	"    「create」と 依頼 を受け取ったとき、",
	"        新番号 は なし。",
	"        1から8まで繰り返す。",
	"            もし 新番号 が なし ならば、",
	"                次pid は （次pid を 8 で割った余り）。",
	"                次pid は 次pid 足す 1。",
	"                もし 状態表の 次pid 番目 が 「FREE」 ならば、",
	"                    新番号 は 次pid。",
	"                以上。",
	"            以上。",
	"        以上。",
	"        もし 新番号 が なし ならば、",
	"            戻り値表の 実行中 番目 は 「SYSERR」。",
	"        そうでなければ、",
	"            状態表の 新番号 番目 は 「SUSP」。",
	"            優先度表の 新番号 番目 は 依頼の 3 番目。",
	"            名前表の 新番号 番目 は 依頼の 4 番目。",
	"            本体表の 新番号 番目 は 依頼の 1 番目。",
	"            伝言あり表の 新番号 番目 は いいえ。",
	"            プロセス数 は プロセス数 足す 1。",
	"            相手 は 空の配列。",
	"            相手 に 自分 と 新番号 と 依頼の 5 番目 を追加する。",
	"            依頼の 1 番目 に「生まれた」と 相手 を送る。",
	"            戻り値表の 実行中 番目 は 新番号。",
	"        以上。",
	"        自分 に「clkhandler」を送る。",
	"    以上。",
	"    「resume」と pid を受け取ったとき、",
	"        もし 状態表の pid 番目 が 「SUSP」 でない ならば、",
	"            戻り値表の 実行中 番目 は 「SYSERR」。",
	"        そうでなければ、",
	"            戻り値表の 実行中 番目 は 優先度表の pid 番目。",
	"            自分 に「ready」と pid を送る。",
	"        以上。",
	"        自分 に「clkhandler」を送る。",
	"    以上。",
	"    「ready」と pid を受け取ったとき、",
	"        状態表の pid 番目 は 「READY」。",
	"        要再スケジュール は はい。",
	"        準備リスト に pid を追加する。",
	"        止め は いいえ。",
	"        1から（準備リスト の要素数 引く 1）まで繰り返す。",
	"            もし 止め が いいえ ならば、",
	"                位置 は （準備リスト の要素数 引く 現在の番号）。",
	"                もし 優先度表の 準備リストの 位置 番目 番目 が 優先度表の pid 番目 より小さい ならば、",
	"                    準備リストの （位置 足す 1） 番目 は 準備リストの 位置 番目。",
	"                    準備リストの 位置 番目 は pid。",
	"                そうでなければ、",
	"                    止め は はい。",
	"                以上。",
	"            以上。",
	"        以上。",
	"    以上。",
	"    「resched」を受け取ったとき、",
	"        要再スケジュール は いいえ。",
	"        刻み残り は 2。",
	"        止め は いいえ。",
	"        もし 状態表の 実行中 番目 が 「CURR」 ならば、",
	"            もし 準備リスト が 空 ならば、",
	"                止め は はい。",
	"            そうでなければ、",
	"                もし 優先度表の 準備リストの 1 番目 番目 が 優先度表の 実行中 番目 より小さい ならば、",
	"                    止め は はい。",
	"                以上。",
	"            以上。",
	"            もし 止め が はい ならば、",
	"                自分 に「戻る」を送る。",
	"            そうでなければ、",
	"                自分 に「ready」と 実行中 を送る。",
	"                自分 に「resched」を送る。",
	"            以上。",
	"        そうでなければ、",
	"            古 は 実行中。",
	"            実行中 は 準備リスト の先頭を取り出す。",
	"            状態表の 実行中 番目 は 「CURR」。",
	"            自分 に「ctxsw」と 古 を送る。",
	"        以上。",
	"    以上。",
	"    「ctxsw」と 前 を受け取ったとき、",
	"        もし 切替表示 が はい ならば、",
	"            「〔ctxsw〕」 と 名前表の 前 番目 と 「→」 と 名前表の 実行中 番目 を表示する。",
	"        以上。",
	"        本体表の 実行中 番目 に「走れ」と 戻り値表の 実行中 番目 を送る。",
	"    以上。",
	"    「戻る」を受け取ったとき、",
	"        本体表の 実行中 番目 に「走れ」と 戻り値表の 実行中 番目 を送る。",
	"    以上。",
	"    「clkhandler」を受け取ったとき、",
	"        時刻 は 時刻 足す 100。",
	"        刻み残り は （刻み残り 引く 1）。",
	"        起こす は いいえ。",
	"        もし 状態表の 実行中 番目 が 「CURR」 でない ならば、",
	"            要再スケジュール は はい。",
	"        以上。",
	"        もし 刻み残り が 1 より小さい ならば、",
	"            要再スケジュール は はい。",
	"        以上。",
	"        もし 眠りリスト が 空 でない ならば、",
	"            眠り鍵の 1 番目 は （眠り鍵の 1 番目 引く 100）。",
	"            もし 眠り鍵の 1 番目 が 1 より小さい ならば、",
	"                起こす は はい。",
	"            以上。",
	"        以上。",
	"        もし 起こす が はい ならば、",
	"            自分 に「wakeup」を送る。",
	"        そうでなければ、",
	"            もし 要再スケジュール が はい ならば、",
	"                自分 に「resched」を送る。",
	"            そうでなければ、",
	"                自分 に「戻る」を送る。",
	"            以上。",
	"        以上。",
	"    以上。",
	"    「wakeup」を受け取ったとき、",
	"        1から8まで繰り返す。",
	"            もし 眠りリスト が 空 でない ならば、",
	"                もし 眠り鍵の 1 番目 が 1 より小さい ならば、",
	"                    起こすpid は 眠りリスト の先頭を取り出す。",
	"                    鍵 は 眠り鍵 の先頭を取り出す。",
	"                    もし 眠りリスト が 空 でない ならば、",
	"                        眠り鍵の 1 番目 は （眠り鍵の 1 番目 足す 鍵）。",
	"                    以上。",
	"                    自分 に「ready」と 起こすpid を送る。",
	"                以上。",
	"            以上。",
	"        以上。",
	"        自分 に「resched」を送る。",
	"    以上。",
	"    「sleepms」と 長さ を受け取ったとき、",
	"        戻り値表の 実行中 番目 は 「OK」。",
	"        もし 長さ が 1 より小さい ならば、",
	"            自分 に「clkhandler」を送る。",
	"        そうでなければ、",
	"            残り は 長さ。",
	"            入れた は いいえ。",
	"            新リスト は 空の配列。",
	"            新鍵 は 空の配列。",
	"            1から（眠りリスト の要素数）まで繰り返す。",
	"                もし 入れた が いいえ ならば、",
	"                    もし 残り が 眠り鍵の 現在の番号 番目 より小さい ならば、",
	"                        新リスト に 実行中 を追加する。",
	"                        新鍵 に 残り を追加する。",
	"                        入れた は はい。",
	"                        新リスト に 眠りリストの 現在の番号 番目 を追加する。",
	"                        新鍵 に （眠り鍵の 現在の番号 番目 引く 残り） を追加する。",
	"                    そうでなければ、",
	"                        残り は （残り 引く 眠り鍵の 現在の番号 番目）。",
	"                        新リスト に 眠りリストの 現在の番号 番目 を追加する。",
	"                        新鍵 に 眠り鍵の 現在の番号 番目 を追加する。",
	"                    以上。",
	"                そうでなければ、",
	"                    新リスト に 眠りリストの 現在の番号 番目 を追加する。",
	"                    新鍵 に 眠り鍵の 現在の番号 番目 を追加する。",
	"                以上。",
	"            以上。",
	"            もし 入れた が いいえ ならば、",
	"                新リスト に 実行中 を追加する。",
	"                新鍵 に 残り を追加する。",
	"            以上。",
	"            眠りリスト は 新リスト。",
	"            眠り鍵 は 新鍵。",
	"            状態表の 実行中 番目 は 「SLEEP」。",
	"            自分 に「clkhandler」を送る。",
	"        以上。",
	"    以上。",
	"    「semcreate」と 個数 を受け取ったとき、",
	"        新番号 は なし。",
	"        1から8まで繰り返す。",
	"            もし 新番号 が なし ならば、",
	"                もし セマフォ状態表の 現在の番号 番目 が 「FREE」 ならば、",
	"                    新番号 は 現在の番号。",
	"                以上。",
	"            以上。",
	"        以上。",
	"        もし 新番号 が なし ならば、",
	"            戻り値表の 実行中 番目 は 「SYSERR」。",
	"        そうでなければ、",
	"            セマフォ状態表の 新番号 番目 は 「USED」。",
	"            セマフォ数表の 新番号 番目 は 個数。",
	"            戻り値表の 実行中 番目 は 新番号。",
	"        以上。",
	"        自分 に「clkhandler」を送る。",
	"    以上。",
	"    「wait」と セマフォ を受け取ったとき、",
	"        戻り値表の 実行中 番目 は 「OK」。",
	"        セマフォ数表の セマフォ 番目 は （セマフォ数表の セマフォ 番目 引く 1）。",
	"        もし セマフォ数表の セマフォ 番目 が 0 より小さい ならば、",
	"            状態表の 実行中 番目 は 「WAIT」。",
	"            セマフォ待ち表の セマフォ 番目 に 実行中 を追加する。",
	"        以上。",
	"        自分 に「clkhandler」を送る。",
	"    以上。",
	"    「signal」と セマフォ を受け取ったとき、",
	"        戻り値表の 実行中 番目 は 「OK」。",
	"        もし セマフォ数表の セマフォ 番目 が 0 より小さい ならば、",
	"            起こすpid は セマフォ待ち表の セマフォ 番目 の先頭を取り出す。",
	"            自分 に「ready」と 起こすpid を送る。",
	"        以上。",
	"        セマフォ数表の セマフォ 番目 は （セマフォ数表の セマフォ 番目 足す 1）。",
	"        自分 に「clkhandler」を送る。",
	"    以上。",
	"    「send」と 依頼 を受け取ったとき、",
	"        相手 は 依頼の 1 番目。",
	"        戻り値表の 実行中 番目 は 「OK」。",
	"        もし 伝言あり表の 相手 番目 が はい ならば、",
	"            戻り値表の 実行中 番目 は 「SYSERR」。",
	"        そうでなければ、",
	"            伝言表の 相手 番目 は 依頼の 2 番目。",
	"            伝言あり表の 相手 番目 は はい。",
	"            もし 状態表の 相手 番目 が 「RECV」 ならば、",
	"                戻り値表の 相手 番目 は 依頼の 2 番目。",
	"                伝言あり表の 相手 番目 は いいえ。",
	"                自分 に「ready」と 相手 を送る。",
	"            以上。",
	"        以上。",
	"        自分 に「clkhandler」を送る。",
	"    以上。",
	"    「receive」を受け取ったとき、",
	"        もし 伝言あり表の 実行中 番目 が はい ならば、",
	"            戻り値表の 実行中 番目 は 伝言表の 実行中 番目。",
	"            伝言あり表の 実行中 番目 は いいえ。",
	"        そうでなければ、",
	"            状態表の 実行中 番目 は 「RECV」。",
	"        以上。",
	"        自分 に「clkhandler」を送る。",
	"    以上。",
	"    「getpid」を受け取ったとき、",
	"        戻り値表の 実行中 番目 は 実行中。",
	"        自分 に「clkhandler」を送る。",
	"    以上。",
	"    「kill」と pid を受け取ったとき、",
	"        止め は いいえ。",
	"        もし pid が 1 ならば、",
	"            止め は はい。",
	"        以上。",
	"        もし 状態表の pid 番目 が 「FREE」 ならば、",
	"            止め は はい。",
	"        以上。",
	"        もし 止め が はい ならば、",
	"            戻り値表の 実行中 番目 は 「SYSERR」。",
	"            自分 に「clkhandler」を送る。",
	"        そうでなければ、",
	"            プロセス数 は （プロセス数 引く 1）。",
	"            新リスト は 空の配列。",
	"            1から（準備リスト の要素数）まで繰り返す。",
	"                もし 準備リストの 現在の番号 番目 が pid でない ならば、",
	"                    新リスト に 準備リストの 現在の番号 番目 を追加する。",
	"                以上。",
	"            以上。",
	"            準備リスト は 新リスト。",
	"            状態表の pid 番目 は 「FREE」。",
	"            伝言あり表の pid 番目 は いいえ。",
	"            もし プロセス数 が 2 より小さい ならば、",
	"                自分 に「xdone」を送る。",
	"            そうでなければ、",
	"                自分 に「clkhandler」を送る。",
	"            以上。",
	"        以上。",
	"    以上。",
	"    「exit」を受け取ったとき、",
	"        自分 に「kill」と 実行中 を送る。",
	"    以上。",
	"    「xdone」を受け取ったとき、",
	"        「All user processes have completed.」 を表示する。",
	"    以上。",
	"定義を終わる。",
	"",
	"「ヌル係」というアクターを定義する。",
	"    状態は 核、pid、メイン、段階。",
	"    初期状態は",
	"        段階 は 0。",
	"    以上。",
	"    「生まれた」と 組 を受け取ったとき、",
	"        核 は 組の 1 番目。",
	"        pid は 組の 2 番目。",
	"        メイン は 組の 3 番目。",
	"    以上。",
	"    「走れ」と 戻り値 を受け取ったとき、",
	"        もし 段階 が 0 ならば、",
	"            段階 は 1。",
	"            組 は 空の配列。",
	"            組 に メイン と 65536 と 20 と 「Main process」 と 空 を追加する。",
	"            核 に「create」と 組 を送る。",
	"        そうでなければ、",
	"            もし 段階 が 1 ならば、",
	"                段階 は 2。",
	"                核 に「resume」と 戻り値 を送る。",
	"            そうでなければ、",
	"                核 に「clkhandler」を送る。",
	"            以上。",
	"        以上。",
	"    以上。",
	"定義を終わる。",
	"",
	"「メイン係」というアクターを定義する。",
	"    状態は 核、pid、段階、甲、乙、g1、g2、組、引数。",
	"    初期状態は",
	"        段階 は 0。",
	"    以上。",
	"    「生まれた」と 組 を受け取ったとき、",
	"        核 は 組の 1 番目。",
	"        pid は 組の 2 番目。",
	"    以上。",
	"    「走れ」と 戻り値 を受け取ったとき、",
	"        段階 は 段階 足す 1。",
	"        もし 段階 が 1 ならば、",
	"            「=== Sample: two greeter processes running concurrently ===」 を表示する。",
	"            甲 は 「挨拶係」の新しいアクター。",
	"            引数 は 空の配列。",
	"            引数 に 「Alice」 と 3 を追加する。",
	"            組 は 空の配列。",
	"            組 に 甲 と 4096 と 50 と 「greeter-A」 と 引数 を追加する。",
	"            核 に「create」と 組 を送る。",
	"        以上。",
	"        もし 段階 が 2 ならば、",
	"            g1 は 戻り値。",
	"            乙 は 「挨拶係」の新しいアクター。",
	"            引数 は 空の配列。",
	"            引数 に 「Bob」 と 3 を追加する。",
	"            組 は 空の配列。",
	"            組 に 乙 と 4096 と 50 と 「greeter-B」 と 引数 を追加する。",
	"            核 に「create」と 組 を送る。",
	"        以上。",
	"        もし 段階 が 3 ならば、",
	"            g2 は 戻り値。",
	"            核 に「resume」と g1 を送る。",
	"        以上。",
	"        もし 段階 が 4 ならば、",
	"            核 に「resume」と g2 を送る。",
	"        以上。",
	"        もし 段階 が 5 ならば、",
	"            核 に「sleepms」と 2500 を送る。",
	"        以上。",
	"        もし 段階 が 6 ならば、",
	"            「=== Sample finished, starting shell ===」 を表示する。",
	"            核 に「exit」を送る。",
	"        以上。",
	"    以上。",
	"定義を終わる。",
	"",
	"「挨拶係」というアクターを定義する。",
	"    状態は 核、pid、呼び名、回数、回目、引数。",
	"    初期状態は",
	"        回目 は 0。",
	"    以上。",
	"    「生まれた」と 組 を受け取ったとき、",
	"        核 は 組の 1 番目。",
	"        pid は 組の 2 番目。",
	"        引数 は 組の 3 番目。",
	"        呼び名 は 引数の 1 番目。",
	"        回数 は 引数の 2 番目。",
	"    以上。",
	"    「走れ」と 戻り値 を受け取ったとき、",
	"        回目 は 回目 足す 1。",
	"        もし 回目 が （回数 足す 1） より小さい ならば、",
	"            「[」 と 呼び名 と 「] hello from Xinu! (」 と 回目 と 「/」 と 回数 と 「)」 を表示する。",
	"            核 に「sleepms」と 300 を送る。",
	"        そうでなければ、",
	"            核 に「exit」を送る。",
	"        以上。",
	"    以上。",
	"定義を終わる。",
	"",
	"実行を始める。",
	"    核 は 「カーネル」の新しいアクター。",
	"    ヌル は 「ヌル係」の新しいアクター。",
	"    メイン は 「メイン係」の新しいアクター。",
	"    起動 は 空の配列。",
	"    起動 に ヌル と メイン を追加する。",
	"    核 に「nulluser」と 起動 を送る。",
	"実行を終わる。",
	"",
};
static const unsigned char KST[422] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1,1,1,1,1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1,1,1,0,0,0,1,1,0,1,0,0,1,0,0,1,1,1,1,1,0,1,1,0,1,1,1,1,0,0,1,1,0,1,1,0,1,0,0,0,0,1,1,1,1,1,1,1,0,1,0,0,0,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,0,1,1,1,0,1,0,0,1,1,1,1,1,0,1,0,0,1,1,1,1,0,1,1,0,0,1,1,1,1,0,1,1,1,1,1,1,0,0,1,0,0,1,1,1,0,1,0,1,0,0,1,1,0,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0 };
static unsigned char KBP[422];
static const char *KSRC[320] = {
	"■ Xinu の核（カーネル）をことのはで書き直したもの",
	"※ 元は PC Xinu（~/projects/xinu-mac/xinu-vbox）の system/*.c。受信節の名前は Xinu の関数名そのまま。",
	"※ 書き直しの約束",
	"※ ・核は1つのアクター（カーネル）。Xinu の大域変数（proctab・readylist・sleepq・semtab …）はその状態。",
	"※   proctab[pid].prstate は「状態表の（pid）番目」、prprio は「優先度表の（pid）番目」のように、欄ごとの表にした。",
	"※ ・プロセス1つ＝アクター1つ。プロセスは「走れ」を受け取ると1歩だけ進み、必ず核へシステムコールを1つ送る。",
	"※   核はそれを処理し、次に走るプロセスへ「走れ」を送る（ctxsw）。だから走っているプロセスはいつも1つ。",
	"※   システムコールの戻り値は「走れ」に添えて渡す（Xinu ではプロセスごとの eax）。",
	"※ ・関数の中から別の関数を呼ぶところは、自分へのメッセージにした。受信箱は届いた順に処理するので、送った順に実行される。",
	"※ ・1歩＝時計の1刻み＝100ミリ秒。システムコールの出口では必ず clkhandler を通る。",
	"※   ready は準備リストに入れるだけで、resched は核の出口（clkhandler）でまとめて行う。",
	"※ ・プロセス番号（pid）は1から。1番がヌルプロセス（Xinu の 0 番）。表の大きさ NPROC と NSEM は 8。",
	"※ ・この版で省いたもの: メモリ管理・装置・ネットワーク・startup プロセス・suspend・kill の SLEEP/WAIT の場合。",
	"",
	"※【system/initialize.c】nulluser：表を作り、自分がヌルプロセスになる",
	"カーネルというアクターを定義する。",
	"カーネルは状態表と優先度表と名前表と本体表と戻り値表と伝言表と伝言あり表と実行中とプロセス数と次pidと準備リストと眠りリストと眠り鍵と刻み残りと時刻と要再スケジュールとセマフォ状態表とセマフォ数表とセマフォ待ち表と新番号と古と相手と鍵と残りと入れたと新リストと新鍵と待ち列と起こすと止めと位置と切替表示を持つ。",
	"状態表の初期値は空とし、優先度表の初期値は空とし、名前表の初期値は空とし、本体表の初期値は空とする。",
	"戻り値表の初期値は空とし、伝言表の初期値は空とし、伝言あり表の初期値は空とする。",
	"準備リストの初期値は空とし、眠りリストの初期値は空とし、眠り鍵の初期値は空とする。",
	"セマフォ状態表の初期値は空とし、セマフォ数表の初期値は空とし、セマフォ待ち表の初期値は空とする。",
	"実行中の初期値は1とし、プロセス数の初期値は0とし、次pidの初期値は1とし、時刻の初期値は0とする。",
	"刻み残りの初期値は2とし、要再スケジュールの初期値はいいえとし、切替表示の初期値はいいえとする。",
	"",
	"カーネルが「nulluser」というメッセージと起動を受け取ったとき、",
	"※ sysinit: プロセス表とセマフォ表を作る",
	"1から8までの各番号について、次のことを行う。",
	"「FREE」を状態表の末尾に追加し、0を優先度表の末尾に追加し、「-」を名前表の末尾に追加し、なしを本体表の末尾に追加する。",
	"0を戻り値表の末尾に追加し、0を伝言表の末尾に追加し、いいえを伝言あり表の末尾に追加する。",
	"「FREE」をセマフォ状態表の末尾に追加し、0をセマフォ数表の末尾に追加する。",
	"空の配列を用意し、待ち列と名付け、待ち列をセマフォ待ち表の末尾に追加する。",
	"以上。",
	"※ いま動いているこの流れがヌルプロセスになる（pid 1、優先度 0）",
	"状態表の1番目を「CURR」に設定し、名前表の1番目を「prnull」に設定し、本体表の1番目を起動の1番目に設定する。",
	"プロセス数を1に変更し、実行中を1に変更する。",
	"「Xinu（ことのは版）: 核を初期化した。NPROC 8、NSEM 8、1刻み 100 ミリ秒」という文字列を表示する。",
	"空の配列を用意し、相手と名付け、自分と1と起動の2番目を相手の末尾に追加し、起動の1番目に「生まれた」というメッセージと相手を送る。",
	"自分に「戻る」というメッセージを送る。",
	"",
	"※【system/create.c】create：プロセスを作る（止めたまま。走らせるのは resume）。newpid もここ",
	"カーネルが「create」というメッセージと依頼を受け取ったとき、",
	"※ 依頼＝[本体（プロセスのアクター）, スタックの大きさ, 優先度, 名前, 引数の配列]",
	"※ newpid: 前に渡した番号の次から、空いている番号を探す",
	"新番号をなしに変更する。",
	"1から8までの各番号について、次のことを行う。",
	"新番号がなしならば、次のことを行う。",
	"次pidを（次pidを8で割った余り）に変更し、次pidに1を加える。",
	"状態表の（次pid）番目が「FREE」ならば、新番号を次pidに変更する。",
	"以上。",
	"以上。",
	"新番号がなしならば、戻り値表の（実行中）番目を「SYSERR」に設定する。",
	"そうでなければ、次のことを行う。",
	"状態表の（新番号）番目を「SUSP」に設定し、優先度表の（新番号）番目を依頼の3番目に設定し、名前表の（新番号）番目を依頼の4番目に設定する。",
	"本体表の（新番号）番目を依頼の1番目に設定し、伝言あり表の（新番号）番目をいいえに設定し、プロセス数に1を加える。",
	"※ スタックに引数を積む代わりに、本体へ「生まれた」で核・pid・引数を渡す",
	"空の配列を用意し、相手と名付け、自分と新番号と依頼の5番目を相手の末尾に追加し、依頼の1番目に「生まれた」というメッセージと相手を送る。",
	"戻り値表の（実行中）番目を新番号に設定する。",
	"以上。",
	"自分に「clkhandler」というメッセージを送る。",
	"",
	"※【system/resume.c】resume：止めてあるプロセスを準備リストへ",
	"カーネルが「resume」というメッセージとpidを受け取ったとき、",
	"状態表の（pid）番目が「SUSP」でなければ、戻り値表の（実行中）番目を「SYSERR」に設定する。",
	"そうでなければ、戻り値表の（実行中）番目を優先度表の（pid）番目に設定し、自分に「ready」というメッセージとpidを送る。",
	"自分に「clkhandler」というメッセージを送る。",
	"",
	"※【system/ready.c】ready：準備リストへ優先度の順に入れる（同じ優先度なら後ろへ）",
	"カーネルが「ready」というメッセージとpidを受け取ったとき、",
	"状態表の（pid）番目を「READY」に設定し、要再スケジュールをはいに変更する。",
	"※ insert（insert.c）: 末尾に置いてから、自分より優先度の低いものの前まで繰り上げる",
	"pidを準備リストの末尾に追加し、止めをいいえに変更する。",
	"1から（準備リストの要素数から1を引いた数）までの各番号について、次のことを行う。",
	"止めがいいえならば、次のことを行う。",
	"位置を（準備リストの要素数から現在の番号を引いた数）に変更する。",
	"優先度表の（準備リストの（位置）番目）番目が優先度表の（pid）番目より小さければ、次のことを行う。",
	"準備リストの（位置に1を加えた数）番目を準備リストの（位置）番目に設定し、準備リストの（位置）番目をpidに設定する。",
	"以上。",
	"そうでなければ、止めをはいに変更する。",
	"以上。",
	"以上。",
	"",
	"※【system/resched.c】resched：次に走るプロセスを選ぶ",
	"カーネルが「resched」というメッセージを受け取ったとき、",
	"要再スケジュールをいいえに変更し、刻み残りを2に変更し、止めをいいえに変更する。",
	"状態表の（実行中）番目が「CURR」ならば、次のことを行う。",
	"※ 今のプロセスの方が優先度が高ければ、そのまま続ける（Xinu: prprio > firstkey(readylist)）",
	"準備リストが空ならば、止めをはいに変更する。",
	"そうでなければ、次のことを行う。",
	"優先度表の（準備リストの1番目）番目が優先度表の（実行中）番目より小さければ、止めをはいに変更する。",
	"以上。",
	"※ 譲るときは、今のプロセスを準備リストへ戻して（ready）、もう一度選び直す",
	"止めがはいならば、自分に「戻る」というメッセージを送る。",
	"そうでなければ、自分に「ready」というメッセージと実行中を送り、自分に「resched」というメッセージを送る。",
	"以上。",
	"そうでなければ、次のことを行う。",
	"古を実行中に変更し、準備リストの先頭から実行中を取り出し、状態表の（実行中）番目を「CURR」に設定する。",
	"自分に「ctxsw」というメッセージと古を送る。",
	"以上。",
	"",
	"※【system/ctxsw.S】ctxsw：切り替え。新しいプロセスに「走れ」を送り、システムコールの戻り値を渡す",
	"カーネルが「ctxsw」というメッセージと前を受け取ったとき、",
	"切替表示がはいならば、「〔ctxsw〕」と名前表の（前）番目と「→」と名前表の（実行中）番目を表示する。",
	"本体表の（実行中）番目に「走れ」というメッセージと戻り値表の（実行中）番目を送る。",
	"",
	"※【system/intr.S】戻る：割り込みやシステムコールから、同じプロセスへ戻る（iret）",
	"カーネルが「戻る」というメッセージを受け取ったとき、",
	"本体表の（実行中）番目に「走れ」というメッセージと戻り値表の（実行中）番目を送る。",
	"",
	"※【system/clkhandler.c】clkhandler：時計の割り込み（1刻み＝100ミリ秒）",
	"カーネルが「clkhandler」というメッセージを受け取ったとき、",
	"時刻に100を加え、刻み残りを（刻み残りから1を引いた数）に変更し、起こすをいいえに変更する。",
	"状態表の（実行中）番目が「CURR」でなければ、要再スケジュールをはいに変更する。",
	"刻み残りが1より小さければ、要再スケジュールをはいに変更する。",
	"※ 眠りリストは差分の列なので、先頭の鍵だけ減らせばよい",
	"眠りリストが空でなければ、次のことを行う。",
	"眠り鍵の1番目を（眠り鍵の1番目から100を引いた数）に設定する。",
	"眠り鍵の1番目が1より小さければ、起こすをはいに変更する。",
	"以上。",
	"起こすがはいならば、自分に「wakeup」というメッセージを送る。",
	"そうでなければ、次のことを行う。",
	"要再スケジュールがはいならば、自分に「resched」というメッセージを送る。",
	"そうでなければ、自分に「戻る」というメッセージを送る。",
	"以上。",
	"",
	"※【system/wakeup.c】wakeup：時間の来たプロセスをすべて起こし、選び直す",
	"カーネルが「wakeup」というメッセージを受け取ったとき、",
	"1から8までの各番号について、次のことを行う。",
	"眠りリストが空でなければ、次のことを行う。",
	"眠り鍵の1番目が1より小さければ、次のことを行う。",
	"眠りリストの先頭から起こすpidを取り出し、眠り鍵の先頭から鍵を取り出す。",
	"※ 刻みが粗いので、先頭の鍵が負になった分は次の人へ繰り越す",
	"眠りリストが空でなければ、眠り鍵の1番目を（眠り鍵の1番目に鍵を加えた数）に設定する。",
	"自分に「ready」というメッセージと起こすpidを送る。",
	"以上。",
	"以上。",
	"以上。",
	"自分に「resched」というメッセージを送る。",
	"",
	"※【system/sleep.c】sleepms：指定したミリ秒だけ眠る",
	"カーネルが「sleepms」というメッセージと長さを受け取ったとき、",
	"戻り値表の（実行中）番目を「OK」に設定する。",
	"長さが1より小さければ、自分に「clkhandler」というメッセージを送る。",
	"そうでなければ、次のことを行う。",
	"※ insertd（insertd.c）: 鍵は前の人との差。自分の鍵より大きい人の前に入り、その人の鍵から自分の分を引く",
	"残りを長さに変更し、入れたをいいえに変更し、空の配列を用意し、新リストと名付け、空の配列を用意し、新鍵と名付ける。",
	"1から眠りリストの要素数までの各番号について、次のことを行う。",
	"入れたがいいえならば、次のことを行う。",
	"残りが眠り鍵の（現在の番号）番目より小さければ、次のことを行う。",
	"実行中を新リストの末尾に追加し、残りを新鍵の末尾に追加し、入れたをはいに変更する。",
	"眠りリストの（現在の番号）番目を新リストの末尾に追加し、（眠り鍵の（現在の番号）番目から残りを引いた数）を新鍵の末尾に追加する。",
	"以上。",
	"そうでなければ、次のことを行う。",
	"残りを（残りから眠り鍵の（現在の番号）番目を引いた数）に変更する。",
	"眠りリストの（現在の番号）番目を新リストの末尾に追加し、眠り鍵の（現在の番号）番目を新鍵の末尾に追加する。",
	"以上。",
	"以上。",
	"そうでなければ、次のことを行う。",
	"眠りリストの（現在の番号）番目を新リストの末尾に追加し、眠り鍵の（現在の番号）番目を新鍵の末尾に追加する。",
	"以上。",
	"以上。",
	"入れたがいいえならば、実行中を新リストの末尾に追加し、残りを新鍵の末尾に追加する。",
	"眠りリストを新リストに変更し、眠り鍵を新鍵に変更し、状態表の（実行中）番目を「SLEEP」に設定する。",
	"自分に「clkhandler」というメッセージを送る。",
	"以上。",
	"",
	"※【system/semcreate.c】semcreate：セマフォを作る（newsem もここ）",
	"カーネルが「semcreate」というメッセージと個数を受け取ったとき、",
	"新番号をなしに変更する。",
	"1から8までの各番号について、次のことを行う。",
	"新番号がなしならば、次のことを行う。",
	"セマフォ状態表の（現在の番号）番目が「FREE」ならば、新番号を現在の番号に変更する。",
	"以上。",
	"以上。",
	"新番号がなしならば、戻り値表の（実行中）番目を「SYSERR」に設定する。",
	"そうでなければ、次のことを行う。",
	"セマフォ状態表の（新番号）番目を「USED」に設定し、セマフォ数表の（新番号）番目を個数に設定する。",
	"戻り値表の（実行中）番目を新番号に設定する。",
	"以上。",
	"自分に「clkhandler」というメッセージを送る。",
	"",
	"※【system/wait.c】wait：セマフォを1つ減らし、足りなければ待つ",
	"カーネルが「wait」というメッセージとセマフォを受け取ったとき、",
	"戻り値表の（実行中）番目を「OK」に設定する。",
	"セマフォ数表の（セマフォ）番目を（セマフォ数表の（セマフォ）番目から1を引いた数）に設定する。",
	"セマフォ数表の（セマフォ）番目が0より小さければ、次のことを行う。",
	"状態表の（実行中）番目を「WAIT」に設定し、実行中をセマフォ待ち表の（セマフォ）番目の末尾に追加する。",
	"以上。",
	"自分に「clkhandler」というメッセージを送る。",
	"",
	"※【system/signal.c】signal：セマフォを1つ増やし、待っている人がいれば1人起こす",
	"カーネルが「signal」というメッセージとセマフォを受け取ったとき、",
	"戻り値表の（実行中）番目を「OK」に設定する。",
	"セマフォ数表の（セマフォ）番目が0より小さければ、次のことを行う。",
	"セマフォ待ち表の（セマフォ）番目の先頭から起こすpidを取り出し、自分に「ready」というメッセージと起こすpidを送る。",
	"以上。",
	"セマフォ数表の（セマフォ）番目を（セマフォ数表の（セマフォ）番目に1を加えた数）に設定する。",
	"自分に「clkhandler」というメッセージを送る。",
	"",
	"※【system/send.c】send：プロセスに伝言を1つ渡す（受け取り待ちなら起こす）",
	"カーネルが「send」というメッセージと依頼を受け取ったとき、",
	"※ 依頼＝[宛先の pid, 伝言]",
	"相手を依頼の1番目に変更し、戻り値表の（実行中）番目を「OK」に設定する。",
	"伝言あり表の（相手）番目がはいならば、戻り値表の（実行中）番目を「SYSERR」に設定する。",
	"そうでなければ、次のことを行う。",
	"伝言表の（相手）番目を依頼の2番目に設定し、伝言あり表の（相手）番目をはいに設定する。",
	"状態表の（相手）番目が「RECV」ならば、次のことを行う。",
	"※ 起きた receive の戻り値として伝言を渡す（Xinu では起きた receive が prmsg を読む）",
	"戻り値表の（相手）番目を依頼の2番目に設定し、伝言あり表の（相手）番目をいいえに設定し、自分に「ready」というメッセージと相手を送る。",
	"以上。",
	"以上。",
	"自分に「clkhandler」というメッセージを送る。",
	"",
	"※【system/receive.c】receive：伝言を受け取る。まだ無ければ届くまで待つ",
	"カーネルが「receive」というメッセージを受け取ったとき、",
	"伝言あり表の（実行中）番目がはいならば、次のことを行う。",
	"戻り値表の（実行中）番目を伝言表の（実行中）番目に設定し、伝言あり表の（実行中）番目をいいえに設定する。",
	"以上。",
	"そうでなければ、状態表の（実行中）番目を「RECV」に設定する。",
	"自分に「clkhandler」というメッセージを送る。",
	"",
	"※【system/getpid.c】getpid：自分の pid",
	"カーネルが「getpid」というメッセージを受け取ったとき、",
	"戻り値表の（実行中）番目を実行中に設定し、自分に「clkhandler」というメッセージを送る。",
	"",
	"※【system/kill.c】kill：プロセスを消す。残りがヌルプロセスだけになったら xdone",
	"カーネルが「kill」というメッセージとpidを受け取ったとき、",
	"止めをいいえに変更する。",
	"pidが1ならば、止めをはいに変更する。",
	"状態表の（pid）番目が「FREE」ならば、止めをはいに変更する。",
	"止めがはいならば、戻り値表の（実行中）番目を「SYSERR」に設定し、自分に「clkhandler」というメッセージを送る。",
	"そうでなければ、次のことを行う。",
	"プロセス数を（プロセス数から1を引いた数）に変更する。",
	"※ 準備リストにいれば外す（getitem）",
	"空の配列を用意し、新リストと名付ける。",
	"1から準備リストの要素数までの各番号について、次のことを行う。",
	"準備リストの（現在の番号）番目がpidでなければ、準備リストの（現在の番号）番目を新リストの末尾に追加する。",
	"以上。",
	"準備リストを新リストに変更し、状態表の（pid）番目を「FREE」に設定し、伝言あり表の（pid）番目をいいえに設定する。",
	"プロセス数が2より小さければ、自分に「xdone」というメッセージを送る。",
	"そうでなければ、自分に「clkhandler」というメッセージを送る。",
	"以上。",
	"",
	"※【system/exit.c】exit：自分を消す（プロセスの関数が戻ったときも userret からここへ来る）",
	"カーネルが「exit」というメッセージを受け取ったとき、",
	"自分に「kill」というメッセージと実行中を送る。",
	"",
	"※【system/xdone.c】xdone：最後のユーザプロセスが終わった。止まる（halt）",
	"カーネルが「xdone」というメッセージを受け取ったとき、",
	"「All user processes have completed.」という文字列を表示する。",
	"これでカーネルの定義を終わる。",
	"",
	"※【system/initialize.c】ヌルプロセス：main を作って走らせ、あとは何もしない",
	"ヌル係というアクターを定義する。",
	"ヌル係は核とpidとメインと段階を持つ。",
	"段階の初期値は0とする。",
	"ヌル係が「生まれた」というメッセージと組を受け取ったとき、",
	"核を組の1番目に変更し、pidを組の2番目に変更し、メインを組の3番目に変更する。",
	"ヌル係が「走れ」というメッセージと戻り値を受け取ったとき、",
	"段階が0ならば、次のことを行う。",
	"※ resume(create(main, INITSTK, INITPRIO, \"Main process\", 0))",
	"段階を1に変更し、空の配列を用意し、組と名付け、メインと65536と20と「Main process」と空を組の末尾に追加し、核に「create」というメッセージと組を送る。",
	"以上。",
	"そうでなければ、次のことを行う。",
	"段階が1ならば、段階を2に変更し、核に「resume」というメッセージと戻り値を送る。",
	"※ while (TRUE) ; 何もしない。次に来るのは時計の割り込み",
	"そうでなければ、核に「clkhandler」というメッセージを送る。",
	"以上。",
	"これでヌル係の定義を終わる。",
	"■ 見本1: PC Xinu の system/main.c（greeter を2つ同時に走らせる）",
	"※ 先に読む: kxinu/核.txt",
	"※ 本物の Xinu と同じ並び: main（優先度20）が greeter（優先度50）を作って resume すると、すぐ greeter に切り替わる。",
	"",
	"※【system/main.c】main：挨拶係を2つ作って走らせ、2.5 秒眠ってから終わりを告げる",
	"メイン係というアクターを定義する。",
	"メイン係は核とpidと段階と甲と乙とg1とg2と組と引数を持つ。",
	"段階の初期値は0とする。",
	"メイン係が「生まれた」というメッセージと組を受け取ったとき、",
	"核を組の1番目に変更し、pidを組の2番目に変更する。",
	"メイン係が「走れ」というメッセージと戻り値を受け取ったとき、",
	"段階に1を加える。",
	"段階が1ならば、次のことを行う。",
	"「=== Sample: two greeter processes running concurrently ===」という文字列を表示する。",
	"※ g1 = create(greeter, 4096, 50, \"greeter-A\", 2, \"Alice\", 3)",
	"挨拶係というアクターを1つ生成し、甲と名付け、空の配列を用意し、引数と名付け、「Alice」と3を引数の末尾に追加する。",
	"空の配列を用意し、組と名付け、甲と4096と50と「greeter-A」と引数を組の末尾に追加し、核に「create」というメッセージと組を送る。",
	"以上。",
	"段階が2ならば、次のことを行う。",
	"※ g2 = create(greeter, 4096, 50, \"greeter-B\", 2, \"Bob\", 3)",
	"g1を戻り値に変更する。",
	"挨拶係というアクターを1つ生成し、乙と名付け、空の配列を用意し、引数と名付け、「Bob」と3を引数の末尾に追加する。",
	"空の配列を用意し、組と名付け、乙と4096と50と「greeter-B」と引数を組の末尾に追加し、核に「create」というメッセージと組を送る。",
	"以上。",
	"段階が3ならば、g2を戻り値に変更し、核に「resume」というメッセージとg1を送る。",
	"段階が4ならば、核に「resume」というメッセージとg2を送る。",
	"段階が5ならば、核に「sleepms」というメッセージと2500を送る。",
	"※ 本物はこのあとシェルを起動する。ここでは main を終える",
	"段階が6ならば、「=== Sample finished, starting shell ===」という文字列を表示し、核に「exit」というメッセージを送る。",
	"これでメイン係の定義を終わる。",
	"",
	"※【system/main.c】greeter：名前を添えて count 回挨拶する。1回ごとに 300 ミリ秒眠る",
	"挨拶係というアクターを定義する。",
	"挨拶係は核とpidと呼び名と回数と回目と引数を持つ。",
	"回目の初期値は0とする。",
	"挨拶係が「生まれた」というメッセージと組を受け取ったとき、",
	"核を組の1番目に変更し、pidを組の2番目に変更し、引数を組の3番目に変更する。",
	"呼び名を引数の1番目に変更し、回数を引数の2番目に変更する。",
	"挨拶係が「走れ」というメッセージと戻り値を受け取ったとき、",
	"回目に1を加える。",
	"※ for (i = 1; i <= count; i++) { kprintf(...); sleepms(300); }  終われば return（exit へ）",
	"回目が（回数に1を加えた数）より小さければ、「[」と呼び名と「] hello from Xinu! (」と回目と「/」と回数と「)」を表示し、核に「sleepms」というメッセージと300を送る。",
	"そうでなければ、核に「exit」というメッセージを送る。",
	"これで挨拶係の定義を終わる。",
	"",
	"※【system/start.S】起動：核とヌルプロセスを用意して nulluser へ",
	"実行を始める。",
	"カーネルというアクターを1つ生成し、核と名付ける。",
	"ヌル係というアクターを1つ生成し、ヌルと名付ける。",
	"メイン係というアクターを1つ生成し、メインと名付ける。",
	"空の配列を用意し、起動と名付け、ヌルとメインを起動の末尾に追加し、核に「nulluser」というメッセージと起動を送る。",
	"これで実行を終わる。",
};
static struct kclass *KC[4] = { &kcls0, &kcls1, &kcls2, &kcls3 };
static const int32 KCL[4] = { 1, 317, 344, 390 };
static const int32 KCE[4] = { 315, 342, 388, 411 };
struct kprogram kp7_prog = { "Xinu（ことのは版）挨拶", 4, KC, KCL, KCE, kbody, 413, 420,
	421, KL, KST, KBP, 320, KSRC, 26, KF };
