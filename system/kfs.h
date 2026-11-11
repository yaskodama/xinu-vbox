/* kfs.h - Xinu の小さなファイルシステム（KFS）。QEMU の IDE ディスク（ATA、PIO）に置く。再起動しても残る
 *
 * 配置（1区画＝512バイト）
 *   0        見出し   "KFS1"、全区画数、次に割り当てる区画
 *   1〜16    目録     1項目64バイト×128項目（名前48・先頭区画・大きさ・確保した区画数・印）
 *   32〜     中身     ファイルごとに連続した区画。書き直して入りきらなければ後ろへ移す（前の場所は「整理」で詰める）
 * 名前は UTF-8 で 47 バイトまで。「kxinu/核.txt」のように / を含めてよい（ディレクトリは名前の一部）。
 */
#ifndef KFS_H
#define KFS_H
#define KFS_MAXF	128
#define KFS_NAMEL	48

int32	kfs_init(void);			/* ディスクを探して見出しを読む。OK／SYSERR（ディスクが無い） */
int32	kfs_ready(void);		/* 使えるか（初期化済みで形式も正しい） */
int32	kfs_format(void);		/* 空のファイルシステムを作る */
int32	kfs_count(void);		/* ファイルの数 */
const char *kfs_name(int32 i);		/* i 番目（0 から）の名前 */
int32	kfs_size(int32 i);
int32	kfs_find(const char *name);	/* 番号か SYSERR */
int32	kfs_read(const char *name, char *buf, int32 max);	/* 読んだバイト数か SYSERR */
int32	kfs_write(const char *name, const char *buf, int32 len);	/* OK／SYSERR */
int32	kfs_delete(const char *name);
int32	kfs_compact(void);		/* 隙間を詰める */
int32	kfs_total(void);		/* 全区画数 */
int32	kfs_used(void);			/* 使っている区画数（見出し・目録を含む） */
const char *kfs_error(void);		/* 最後の誤りの説明 */
#endif
