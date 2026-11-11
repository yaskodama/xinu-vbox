/* wm.h - Xinu の上のウィンドウシステム */
#ifndef WM_H
#define WM_H

/* 文字の大きさ（1=16 ドット、2=32 ドット）。寸法はすべて U(n) で比例させる */
extern int32 ui;
#define U(n)		((n) * ui)
#define TITLE_H		U(22)
#define MENU_H		U(24)
#define GRIP		U(12)

/* 色 */
#define C_DESK		0x4F6D7A
#define C_MENU		0xE8E8E8
#define C_WIN		0xFFFFFF
#define C_PANE		0xFFFFFF
#define C_LINE		0xA0A0A0
#define C_DARK		0x404040
#define C_TEXT		0x101010
#define C_DIM		0x808080
#define C_TITLE_ON	0x2B4C7E
#define C_TITLE_OFF	0xC4C8CC
#define C_SEL		0xBFD8F2
#define C_SELFOCUS	0x3D7BC6
#define C_HILITE	0xFFF2A8
#define C_RED		0xD03030
#define C_GREEN		0x2E8B3E
#define C_BLUE		0x2050B0
#define C_BTN		0xF0F0F0

enum { WM_DOWN, WM_DRAG, WM_UP };

struct win {
	int32	x, y, w, h;		/* 外枠（題名の帯を含む）	*/
	const char *title;
	int32	shown;
	int32	minw, minh;
	/* 中身の座標は中身の左上を (0,0) とする */
	void	(*draw)(struct win *, int32 cw, int32 ch);
	void	(*mouse)(struct win *, int32 ev, int32 mx, int32 my, int32 cw, int32 ch);
	void	(*wheel)(struct win *, int32 mx, int32 my, int32 dz, int32 cw, int32 ch);
	void	(*key)(struct win *, int32 k);
	char	tbuf[96];		/* 題名を動的に作るとき用	*/
};

void	wm_init(void);
void	wm_add(struct win *w);
void	wm_front(struct win *w);
void	wm_toggle(struct win *w);
struct win *wm_focus(void);
void	wm_dirty(void);
extern void (*wm_ui_hook)(void);
void	wm_run(int32 (*tick)(void));	/* 戻らない。tick() が 0 以外なら描き直す */

/* 中身を描くとき: 中身の左上の画面座標（draw の中で使う） */
extern int32 wm_ox, wm_oy, wm_cw, wm_ch;
void	wm_clip(int32 x, int32 y, int32 w, int32 h);	/* 中身の座標で、さらに狭める */
void	wm_unclip(void);					/* 中身全体に戻す */
uint32	wm_ms(void);

/* ───── 部品 ───── */
/* 一覧の欄。item は i 番目の文字列を buf に書いて色を返す */
struct lst {
	int32	n, sel, top;
	const char *head;		/* 欄の見出し（NULL なら無し） */
	uint32	(*item)(struct lst *, int32 i, char *buf, int32 bn);
	void	*ctx;
};
#define ROW_H	U(18)
void	lst_draw(struct lst *l, int32 x, int32 y, int32 w, int32 h, int32 focused);
int32	lst_hit(struct lst *l, int32 x, int32 y, int32 w, int32 h, int32 mx, int32 my);	/* 行番号か -1 */
void	lst_scroll(struct lst *l, int32 h, int32 dz);
void	lst_show(struct lst *l, int32 h, int32 i);	/* i 行目が見えるように */

void	btn_draw(int32 x, int32 y, int32 w, int32 h, const char *label, int32 enabled);
int32	in_rect(int32 mx, int32 my, int32 x, int32 y, int32 w, int32 h);
void	box_draw(int32 x, int32 y, int32 w, int32 h);	/* 欄の枠 */

#endif
