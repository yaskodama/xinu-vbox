/* input.c - キーボード（PS/2）とマウス（VMware の絶対座標マウス）を見回りで読む
 *
 * マウスは QEMU の vmmouse（VMware バックドア、ポート 0x5658）を絶対座標で使う。
 * ホストのマウスの位置がそのまま画面上の位置になるので、ウィンドウにマウスを捕まえさせなくてよい。
 * キーボードは i8042 から走査コード（セット1）を読む。割り込みは使わず、GUI のプロセスが定期的に見る。
 */
#include <xinu.h>
#include "gfx.h"
#include "input.h"

#define VMPORT_MAGIC	0x564D5868
#define VMPORT_PORT	0x5658
#define VMM_DATA	39
#define VMM_STATUS	40
#define VMM_COMMAND	41
#define VMM_READ_ID		0x45414552
#define VMM_REQUEST_ABSOLUTE	0x53424152

static int32	have_vmmouse;
static int32	shift, ext;

static void vmport(uint32 cmd, uint32 arg, uint32 *r)
{
	uint32 a, b, c, d;
	asm volatile("inl %%dx, %%eax"
		: "=a"(a), "=b"(b), "=c"(c), "=d"(d)
		: "a"(VMPORT_MAGIC), "b"(arg), "c"(cmd), "d"(VMPORT_PORT)
		: "memory");
	r[0] = a; r[1] = b; r[2] = c; r[3] = d;
}

static void kbc_wait_write(void) { int32 i; for (i = 0; i < 100000 && (inb(0x64) & 2); i++) ; }

void input_init(void)
{
	uint32 r[4];
	int32 i;
	/* i8042: 補助装置（マウス）を有効にし、データの報告を始めさせる（vmmouse の合図に使われる） */
	for (i = 0; i < 64 && (inb(0x64) & 1); i++) (void)inb(0x60);
	kbc_wait_write(); outb(0x64, 0xA8);
	kbc_wait_write(); outb(0x64, 0xD4);
	kbc_wait_write(); outb(0x60, 0xF4);
	for (i = 0; i < 64 && (inb(0x64) & 1); i++) (void)inb(0x60);

	vmport(VMM_COMMAND, VMM_READ_ID, r);
	vmport(VMM_STATUS, 0, r);
	if ((r[0] & 0xFFFF) >= 1) {
		vmport(VMM_DATA, 1, r);
		if (r[0] == 0x3442554A) {
			vmport(VMM_COMMAND, VMM_REQUEST_ABSOLUTE, r);
			have_vmmouse = 1;
		}
	}
	if (!have_vmmouse) kprintf("input: vmmouse が無い（マウスは使えない）\n");
}

/* マウスの出来事を一つ読む。無ければ 0 */
int32 input_mouse(int32 *x, int32 *y, int32 *buttons, int32 *wheel)
{
	uint32 r[4];
	if (!have_vmmouse) return 0;
	vmport(VMM_STATUS, 0, r);
	if ((r[0] & 0xFFFF0000) == 0xFFFF0000) {	/* 異常: 絶対座標をもう一度頼む */
		vmport(VMM_COMMAND, VMM_REQUEST_ABSOLUTE, r);
		return 0;
	}
	if ((r[0] & 0xFFFF) < 4) return 0;
	vmport(VMM_DATA, 4, r);
	*buttons = ((r[0] & 0x20) ? 1 : 0) | ((r[0] & 0x10) ? 2 : 0) | ((r[0] & 0x08) ? 4 : 0);
	*x = (int32)((r[1] & 0xFFFF) * SCR_W / 65536);
	*y = (int32)((r[2] & 0xFFFF) * SCR_H / 65536);
	*wheel = (int32)(signed char)(r[3] & 0xFF);
	return 1;
}

/* 走査コード（セット1）→ 文字 */
static const char kmap[0x3A] = {
	0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b', '\t',
	'q','w','e','r','t','y','u','i','o','p','[',']', '\n', 0, 'a','s',
	'd','f','g','h','j','k','l',';','\'','`', 0, '\\','z','x','c','v',
	'b','n','m',',','.','/', 0, '*', 0, ' '
};
static const char kmaps[0x3A] = {
	0, 27, '!','@','#','$','%','^','&','*','(',')','_','+', '\b', '\t',
	'Q','W','E','R','T','Y','U','I','O','P','{','}', '\n', 0, 'A','S',
	'D','F','G','H','J','K','L',':','"','~', 0, '|','Z','X','C','V',
	'B','N','M','<','>','?', 0, '*', 0, ' '
};

/* キーを一つ読む。無ければ 0。矢印などは KEY_* */
int32 input_key(void)
{
	while (inb(0x64) & 1) {
		int32 st = inb(0x64);
		int32 sc = inb(0x60) & 0xFF;
		if (st & 0x20) continue;	/* マウスのバイト（vmmouse を使うので捨てる） */
		if (sc == 0xE0) { ext = 1; continue; }
		if (sc == 0x2A || sc == 0x36) { shift = 1; continue; }
		if (sc == 0xAA || sc == 0xB6) { shift = 0; continue; }
		if (sc & 0x80) { ext = 0; continue; }
		if (ext) {
			ext = 0;
			switch (sc) {
			case 0x48: return KEY_UP;
			case 0x50: return KEY_DOWN;
			case 0x4B: return KEY_LEFT;
			case 0x4D: return KEY_RIGHT;
			case 0x49: return KEY_PGUP;
			case 0x51: return KEY_PGDN;
			}
			continue;
		}
		if (sc == 0x3F) return KEY_F5;
		if (sc == 0x41) return KEY_F7;
		if (sc == 0x42) return KEY_F8;
		if (sc < 0x3A && kmap[sc]) return shift ? kmaps[sc] : kmap[sc];
	}
	return 0;
}
