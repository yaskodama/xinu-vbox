/* gfx.c - 画面への描画
 *
 * QEMU の標準 VGA（PCI 1234:1111）は Bochs VBE の拡張を持つ。ポート 0x1CE/0x1CF で解像度を決め、
 * 線形フレームバッファ（PCI BAR0）に直接書く。裏画面（物理 8MB 番地から 3MB）に全部を描いてから表へ写す。
 * そのために setsegs（system/i386.c）でデータセグメントの上限を 4GB に広げてある。
 */
#include <xinu.h>
#include "gfx.h"

extern	const int jp_count;
extern	const unsigned short jp_uni[];
extern	const unsigned char jp_bits[][32];
extern	const unsigned char asc16_bits[95][16];

#define VBE_INDEX	0x01CE
#define VBE_DATA	0x01CF

static uint32	*lfb;				/* 表の画面			*/
static uint32	*back = (uint32 *)0x800000;	/* 裏画面（論理 1440x900、ヒープの外: 8MB〜13.2MB）。
						   16MB の手前には null プロセスのスタックがある */
int32	ui = 1;					/* 文字の大きさ: 1＝16 ドット（既定。画面では 32 画素） */
static int32	cx0, cy0, cx1, cy1;		/* 描いてよい範囲 [cx0,cx1) x [cy0,cy1) */
static int32	curx = -100, cury = -100;
static int32	ox, oy;				/* 描画の原点（ウィンドウの中身の左上） */

void gfx_origin(int32 x, int32 y) { ox = x; oy = y; }

static void vbe_w(int32 idx, int32 val) { outw(VBE_INDEX, idx); outw(VBE_DATA, val); }
static int32 vbe_r(int32 idx) { outw(VBE_INDEX, idx); return inw(VBE_DATA) & 0xFFFF; }

int32 gfx_init(void)
{
	int32 dev;
	uint32 bar0;
	if ((vbe_r(0) & 0xFFF0) != 0xB0C0) {
		kprintf("gfx: Bochs VBE が無い（QEMU は -vga std で起動する）\n");
		return SYSERR;
	}
	dev = find_pci_device(0x1111, 0x1234, 0);
	if (dev == SYSERR) {
		kprintf("gfx: VGA の PCI 装置が見つからない\n");
		return SYSERR;
	}
	pci_bios_read_config_dword(dev, 0x10, &bar0);
	lfb = (uint32 *)(bar0 & 0xFFFFFFF0);
	vbe_w(4, 0);			/* いったん無効	*/
	vbe_w(1, PHYS_W);
	vbe_w(2, PHYS_H);
	vbe_w(3, 32);
	vbe_w(4, 0x41);			/* 有効＋線形フレームバッファ */
	gfx_noclip();
	return OK;
}

void gfx_clip(int32 x, int32 y, int32 w, int32 h)
{
	cx0 = x < 0 ? 0 : x;  cy0 = y < 0 ? 0 : y;
	cx1 = x + w > SCR_W ? SCR_W : x + w;
	cy1 = y + h > SCR_H ? SCR_H : y + h;
}
void gfx_noclip(void) { cx0 = 0; cy0 = 0; cx1 = SCR_W; cy1 = SCR_H; }

void gfx_fill(int32 x, int32 y, int32 w, int32 h, uint32 c)
{
	x += ox; y += oy;
	{
	int32 x0 = x < cx0 ? cx0 : x, y0 = y < cy0 ? cy0 : y;
	int32 x1 = x + w > cx1 ? cx1 : x + w, y1 = y + h > cy1 ? cy1 : y + h;
	int32 i, j;
	for (j = y0; j < y1; j++) {
		uint32 *p = back + j * SCR_W;
		for (i = x0; i < x1; i++) p[i] = c;
	}
	}
}

void gfx_frame(int32 x, int32 y, int32 w, int32 h, uint32 c)
{
	gfx_fill(x, y, w, 1, c);
	gfx_fill(x, y + h - 1, w, 1, c);
	gfx_fill(x, y, 1, h, c);
	gfx_fill(x + w - 1, y, 1, h, c);
}

static inline void pset(int32 x, int32 y, uint32 c)
{
	if (x >= cx0 && x < cx1 && y >= cy0 && y < cy1) back[y * SCR_W + x] = c;
}

/* UTF-8 を一文字読む。読んだバイト数を *n に返す */
static uint32 utf8(const char *s, int32 *n)
{
	const unsigned char *u = (const unsigned char *)s;
	if (u[0] < 0x80) { *n = 1; return u[0]; }
	if (u[0] < 0xE0 && u[1]) { *n = 2; return ((u[0] & 0x1F) << 6) | (u[1] & 0x3F); }
	if (u[0] < 0xF0 && u[1] && u[2]) { *n = 3; return ((u[0] & 0x0F) << 12) | ((u[1] & 0x3F) << 6) | (u[2] & 0x3F); }
	*n = 1;
	return '?';
}

static const unsigned char *glyph(uint32 cp)
{
	int32 lo = 0, hi = jp_count - 1;
	if (cp == 0x3000) return NULL;	/* 全角空白 */
	while (lo <= hi) {
		int32 mid = (lo + hi) / 2;
		if (jp_uni[mid] == cp) return jp_bits[mid];
		if (jp_uni[mid] < cp) lo = mid + 1; else hi = mid - 1;
	}
	return NULL;
}

static int32 charw(uint32 cp) { return ((cp < 0x80) ? 8 : (cp >= 0xFF61 && cp <= 0xFF9F) ? 8 : 16) * ui; }

static inline void dot(int32 x, int32 y, uint32 c)
{
	int32 i, j;
	for (j = 0; j < ui; j++) for (i = 0; i < ui; i++) pset(x + i, y + j, c);
}

static void drawchar(int32 x, int32 y, uint32 cp, uint32 c)
{
	int32 r, b;
	if (cp < 0x80) {
		if (cp < 0x20 || cp > 0x7E) return;
		for (r = 0; r < 16; r++) {
			unsigned char bits = asc16_bits[cp - 0x20][r];
			for (b = 0; b < 8; b++) if (bits & (0x80 >> b)) dot(x + b * ui, y + r * ui, c);
		}
		return;
	}
	{
		const unsigned char *g = glyph(cp);
		if (!g) {
			if (cp != 0x3000) gfx_frame(x + 2 * ui - ox, y + 2 * ui - oy, 12 * ui, 12 * ui, c);	/* 字形が無い字は □ */
			return;
		}
		for (r = 0; r < 16; r++) {
			uint32 bits = (g[r * 2] << 8) | g[r * 2 + 1];
			for (b = 0; b < 16; b++) if (bits & (0x8000 >> b)) dot(x + b * ui, y + r * ui, c);
		}
	}
}

int32 gfx_textn(int32 x, int32 y, const char *s, int32 maxw, uint32 c)
{
	int32 x0, n;
	x += ox; y += oy; x0 = x;
	while (*s) {
		uint32 cp = utf8(s, &n);
		int32 w = charw(cp);
		if (maxw >= 0 && x + w - x0 > maxw) break;
		if (cp == '\t') { x += 32 * ui; s += n; continue; }
		if (x < cx1 && x + w > cx0 && y < cy1 && y + FONT_H > cy0) drawchar(x, y, cp, c);
		x += w;
		s += n;
	}
	return x - x0;
}
int32 gfx_text(int32 x, int32 y, const char *s, uint32 c) { return gfx_textn(x, y, s, -1, c); }

int32 gfx_fitbytes(const char *s, int32 maxw)
{
	int32 w = 0, n, b = 0;
	while (s[b]) {
		uint32 cp = utf8(s + b, &n);
		int32 cw = cp == '\t' ? 32 * ui : charw(cp);
		if (w + cw > maxw && b > 0) break;
		w += cw; b += n;
	}
	return b;
}

int32 gfx_textw(const char *s)
{
	int32 w = 0, n;
	while (*s) { uint32 cp = utf8(s, &n); w += cp == '\t' ? 32 * ui : charw(cp); s += n; }
	return w;
}

/* ───── カーソル（矢印）: 表の画面にだけ描く。裏画面は汚さない ───── */
static const char *arrow[19] = {
	"X           ", "XX          ", "X.X         ", "X..X        ", "X...X       ",
	"X....X      ", "X.....X     ", "X......X    ", "X.......X   ", "X........X  ",
	"X.........X ", "X......XXXXX", "X...X..X    ", "X..XX..X    ", "X.X  X..X   ",
	"XX   X..X   ", "X     X..X  ", "      X..X  ", "       XX   "
};

/* 論理の矩形を表の画面へ（縦横 ZOOM 倍に広げて）写す */
static void blit(int32 x, int32 y, int32 w, int32 h)
{
	int32 j, i, x1, y1;
	if (x < 0) { w += x; x = 0; }
	if (y < 0) { h += y; y = 0; }
	x1 = x + w > SCR_W ? SCR_W : x + w;
	y1 = y + h > SCR_H ? SCR_H : y + h;
	for (j = y; j < y1; j++) {
		uint32 *s = back + j * SCR_W;
		uint32 *d0 = lfb + (j * ZOOM) * PHYS_W, *d1 = d0 + PHYS_W;
		for (i = x; i < x1; i++) {
			uint32 c = s[i];
			d0[2 * i] = c; d0[2 * i + 1] = c;
			d1[2 * i] = c; d1[2 * i + 1] = c;
		}
	}
}

/* カーソルは表の画面に直接描く（論理 12x19 を ZOOM 倍） */
static void draw_cursor(int32 x, int32 y)
{
	int32 r, b, i, j;
	for (r = 0; r < 19; r++) for (b = 0; b < 12; b++) {
		char ch = arrow[r][b];
		if (ch == ' ') continue;
		for (j = 0; j < ZOOM; j++) for (i = 0; i < ZOOM; i++) {
			int32 px = (x + b) * ZOOM + i, py = (y + r) * ZOOM + j;
			if (px >= 0 && px < PHYS_W && py >= 0 && py < PHYS_H) lfb[py * PHYS_W + px] = ch == 'X' ? C_BLACK : C_WHITE;
		}
	}
}

void gfx_cursor(int32 x, int32 y)
{
	if (!lfb) return;
	if (x == curx && y == cury) return;
	blit(curx, cury, 12, 19);
	curx = x; cury = y;
	draw_cursor(curx, cury);
}

void gfx_present_rect(int32 x, int32 y, int32 w, int32 h)
{
	if (!lfb) return;
	blit(x, y, w, h);
	draw_cursor(curx, cury);
}
void gfx_present(void) { gfx_present_rect(0, 0, SCR_W, SCR_H); }
