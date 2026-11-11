/* kxsrc.h - 埋め込んだ Xinu のソースの表（gen_xsrc.py が kxsrc.c を作る） */
#ifndef KXSRC_H
#define KXSRC_H
struct xfn { const char *name; int32 line, end; };	/* 関数（行番号は 1 から） */
struct xfile {
	int32	dir;			/* xdirs の番号	*/
	const char *name;
	int32	nlines;
	const char *const *lines;
	int32	nfn;
	const struct xfn *fns;
};
extern const struct xfile xfiles[];
extern const int32 nxfiles;
extern const char *const xdirs[];
extern const int32 nxdirs;
/* ことのはで書き直した Xinu（kxinu/）。ファイルは元の C の場所（system/create.c など）で呼ぶ */
struct kxgrp { const char *name; const char *prog; int32 nlines; const char *const *lines; };
struct kxfile {
	int32	grp;
	const char *path;		/* 対応する C のファイル		*/
	int32	nsec;
	int32	sec[4][2];		/* そのファイルに当たる行の範囲	*/
	int32	nfn;
	const struct xfn *fns;		/* 受信節（行は grp の本文の行）	*/
};
extern const struct kxgrp kxgrps[];
extern const int32 nkxgrps;
extern const struct kxfile kxfiles[];
extern const int32 nkxfiles;
#endif
