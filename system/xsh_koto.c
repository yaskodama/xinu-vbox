/* xsh_koto.c - シェルのコマンド koto: ファイルシステム（KFS）と、Xinu の中のことのはコンパイラ
 *   koto ls                 ファイルの一覧
 *   koto cat 名前           中身を表示
 *   koto save               ことのは版 Xinu の核と見本、組み込みの例題をディスクへ保存
 *   koto cc 名前            コンパイルする（「※ 先に読む:」のファイルを前につなぐ）
 *   koto run 名前           コンパイルして走らせ、終わるまで待つ
 *   koto rm 名前 ／ koto format ／ koto df ／ koto compact
 */
#include <xinu.h>
#include "kxc.h"
#include "kfs.h"

extern int strcmp(const char *, const char *);

static int32 need(void)
{
	if (kfs_ready()) return OK;
	if (kfs_init() == OK) return OK;
	printf("koto: %s\n", kfs_error());
	return SYSERR;
}

shellcmd xsh_koto(int nargs, char *args[])
{
	char err[200];
	int32 i, r;
	const char *c = nargs > 1 ? args[1] : "";
	if (nargs < 2 || strcmp(c, "--help") == 0) {
		printf("使い方: koto ls | cat 名前 | save | cc 名前 | run 名前 | rm 名前 | format | df | compact\n");
		return 0;
	}
	if (strcmp(c, "format") == 0) {
		if (kfs_format() != OK) { printf("koto: %s\n", kfs_error()); return 1; }
		printf("初期化しました（%d 区画）\n", kfs_total());
		return 0;
	}
	if (need() != OK) return 1;
	if (strcmp(c, "ls") == 0) {
		for (i = 0; i < kfs_count(); i++) printf("%8d  %s\n", kfs_size(i), kfs_name(i));
		printf("%d 個のファイル\n", kfs_count());
	} else if (strcmp(c, "df") == 0) {
		printf("%d / %d 区画を使用（1区画 512 バイト）\n", kfs_used(), kfs_total());
	} else if (strcmp(c, "compact") == 0) {
		if (kfs_compact() != OK) { printf("koto: %s\n", kfs_error()); return 1; }
		printf("詰めました。%d / %d 区画を使用\n", kfs_used(), kfs_total());
	} else if (strcmp(c, "save") == 0) {
		r = kx_save_kernel(NULL, 0);
		if (r == SYSERR) { printf("koto: %s\n", kfs_error()); return 1; }
		printf("%d 個のファイルを保存しました\n", r);
	} else if (nargs < 3) {
		printf("koto %s: ファイルの名前が要る\n", c);
		return 1;
	} else if (strcmp(c, "cat") == 0) {
		int32 sz = -1;
		char *b;
		for (i = 0; i < kfs_count(); i++) if (strcmp(kfs_name(i), args[2]) == 0) sz = kfs_size(i);
		if (sz < 0) { printf("koto: %s は無い\n", args[2]); return 1; }
		b = getmem(sz + 1);
		r = kfs_read(args[2], b, sz);
		if (r >= 0) { b[r] = 0; for (i = 0; i < r; i++) putc(stdout, b[i]); }
		freemem(b, sz + 1);
	} else if (strcmp(c, "rm") == 0) {
		if (kfs_delete(args[2]) != OK) { printf("koto: %s\n", kfs_error()); return 1; }
	} else if (strcmp(c, "cc") == 0 || strcmp(c, "run") == 0) {
		r = kx_compile_file(args[2], err, sizeof(err));
		if (r == SYSERR) { printf("コンパイルできない: %s\n", err); return 1; }
		printf("コンパイルしました: %s（アクター定義 %d、受信節と実行部 %d、%d 行）\n",
		       kprogs[r]->name, kprogs[r]->ncls, kprogs[r]->nfun, kprogs[r]->nsrc);
		if (strcmp(c, "run") == 0) {
			kd.mode = KM_RUN;
			kd_run(kprogs[r]);
			while (kd.state == KR_RUN || kd.state == KR_PAUSED) sleepms(50);
			printf("── %s（処理したメッセージ %d 通）\n", kd.state == KR_ERROR ? "誤りで止まった" : "終わり", kd.nmsgs);
		}
	} else {
		printf("koto: %s というコマンドは無い\n", c);
		return 1;
	}
	return 0;
}
