/* kfs.c - Xinu の小さなファイルシステム（KFS）と ATA（IDE）ディスクの読み書き。kfs.h を参照 */
#include <xinu.h>
#include "kfs.h"

extern int strcmp(const char *, const char *);

/* ───── ATA（1次の主ディスク、PIO、割り込みなし） ───── */
#define ATA_DATA	0x1F0
#define ATA_ERR		0x1F1
#define ATA_COUNT	0x1F2
#define ATA_LBA0	0x1F3
#define ATA_LBA1	0x1F4
#define ATA_LBA2	0x1F5
#define ATA_DRIVE	0x1F6
#define ATA_CMD		0x1F7	/* 書くと命令、読むと状態 */
#define ATA_CTL		0x3F6
#define ST_BSY	0x80
#define ST_DRQ	0x08
#define ST_ERR	0x01

static int32	ata_sectors;		/* ディスクの区画数（0 ならディスクが無い） */
static const char *kerr = "";

static int32 ata_wait(int32 drq)
{
	int32 i, s;
	for (i = 0; i < 2000000; i++) {
		s = inb(ATA_CMD) & 0xFF;
		if (s == 0xFF) return SYSERR;		/* 何もつながっていない */
		if (s & ST_BSY) continue;
		if (s & ST_ERR) return SYSERR;
		if (!drq || (s & ST_DRQ)) return OK;
	}
	return SYSERR;
}
static void ata_lba(uint32 lba)
{
	outb(ATA_DRIVE, 0xE0 | ((lba >> 24) & 0x0F));
	outb(ATA_COUNT, 1);
	outb(ATA_LBA0, lba & 0xFF);
	outb(ATA_LBA1, (lba >> 8) & 0xFF);
	outb(ATA_LBA2, (lba >> 16) & 0xFF);
}
static int32 ata_read(uint32 lba, void *buf)
{
	uint16 *w = (uint16 *)buf;
	int32 i;
	if (ata_wait(0) != OK) return SYSERR;
	ata_lba(lba);
	outb(ATA_CMD, 0x20);
	if (ata_wait(1) != OK) return SYSERR;
	for (i = 0; i < 256; i++) w[i] = inw(ATA_DATA);
	return OK;
}
static int32 ata_write(uint32 lba, const void *buf)
{
	const uint16 *w = (const uint16 *)buf;
	int32 i;
	if (ata_wait(0) != OK) return SYSERR;
	ata_lba(lba);
	outb(ATA_CMD, 0x30);
	if (ata_wait(1) != OK) return SYSERR;
	for (i = 0; i < 256; i++) outw(ATA_DATA, w[i]);
	outb(ATA_CMD, 0xE7);			/* 書き込みの溜めを吐き出す */
	return ata_wait(0);
}
static int32 ata_identify(void)
{
	uint16 id[256];
	int32 i, s;
	outb(ATA_CTL, 0x02);			/* 割り込みを止める（読み終わりは状態を見て待つ） */
	outb(ATA_DRIVE, 0xA0);
	outb(ATA_COUNT, 0); outb(ATA_LBA0, 0); outb(ATA_LBA1, 0); outb(ATA_LBA2, 0);
	outb(ATA_CMD, 0xEC);
	s = inb(ATA_CMD) & 0xFF;
	if (s == 0 || s == 0xFF) return 0;
	if (ata_wait(1) != OK) return 0;
	for (i = 0; i < 256; i++) id[i] = inw(ATA_DATA);
	return id[60] | ((int32)id[61] << 16);	/* LBA28 で使える区画数 */
}

/* ───── KFS ───── */
#define DIR0	1
#define DIRN	16
#define DATA0	32
struct kfsent {				/* 64 バイト */
	char	name[KFS_NAMEL];
	uint32	start, size, cap, flags;
};
struct kfshead { char magic[4]; uint32 total, next, nfiles; char pad[496]; };

static struct kfshead	hd;
static struct kfsent	dir[KFS_MAXF];
static int32	ok;
static sid32	kfsmutex = SYSERR;
static char	sec[512];

static int32 kslen(const char *s) { int32 n = 0; while (s[n]) n++; return n; }
static void lock(void) { if (kfsmutex == SYSERR) kfsmutex = semcreate(1); wait(kfsmutex); }
static int32 unlock(int32 r) { signal(kfsmutex); return r; }
static int32 fail(const char *e) { kerr = e; return SYSERR; }

static int32 save_head(void) { return ata_write(0, &hd); }
static int32 save_dir(void)
{
	int32 i;
	for (i = 0; i < DIRN; i++) if (ata_write(DIR0 + i, (char *)dir + i * 512) != OK) return SYSERR;
	return OK;
}

int32 kfs_init(void)
{
	int32 i;
	ok = 0;
	ata_sectors = ata_identify();
	if (ata_sectors <= DATA0) return fail("ディスクが無い（QEMU に -drive …,if=ide を付ける）");
	if (ata_read(0, &hd) != OK) return fail("見出しが読めない");
	if (hd.magic[0] != 'K' || hd.magic[1] != 'F' || hd.magic[2] != 'S' || hd.magic[3] != '1')
		return fail("まだ初期化（フォーマット）されていない");
	for (i = 0; i < DIRN; i++) if (ata_read(DIR0 + i, (char *)dir + i * 512) != OK) return fail("目録が読めない");
	ok = 1;
	return OK;
}
int32 kfs_ready(void) { return ok; }
const char *kfs_error(void) { return kerr; }
int32 kfs_total(void) { return ata_sectors; }
int32 kfs_used(void) { return ok ? (int32)hd.next : 0; }

int32 kfs_format(void)
{
	int32 i;
	char *p = (char *)&hd;
	if (ata_sectors <= DATA0 && (ata_sectors = ata_identify()) <= DATA0) return fail("ディスクが無い");
	lock();
	for (i = 0; i < (int32)sizeof(hd); i++) p[i] = 0;
	hd.magic[0] = 'K'; hd.magic[1] = 'F'; hd.magic[2] = 'S'; hd.magic[3] = '1';
	hd.total = ata_sectors; hd.next = DATA0; hd.nfiles = 0;
	p = (char *)dir;
	for (i = 0; i < (int32)sizeof(dir); i++) p[i] = 0;
	if (save_head() != OK || save_dir() != OK) return unlock(fail("書き込めない"));
	ok = 1;
	return unlock(OK);
}

/* 使っている項目を i 番目（0 から）まで数える */
static int32 nth(int32 i)
{
	int32 k;
	for (k = 0; k < KFS_MAXF; k++) if (dir[k].name[0] && i-- == 0) return k;
	return SYSERR;
}
int32 kfs_count(void)
{
	int32 k, n = 0;
	if (!ok) return 0;
	for (k = 0; k < KFS_MAXF; k++) if (dir[k].name[0]) n++;
	return n;
}
const char *kfs_name(int32 i) { int32 k = nth(i); return k == SYSERR ? "" : dir[k].name; }
int32 kfs_size(int32 i) { int32 k = nth(i); return k == SYSERR ? 0 : (int32)dir[k].size; }
static int32 slot(const char *name)
{
	int32 k;
	for (k = 0; k < KFS_MAXF; k++) if (dir[k].name[0] && strcmp(dir[k].name, name) == 0) return k;
	return SYSERR;
}
int32 kfs_find(const char *name)
{
	int32 k, i = 0;
	if (!ok) return SYSERR;
	for (k = 0; k < KFS_MAXF; k++) {
		if (!dir[k].name[0]) continue;
		if (strcmp(dir[k].name, name) == 0) return i;
		i++;
	}
	return SYSERR;
}

int32 kfs_read(const char *name, char *buf, int32 max)
{
	int32 k, n, s, j, len;
	if (!ok) return fail("ファイルシステムが無い");
	lock();
	if ((k = slot(name)) == SYSERR) return unlock(fail("そのファイルは無い"));
	len = dir[k].size < (uint32)max ? (int32)dir[k].size : max;
	for (n = 0, s = 0; n < len; s++) {
		if (ata_read(dir[k].start + s, sec) != OK) return unlock(fail("読めない"));
		for (j = 0; j < 512 && n < len; j++) buf[n++] = sec[j];
	}
	return unlock(len);
}

int32 kfs_write(const char *name, const char *buf, int32 len)
{
	int32 k, s, j, n, need = (len + 511) / 512;
	if (!ok) return fail("ファイルシステムが無い");
	if (kslen(name) == 0 || kslen(name) >= KFS_NAMEL) return fail("名前が長すぎる（47バイトまで）");
	lock();
	if ((k = slot(name)) == SYSERR) {
		for (k = 0; k < KFS_MAXF && dir[k].name[0]; k++) ;
		if (k == KFS_MAXF) return unlock(fail("目録がいっぱい"));
		for (j = 0; name[j]; j++) dir[k].name[j] = name[j];
		for (; j < KFS_NAMEL; j++) dir[k].name[j] = 0;
		dir[k].cap = 0; dir[k].start = 0;
	}
	if ((uint32)need > dir[k].cap) {		/* 入りきらない: 後ろに新しく取る */
		if (hd.next + need > hd.total) { dir[k].name[0] = dir[k].cap ? dir[k].name[0] : 0; return unlock(fail("ディスクがいっぱい（整理してみる）")); }
		dir[k].start = hd.next; dir[k].cap = need; hd.next += need;
	}
	for (n = 0, s = 0; s < need; s++) {
		for (j = 0; j < 512; j++) sec[j] = n < len ? buf[n++] : 0;
		if (ata_write(dir[k].start + s, sec) != OK) return unlock(fail("書き込めない"));
	}
	dir[k].size = len;
	if (save_dir() != OK || save_head() != OK) return unlock(fail("目録が書けない"));
	return unlock(OK);
}

int32 kfs_delete(const char *name)
{
	int32 k;
	if (!ok) return fail("ファイルシステムが無い");
	lock();
	if ((k = slot(name)) == SYSERR) return unlock(fail("そのファイルは無い"));
	dir[k].name[0] = 0;
	if (save_dir() != OK) return unlock(fail("目録が書けない"));
	return unlock(OK);
}

/* 隙間を詰める: 先頭区画の小さい順に、前へ寄せて写す */
int32 kfs_compact(void)
{
	int32 k, best, s;
	uint32 at = DATA0, lo;
	static unsigned char done[KFS_MAXF];
	if (!ok) return fail("ファイルシステムが無い");
	lock();
	for (k = 0; k < KFS_MAXF; k++) done[k] = 0;
	for (;;) {
		best = SYSERR; lo = 0xFFFFFFFF;
		for (k = 0; k < KFS_MAXF; k++)
			if (dir[k].name[0] && !done[k] && dir[k].start < lo) { lo = dir[k].start; best = k; }
		if (best == SYSERR) break;
		done[best] = 1;
		{
			uint32 need = (dir[best].size + 511) / 512;
			if (dir[best].start != at)
				for (s = 0; s < (int32)need; s++) {
					if (ata_read(dir[best].start + s, sec) != OK || ata_write(at + s, sec) != OK) return unlock(fail("写せない"));
				}
			dir[best].start = at; dir[best].cap = need; at += need;
		}
	}
	hd.next = at;
	if (save_dir() != OK || save_head() != OK) return unlock(fail("目録が書けない"));
	return unlock(OK);
}
