/* kxlex.c - ことのはの字句解析（Xinu の中で動く）。../../lex.py と同じ切り方
 *   - 「※」から行末までは注釈、「■」で始まる行は見出しとして読み飛ばす。改行と空白は「…」の中を除いて捨てる
 *   - 予約語と、宣言された名前（アクター名・状態・受信の引数・「〜と名付け」・「〜を取り出す」）を最長一致で切る
 *   - 数字列、「…」の文字列
 */
#include <xinu.h>
#include "kxc.h"
#include "kxc.tab.h"

extern int strncmp(const char *, const char *, int);

struct kw { const char *s; int32 code; };
static const struct kw KW[] = {
	{ "というアクターを定義する。", K_DEFACTOR }, { "を持つ。", K_HAS },
	{ "の初期値は", K_INIT }, { "とし、", K_TOSHI }, { "とする。", K_TOSURU },
	{ "というメッセージ", T_MSG }, { "を受け取ったとき、", K_RECV },
	{ "これで", KORE }, { "の定義を終わる。", K_ENDDEF },
	{ "実行を始める。", K_RUN }, { "実行を終わる。", K_ENDRUN },
	{ "。", MARU }, { "、", TEN }, { "その後、", SONOATO },
	{ "ならば、", NARABA }, { "でなければ、", DENAKEREBA }, { "より小さければ、", YORICHIISA },
	{ "そうでなければ、", SOUDENAKEREBA }, { "次のことを行う。", K_BLOCK }, { "以上。", IJOU },
	{ "から", KARA }, { "までの各番号について、", MADE_NITSUITE },
	{ "は", WA }, { "と", TO }, { "が", GA }, { "に", NI }, { "を", WO }, { "の", NO },
	{ "の末尾", NO_MATSUBI }, { "の先頭から", NO_SENTOU_KARA }, { "の全員", NO_ZENIN },
	{ "番目", BANME }, { "それぞれ", SOREZORE }, { "という文字列", T_MOJIRETSU },
	{ "というアクター", T_ACTOR }, { "1つ", ICHITSU },
	{ "表示する", HYOUJI_S }, { "表示し", HYOUJI_R }, { "送る", OKURU_S }, { "送り", OKURU_R },
	{ "変更する", HENKOU_S }, { "変更し", HENKOU_R }, { "設定する", HENKOU_S }, { "設定し", HENKOU_R },
	{ "加える", KUWAE_S }, { "加え", KUWAE_R }, { "加えた数", KUWAETA },
	{ "引いた数", HIITA }, { "で割った余り", WARIAMARI }, { "の要素数", NO_YOUSOSU },
	{ "追加する", TSUIKA_S }, { "追加し", TSUIKA_R }, { "取り出す", TORIDASU_S }, { "取り出し", TORIDASU_R },
	{ "名付ける", NAZUKE_S }, { "名付け", NAZUKE_R }, { "生成し", SEISEI_R }, { "用意し", YOUI_R },
	{ "はい", HAI }, { "いいえ", IIE }, { "なし", NASHI }, { "空", SORA }, { "空の配列", SORA_HAIRETSU },
	{ "自分", JIBUN }, { "自分自身", JIBUN_JISHIN }, { "現在の番号", GENZAI }, { "その", SONO },
	{ "（", LP }, { "）", RP },
};
#define NKW	((int32)(sizeof(KW) / sizeof(KW[0])))

static int32 slen(const char *s) { int32 n = 0; while (s[n]) n++; return n; }
static int32 ulen(unsigned char c) { return c < 0x80 ? 1 : c < 0xE0 ? 2 : c < 0xF0 ? 3 : 4; }
static int32 nchars(const char *s, int32 n) { int32 i = 0, k = 0; while (i < n) { i += ulen((unsigned char)s[i]); k++; } return k; }
static char *sdup(const char *s, int32 n) { char *r = kx_alloc(n + 1); int32 i; for (i = 0; i < n; i++) r[i] = s[i]; r[n] = 0; return r; }

/* 注釈と見出しを除いた本文 t と、各バイトの元の行番号 */
static char *t;
static int32 *tl, tn;

/* t の中で pat を from から探す（無ければ -1） */
static int32 tfind(int32 from, int32 to, const char *pat)
{
	int32 m = slen(pat), i;
	for (i = from; i + m <= to; i++) if (t[i] == pat[0] && strncmp(t + i, pat, m) == 0) return i;
	return -1;
}
static int32 isdelim(int32 i, int32 maru_only)	/* t[i] から「。」（maru_only でなければ「、」も）が始まるか */
{
	if (i + 3 > tn || (unsigned char)t[i] != 0xE3 || (unsigned char)t[i + 1] != 0x80) return 0;
	return (unsigned char)t[i + 2] == 0x82 || (!maru_only && (unsigned char)t[i + 2] == 0x81);
}
static int32 hasdelim(int32 a, int32 b, int32 maru_only)
{
	int32 i;
	for (i = a; i < b; i++) if (isdelim(i, maru_only)) return 1;
	return 0;
}

/* 宣言された名前 */
#define MAXNAMES 400
static const char *kxnames[MAXNAMES];
static int32 nkxnames;
static void addname(int32 a, int32 b)
{
	int32 i, n = b - a;
	if (n <= 0) return;
	for (i = 0; i < nkxnames; i++) if (slen(kxnames[i]) == n && strncmp(kxnames[i], t + a, n) == 0) return;
	if (nkxnames < MAXNAMES) kxnames[nkxnames++] = sdup(t + a, n);
}
static void collect(void)
{
	int32 pos, L, a, i, p, q, e, run;
	const char *P;
	nkxnames = 0;
	/* ([^。、]+?)というアクターを定義する */
	P = "というアクターを定義する";
	for (pos = 0; (L = tfind(pos, tn, P)) >= 0; pos = L + slen(P)) {
		a = pos;
		for (i = pos; i < L; i++) if (isdelim(i, 0)) a = i + 3;
		addname(a, L);
	}
	/* [^。、]+?は([^。]+?)を持つ。  … 「は」と「を持つ。」の間を「と」で切る */
	P = "を持つ。";
	for (pos = 0; (L = tfind(pos, tn, P)) >= 0; pos = L + slen(P)) {
		a = pos;
		for (i = pos; i < L; i++) if (isdelim(i, 1)) a = i + 3;
		for (p = a; p < L; p = run + 3) {
			for (run = p; run < L && !isdelim(run, 0); run++) ;
			if (p < run && (q = tfind(p + ulen((unsigned char)t[p]), run, "は")) >= 0 && q + 3 < L) {
				int32 s = q + 3;
				while (s < L) {
					e = tfind(s, L, "と");
					if (e < 0) e = L;
					addname(s, e);
					s = e + 3;
				}
				break;
			}
			if (run >= L) break;
		}
	}
	/* というメッセージと([^。、]+?)を受け取ったとき  と  の先頭から([^、。]+?)を取り出 */
	{
		static const char *pre[2] = { "というメッセージと", "の先頭から" }, *post[2] = { "を受け取ったとき", "を取り出" };
		int32 k;
		for (k = 0; k < 2; k++)
			for (pos = 0; (L = tfind(pos, tn, pre[k])) >= 0; ) {
				int32 g = L + slen(pre[k]);
				pos = g;
				if (g >= tn) break;
				e = tfind(g + ulen((unsigned char)t[g]), tn, post[k]);
				if (e >= 0 && !hasdelim(g, e, 0)) { addname(g, e); pos = e + slen(post[k]); }
			}
	}
	/* 、([^、。]+?)と名付け */
	for (pos = 0; pos < tn; ) {
		int32 c = -1;
		for (i = pos; i < tn; i++) if (isdelim(i, 0) && (unsigned char)t[i + 2] == 0x81) { c = i; break; }
		if (c < 0) break;
		e = c + 3 < tn ? tfind(c + 3 + ulen((unsigned char)t[c + 3]), tn, "と名付け") : -1;
		if (e >= 0 && !hasdelim(c + 3, e, 0)) { addname(c + 3, e); pos = e + slen("と名付け"); }
		else pos = c + 3;
	}
}

/* 字句の列。本文の写しと字句の表は解析が済んだら返す（kx_lex_end） */
struct ktok { int32 code, line; const char *s; };
static struct ktok *toks;
static int32 ntok, itok;

static char *tmpbuf[3]; static uint32 tmpsz[3]; static int32 ntmp;
static char *tmp(uint32 n)
{
	char *p = getmem(n);
	if (p == (char *)SYSERR) return NULL;
	tmpbuf[ntmp] = p; tmpsz[ntmp++] = n;
	return p;
}
void kx_lex_end(void)
{
	while (ntmp > 0) { ntmp--; freemem(tmpbuf[ntmp], tmpsz[ntmp]); }
	t = NULL; tl = NULL; toks = NULL; ntok = itok = 0;
}

int32 kx_lex_start(const char *src, int32 len)
{
	int32 i, ln = 1, instr = 0, bol = 1, skip = 0, cmt = 0, cap;
	/* 1) 注釈・見出し・空白を除く */
	t = tmp(len + 1); tl = (int32 *)tmp(sizeof(int32) * (len + 1)); tn = 0;
	toks = NULL;
	if (!t || !tl) { kx_semerr(0, "メモリが足りない", "", ""); return SYSERR; }
	for (i = 0; i < len; ) {
		unsigned char c = (unsigned char)src[i];
		int32 n = ulen(c), k;
		if (c == '\n') { ln++; bol = 1; skip = 0; cmt = 0; i++; continue; }
		if (bol) {	/* 行頭の空白のあとが「■」なら、その行は見出し */
			int32 j = i;
			while (j < len && (src[j] == ' ' || src[j] == '\t' || src[j] == '\r' ||
			       ((unsigned char)src[j] == 0xE3 && (unsigned char)src[j + 1] == 0x80 && (unsigned char)src[j + 2] == 0x80)))
				j += (src[j] == ' ' || src[j] == '\t' || src[j] == '\r') ? 1 : 3;
			if (j + 3 <= len && (unsigned char)src[j] == 0xE2 && (unsigned char)src[j + 1] == 0x96 && (unsigned char)src[j + 2] == 0xA0) skip = 1;
			bol = 0;
		}
		if (skip || cmt) { i += n; continue; }
		if (n == 3 && c == 0xE2 && (unsigned char)src[i + 1] == 0x80 && (unsigned char)src[i + 2] == 0xBB) { cmt = 1; i += 3; continue; }	/* ※ */
		if (n == 3 && c == 0xE3 && (unsigned char)src[i + 1] == 0x80 && (unsigned char)src[i + 2] == 0x8C) instr = 1;	/* 「 */
		else if (n == 3 && c == 0xE3 && (unsigned char)src[i + 1] == 0x80 && (unsigned char)src[i + 2] == 0x8D) instr = 0;	/* 」 */
		if (!instr && (c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\v' ||
		    (n == 3 && c == 0xE3 && (unsigned char)src[i + 1] == 0x80 && (unsigned char)src[i + 2] == 0x80))) { i += n; continue; }
		for (k = 0; k < n && i < len; k++) { t[tn] = src[i++]; tl[tn++] = ln; }
	}
	t[tn] = 0;
	/* 2) 宣言された名前 */
	collect();
	/* 3) 最長一致で切る */
	cap = tn / 2 + 16;
	toks = (struct ktok *)tmp(sizeof(struct ktok) * cap); ntok = 0; itok = 0;
	if (!toks) { kx_semerr(0, "メモリが足りない", "", ""); return SYSERR; }
	for (i = 0; i < tn; ) {
		int32 best = -1, bestlen = 0, bestch = 0, k, m, d;
		if (ntok >= cap - 1) { kx_semerr(tl[i], "字句が多すぎる", "", ""); return SYSERR; }
		if ((unsigned char)t[i] == 0xE3 && (unsigned char)t[i + 1] == 0x80 && (unsigned char)t[i + 2] == 0x8C) {	/* 「…」 */
			int32 j = tfind(i, tn, "」");
			if (j < 0) { kx_semerr(tl[i], "「 が閉じていない", "", ""); return SYSERR; }
			toks[ntok].code = STRING; toks[ntok].line = tl[i]; toks[ntok].s = sdup(t + i, j + 3 - i); ntok++;
			i = j + 3; continue;
		}
		for (k = 0; k < NKW + nkxnames; k++) {
			const char *s = k < NKW ? KW[k].s : kxnames[k - NKW];
			m = slen(s);
			if (i + m <= tn && strncmp(t + i, s, m) == 0) {
				int32 ch = nchars(s, m);
				if (ch > bestch) { best = k; bestlen = m; bestch = ch; }
			}
		}
		for (d = 0; i + d < tn && t[i + d] >= '0' && t[i + d] <= '9'; d++) ;
		if (d > 0 && (best < 0 || d > bestch)) {
			toks[ntok].code = NUMBER; toks[ntok].line = tl[i]; toks[ntok].s = sdup(t + i, d); ntok++;
			i += d; continue;
		}
		if (best < 0) {
			char b[40];
			int32 n = 0, c = 0;
			while (i + n < tn && c < 12) { n += ulen((unsigned char)t[i + n]); c++; }
			if (i + n > tn) n = tn - i;
			{ int32 q; for (q = 0; q < n && q < 36; q++) b[q] = t[i + q]; b[q] = 0; }
			kx_semerr(tl[i], "字句エラー: 「", b, "…」は予約語でも宣言された名前でもない");
			return SYSERR;
		}
		toks[ntok].code = best < NKW ? KW[best].code : NAME;
		toks[ntok].line = tl[i];
		toks[ntok].s = best < NKW ? KW[best].s : kxnames[best - NKW];
		ntok++;
		i += bestlen;
	}
	return OK;
}

const char *kx_curtext = "";
int32 kxlex(void)
{
	if (itok >= ntok) { kx_curtext = "（終わり）"; return 0; }
	kxlval.s = toks[itok].s;
	kxlloc.first_line = kxlloc.last_line = toks[itok].line;
	kxlloc.first_column = kxlloc.last_column = 0;
	kx_curtext = toks[itok].s;
	return toks[itok++].code;
}
