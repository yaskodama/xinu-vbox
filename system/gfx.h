/* gfx.h - 画面（QEMU 標準 VGA の Bochs VBE 拡張）への描画 */
#ifndef GFX_H
#define GFX_H

/* 論理の画面（窓や文字の座標はこの大きさで考える）。表の画面はその縦横2倍（Retina の Mac で 1 点＝2x2 画素） */
#define SCR_W	1440
#define SCR_H	900
#define ZOOM	2
#define PHYS_W	(SCR_W * ZOOM)
#define PHYS_H	(SCR_H * ZOOM)

/* 色（0xRRGGBB） */
#define C_BLACK		0x000000
#define C_WHITE		0xFFFFFF

int32	gfx_init(void);			/* 画面を 1024x768x32 にする。失敗なら SYSERR */
void	gfx_clip(int32 x, int32 y, int32 w, int32 h);	/* 以後の描画をこの矩形に限る */
void	gfx_noclip(void);
void	gfx_origin(int32 x, int32 y);	/* 以後の座標の原点（クリップは画面座標のまま） */
void	gfx_fill(int32 x, int32 y, int32 w, int32 h, uint32 c);
void	gfx_frame(int32 x, int32 y, int32 w, int32 h, uint32 c);	/* 1 ドットの枠 */
int32	gfx_text(int32 x, int32 y, const char *s, uint32 c);	/* UTF-8。描いた幅を返す */
int32	gfx_textn(int32 x, int32 y, const char *s, int32 maxw, uint32 c);	/* 幅 maxw で切る */
int32	gfx_textw(const char *s);
int32	gfx_fitbytes(const char *s, int32 maxw);	/* 幅 maxw に入るバイト数（文字の途中で切らない） */
void	gfx_present(void);		/* 裏画面を表に写し、カーソルを描く */
void	gfx_present_rect(int32 x, int32 y, int32 w, int32 h);
void	gfx_cursor(int32 x, int32 y);	/* カーソルだけ動かす */

extern int32 ui;		/* 文字の大きさ（1 か 2）。wm.h の U(n) もこれを使う */
#define FONT_H	(16 * ui)
#endif
