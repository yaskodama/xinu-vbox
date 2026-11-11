/* kxfiles.c - ファイルシステムとコンパイラのつなぎ
 *   kx_save_kernel   ことのは版 Xinu の核と見本（kxsrc.c に埋め込んだもの）と、組み込みの例題をディスクへ書く
 *   kx_compile_file  ファイルを読んでコンパイルする。先頭近くの「※ 先に読む: a.txt b.txt」のファイルを前につなぐ
 */
#include <xinu.h>
#include "kxc.h"
#include "kfs.h"
#include "kxsrc.h"

extern int strcmp(const char *, const char *);
extern int strncmp(const char *, const char *, int);

static int32 slen(const char *s) { int32 n = 0; while (s[n]) n++; return n; }
static int32 cat(char *b, int32 p, int32 n, const char *s) { while (*s && p < n - 1) b[p++] = *s++; b[p] = 0; return p; }

/* 行の並びを改行でつないで書く */
static int32 putlines(const char *name, int32 nl, const char *const *lines)
{
	int32 i, n = 0, r;
	char *buf;
	for (i = 0; i < nl; i++) n += slen(lines[i]) + 1;
	buf = getmem(n + 1);
	if (buf == (char *)SYSERR) return SYSERR;
	for (n = 0, i = 0; i < nl; i++) {
		const char *s = lines[i];
		while (*s) buf[n++] = *s++;
		buf[n++] = '\n';
	}
	r = kfs_write(name, buf, n);
	freemem(buf, n + 1);
	return r;
}

/* 書いたファイルの数か SYSERR */
int32 kx_save_kernel(char *log, int32 logn)
{
	int32 g, i, n = 0, p = 0;
	static const char *fname[3] = { "kxinu/核.txt", "kxinu/見本_挨拶.txt", "kxinu/見本_生産と消費.txt" };
	if (log) log[0] = 0;
	if (!kfs_ready() && kfs_init() != OK) {
		if (kfs_format() != OK) return SYSERR;
	}
	for (g = 0; g < nkxgrps && g < 3; g++) {
		if (putlines(fname[g], kxgrps[g].nlines, kxgrps[g].lines) != OK) return SYSERR;
		if (log) { p = cat(log, p, logn, fname[g]); p = cat(log, p, logn, " "); }
		n++;
	}
	/* 組み込みの例題（Mac で変換したもの）の元の文章形式も「例題/名前.txt」に */
	for (i = 0; i < nkprogs; i++) {
		char nm[KFS_NAMEL];
		int32 q;
		struct kprogram *pg = kprogs[i];
		if (strncmp(pg->name, "Xinu（ことのは版）", slen("Xinu（ことのは版）")) == 0) continue;	/* 核＋見本をつないだもの */
		if (strncmp(pg->name, "kxinu/", 6) == 0 || strncmp(pg->name, "例題/", slen("例題/")) == 0) continue;	/* ディスクからコンパイルしたもの */
		q = cat(nm, 0, sizeof(nm) - 4, "例題/");
		q = cat(nm, q, sizeof(nm) - 4, pg->name);
		cat(nm, q, sizeof(nm), ".txt");
		if (putlines(nm, pg->nsrc, pg->src) != OK) return SYSERR;
		n++;
	}
	return n;
}

/* 「※ 先に読む:」の後ろの名前を一つずつ取り出す */
static int32 nextname(const char **pp, char *out, int32 n)
{
	const char *p = *pp;
	int32 k = 0;
	while (*p == ' ' || *p == '\t' || (p[0] == (char)0xE3 && p[1] == (char)0x80 && (p[2] == (char)0x80 || p[2] == (char)0x81))) p += *p == ' ' || *p == '\t' ? 1 : 3;
	while (*p && *p != ' ' && *p != '\t' && *p != '\n' && *p != '\r' &&
	       !(p[0] == (char)0xE3 && p[1] == (char)0x80 && (p[2] == (char)0x80 || p[2] == (char)0x81)) && k < n - 1)
		out[k++] = *p++;
	out[k] = 0;
	*pp = p;
	return k;
}

static char *readall(const char *name, int32 *len)
{
	int32 i, sz = -1, n;
	char *b;
	for (i = 0; i < kfs_count(); i++) if (strcmp(kfs_name(i), name) == 0) sz = kfs_size(i);
	if (sz < 0) return NULL;
	b = getmem(sz + 1);
	if (b == (char *)SYSERR) return NULL;
	n = kfs_read(name, b, sz);
	if (n < 0) { freemem(b, sz + 1); return NULL; }
	b[n] = 0; *len = n;
	return b;
}

/* 誤りの行を、つないだ本文の行からファイルと行に直す */
static char ferr[KX_MAXINC + 1][KFS_NAMEL];
static int32 fstart[KX_MAXINC + 2], nfile;

int32 kx_compile_file(const char *name, char *err, int32 errn)
{
	char *part[KX_MAXINC + 1], *all;
	int32 plen[KX_MAXINC + 1], np = 0, i, total = 0, r, line;
	char *main;
	int32 mlen;
	const char *p;
	if (err) err[0] = 0;
	if (!kfs_ready() && kfs_init() != OK) { if (err) cat(err, 0, errn, kfs_error()); return SYSERR; }
	if (!(main = readall(name, &mlen))) { if (err) { int32 q = cat(err, 0, errn, name); cat(err, q, errn, " が読めない"); } return SYSERR; }
	/* 先頭 20 行の中の「※ 先に読む:」 */
	nfile = 0;
	for (p = main, line = 0; *p && line < 20; line++) {
		const char *e = p;
		while (*e && *e != '\n') e++;
		if (strncmp(p, "※ 先に読む:", slen("※ 先に読む:")) == 0 || strncmp(p, "※先に読む:", slen("※先に読む:")) == 0) {
			const char *q = p + (p[3] == ' ' ? slen("※ 先に読む:") : slen("※先に読む:"));
			char nm[KFS_NAMEL];
			while (q < e && np < KX_MAXINC && nextname(&q, nm, sizeof(nm)) > 0) {
				if (!(part[np] = readall(nm, &plen[np]))) {
					if (err) { int32 k = cat(err, 0, errn, name); k = cat(err, k, errn, " が先に読む "); k = cat(err, k, errn, nm); cat(err, k, errn, " が無い"); }
					while (np > 0) { np--; freemem(part[np], plen[np] + 1); }
					freemem(main, mlen + 1);
					return SYSERR;
				}
				cat(ferr[nfile], 0, KFS_NAMEL, nm); nfile++;
				np++;
			}
		}
		p = *e ? e + 1 : e;
	}
	part[np] = main; plen[np] = mlen; cat(ferr[nfile], 0, KFS_NAMEL, name); nfile++;
	for (i = 0; i <= np; i++) total += plen[i] + 1;
	all = getmem(total + 1);
	if (all == (char *)SYSERR) { if (err) cat(err, 0, errn, "メモリが足りない"); r = SYSERR; goto out; }
	/* つなぐ。各ファイルが何行目から始まるかを覚える */
	{
		int32 n = 0, ln = 1, k;
		for (i = 0; i <= np; i++) {
			fstart[i] = ln;
			for (k = 0; k < plen[i]; k++) { all[n++] = part[i][k]; if (part[i][k] == '\n') ln++; }
			if (plen[i] == 0 || part[i][plen[i] - 1] != '\n') { all[n++] = '\n'; ln++; }
		}
		fstart[np + 1] = ln;
		all[n] = 0;
		r = kx_compile(name, all, n);
	}
	if (r == SYSERR && err) {
		int32 q = 0, f = np;
		if (kx_errline > 0) {
			for (f = 0; f < np && kx_errline >= fstart[f + 1]; f++) ;
			q = cat(err, 0, errn, ferr[f]);
			q = cat(err, q, errn, " ");
			{
				char t[12]; int32 v = kx_errline - fstart[f] + 1, j = 11;
				t[j] = 0; do { t[--j] = '0' + v % 10; v /= 10; } while (v);
				q = cat(err, q, errn, t + j);
			}
			q = cat(err, q, errn, "行: ");
			cat(err, q, errn, kx_errtext);
		} else cat(err, 0, errn, kx_errtext);
	}
	freemem(all, total + 1);
out:
	for (i = 0; i <= np; i++) freemem(part[i], plen[i] + 1);
	return r;
}
