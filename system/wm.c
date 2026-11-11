/* wm.c - Xinu の上のウィンドウシステム
 *
 * 重なったウィンドウを奥から順に裏画面へ描き、まとめて表へ写す。
 * 題名の帯を掴むと移動、右下の角を掴むと大きさを変える。クリックしたウィンドウが手前に来る。
 * 上端のメニュー帯にはウィンドウの名前が並び、押すと表示/非表示が切り替わる。
 * 入力は GUI のプロセスが 10ms ごとに見回る（割り込みは使わない）。
 */
#include <xinu.h>
#include "gfx.h"
#include "input.h"
#include "wm.h"

#define MAXWIN	12

static struct win *zs[MAXWIN];	/* 奥→手前				*/
static int32	nz;
static struct win *all[MAXWIN];	/* 登録順（メニュー帯の並び）		*/
static int32	nall;
static int32	dirty = 1;
int32	wm_ox, wm_oy, wm_cw, wm_ch;

/* 見回りの回数から作るおおよその時刻（ミリ秒）。この Xinu には ms 単位の時計の変数が無い */
static uint32 loops;
uint32 wm_ms(void) { return loops * 10; }
void wm_clip(int32 x, int32 y, int32 w, int32 h)
{
	/* 中身の範囲との共通部分 */
	int32 x0 = x < 0 ? 0 : x, y0 = y < 0 ? 0 : y;
	int32 x1 = x + w > wm_cw ? wm_cw : x + w, y1 = y + h > wm_ch ? wm_ch : y + h;
	if (x1 < x0) x1 = x0;
	if (y1 < y0) y1 = y0;
	gfx_clip(wm_ox + x0, wm_oy + y0, x1 - x0, y1 - y0);
}
void wm_unclip(void) { gfx_clip(wm_ox, wm_oy, wm_cw, wm_ch); }

void wm_init(void) { nz = nall = 0; }
void wm_dirty(void) { dirty = 1; }

void wm_add(struct win *w)
{
	if (nall < MAXWIN) all[nall++] = w;
	if (nz < MAXWIN) zs[nz++] = w;
	w->shown = 1;
	dirty = 1;
}

void wm_front(struct win *w)
{
	int32 i, j;
	for (i = 0; i < nz; i++) if (zs[i] == w) break;
	if (i == nz) return;
	for (j = i; j < nz - 1; j++) zs[j] = zs[j + 1];
	zs[nz - 1] = w;
	dirty = 1;
}

void wm_toggle(struct win *w)
{
	if (w->shown && zs[nz - 1] == w) w->shown = 0;
	else { w->shown = 1; wm_front(w); }
	dirty = 1;
}

struct win *wm_focus(void)
{
	int32 i;
	for (i = nz - 1; i >= 0; i--) if (zs[i]->shown) return zs[i];
	return NULL;
}

int32 in_rect(int32 mx, int32 my, int32 x, int32 y, int32 w, int32 h)
{
	return mx >= x && mx < x + w && my >= y && my < y + h;
}

void box_draw(int32 x, int32 y, int32 w, int32 h)
{
	gfx_fill(x, y, w, h, C_PANE);
	gfx_frame(x, y, w, h, C_LINE);
}

void btn_draw(int32 x, int32 y, int32 w, int32 h, const char *label, int32 enabled)
{
	int32 tw = gfx_textw(label);
	gfx_fill(x, y, w, h, enabled ? C_BTN : 0xE4E4E4);
	gfx_frame(x, y, w, h, enabled ? C_DARK : 0xB8B8B8);
	gfx_fill(x + 1, y + h - 2, w - 2, 1, enabled ? 0xC0C0C0 : 0xE4E4E4);
	gfx_text(x + (w - tw) / 2, y + (h - FONT_H) / 2, label, enabled ? C_TEXT : 0xA8A8A8);
}

/* ───── 一覧の欄 ───── */
void lst_draw(struct lst *l, int32 x, int32 y, int32 w, int32 h, int32 focused)
{
	char buf[200];
	int32 i, yy, rows, hy = 0;
	box_draw(x, y, w, h);
	if (l->head) {
		gfx_fill(x + 1, y + 1, w - 2, ROW_H, 0xEDEFF2);
		gfx_textn(x + U(4), y + U(1), l->head, w - U(8), C_DIM);
		gfx_fill(x + 1, y + ROW_H + 1, w - 2, 1, C_LINE);
		hy = ROW_H + 1;
	}
	rows = (h - hy - 2) / ROW_H;
	if (l->top > l->n - rows) l->top = l->n - rows;
	if (l->top < 0) l->top = 0;
	wm_clip(x + 1, y + 1 + hy, w - 2, h - 2 - hy);
	for (i = l->top, yy = y + 1 + hy; i < l->n && yy < y + h; i++, yy += ROW_H) {
		uint32 c = l->item(l, i, buf, sizeof(buf));
		if (i == l->sel) {
			gfx_fill(x + 1, yy, w - 2, ROW_H, focused ? C_SELFOCUS : C_SEL);
			if (focused) c = C_WHITE;
		}
		gfx_textn(x + U(4), yy + U(1), buf, w - U(14), c);
	}
	/* 位置の目安（右端の細い帯） */
	if (l->n > rows && rows > 0) {
		int32 th = (h - hy - 2) * rows / l->n, ty = (h - hy - 2 - th) * l->top / (l->n - rows);
		if (th < 8) th = 8;
		gfx_fill(x + w - U(6), y + 1 + hy + ty, U(4), th, 0xA8B0BC);
	}
	wm_unclip();
}

int32 lst_hit(struct lst *l, int32 x, int32 y, int32 w, int32 h, int32 mx, int32 my)
{
	int32 hy = l->head ? ROW_H + 1 : 0, i;
	if (!in_rect(mx, my, x, y + 1 + hy, w, h - 2 - hy)) return -1;
	i = l->top + (my - y - 1 - hy) / ROW_H;
	return i < l->n ? i : -1;
}

void lst_scroll(struct lst *l, int32 h, int32 dz)
{
	l->top += dz * 3;
	if (l->top < 0) l->top = 0;
	(void)h;
}

void lst_show(struct lst *l, int32 h, int32 i)
{
	int32 rows = (h - (l->head ? ROW_H + 1 : 0) - 2) / ROW_H;
	if (i < l->top) l->top = i;
	else if (rows > 0 && i >= l->top + rows) l->top = i - rows + 1;
}

/* ───── 描画 ───── */
static void draw_win(struct win *w, int32 focused)
{
	int32 cw = w->w - 2, ch = w->h - TITLE_H - 1;
	int32 tw;
	/* 影と枠 */
	gfx_noclip();
	gfx_fill(w->x + U(4), w->y + U(4), w->w, w->h, 0x33444C);
	gfx_fill(w->x, w->y, w->w, w->h, C_WIN);
	gfx_frame(w->x, w->y, w->w, w->h, C_DARK);
	/* 題名の帯 */
	gfx_fill(w->x + 1, w->y + 1, w->w - 2, TITLE_H - 1, focused ? C_TITLE_ON : C_TITLE_OFF);
	gfx_fill(w->x + 1, w->y + TITLE_H, w->w - 2, 1, C_DARK);
	gfx_clip(w->x + 1, w->y + 1, w->w - U(30), TITLE_H - 1);
	tw = gfx_textw(w->title);
	gfx_text(w->x + (w->w - tw) / 2 > w->x + U(8) ? w->x + (w->w - tw) / 2 : w->x + U(8), w->y + U(3), w->title,
		 focused ? C_WHITE : C_TEXT);
	gfx_noclip();
	/* 閉じる箱 */
	gfx_fill(w->x + w->w - U(20), w->y + U(5), U(13), U(13), focused ? 0x6C86AC : 0xE0E0E0);
	gfx_frame(w->x + w->w - U(20), w->y + U(5), U(13), U(13), focused ? C_WHITE : C_DARK);
	/* 中身 */
	wm_ox = w->x + 1; wm_oy = w->y + TITLE_H + 1; wm_cw = cw; wm_ch = ch;
	gfx_clip(wm_ox, wm_oy, cw, ch);
	/* draw の中では中身の左上を (0,0) とする */
	gfx_origin(wm_ox, wm_oy);
	if (w->draw) w->draw(w, cw, ch);
	gfx_origin(0, 0);
	/* 大きさを変える角 */
	gfx_clip(wm_ox, wm_oy, cw, ch);
	{
		int32 i;
		for (i = 0; i < 3; i++) {
			gfx_fill(w->x + w->w - U(5) - i * U(4), w->y + w->h - U(5), U(2), U(2), C_DIM);
			gfx_fill(w->x + w->w - U(5), w->y + w->h - U(5) - i * U(4), U(2), U(2), C_DIM);
		}
	}
	gfx_noclip();
}

#define MENU_GAP	U(18)
static const char *size_label(void) { return ui == 2 ? "文字を小さく" : "文字を大きく"; }
void (*wm_ui_hook)(void);	/* 文字の大きさを変えたとき（窓の並べ直し） */
static const char *menu_title(void) { return ui == 2 ? "" : "Xinu ことのは"; }
static void draw_menu(void)
{
	int32 i, x = U(8);
	gfx_noclip();
	gfx_fill(0, 0, SCR_W, MENU_H, C_MENU);
	gfx_fill(0, MENU_H - 1, SCR_W, 1, C_DARK);
	if (*menu_title()) x += gfx_text(x, U(4), menu_title(), C_TITLE_ON) + MENU_GAP;
	for (i = 0; i < nall; i++) {
		int32 tw = gfx_textw(all[i]->title);
		if (all[i]->shown) gfx_fill(x - U(6), U(3), tw + U(12), MENU_H - U(6), 0xD2DAE6);
		gfx_text(x, U(4), all[i]->title, all[i]->shown ? C_TEXT : C_DIM);
		x += tw + MENU_GAP;
	}
	{
		int32 tw = gfx_textw(size_label());
		gfx_fill(SCR_W - tw - U(18), U(3), tw + U(12), MENU_H - U(6), 0xF8F0D0);
		gfx_frame(SCR_W - tw - U(18), U(3), tw + U(12), MENU_H - U(6), C_LINE);
		gfx_text(SCR_W - tw - U(12), U(4), size_label(), C_TEXT);
	}
}

/* メニュー帯の何を押したか: 窓の番号、-2＝文字の大きさ、-1＝なし */
static int32 menu_hit(int32 mx)
{
	int32 i, x = U(8) + (*menu_title() ? gfx_textw(menu_title()) + MENU_GAP : 0);
	int32 tw = gfx_textw(size_label());
	if (mx >= SCR_W - tw - U(18)) return -2;
	for (i = 0; i < nall; i++) {
		int32 w = gfx_textw(all[i]->title);
		if (mx >= x - U(6) && mx < x + w + U(6)) return i;
		x += w + MENU_GAP;
	}
	return -1;
}

static void redraw(void)
{
	int32 i;
	struct win *f = wm_focus();
	gfx_noclip();
	gfx_fill(0, MENU_H, SCR_W, SCR_H - MENU_H, C_DESK);
	{
		const char *msg = "PC Xinu + ことのは";
		gfx_text(SCR_W - gfx_textw(msg) - U(10), SCR_H - FONT_H - U(6), msg, 0xC8D6DC);
	}
	for (i = 0; i < nz; i++) if (zs[i]->shown) draw_win(zs[i], zs[i] == f);
	draw_menu();
	gfx_present();
	dirty = 0;
}

/* ───── 入力の振り分け ───── */
static struct win *top_at(int32 mx, int32 my)
{
	int32 i;
	for (i = nz - 1; i >= 0; i--) {
		struct win *w = zs[i];
		if (w->shown && in_rect(mx, my, w->x, w->y, w->w, w->h)) return w;
	}
	return NULL;
}

void wm_run(int32 (*tick)(void))
{
	int32 mx = SCR_W / 2, my = SCR_H / 2, mb = 0;
	int32 x, y, b, z, k;
	struct win *drag = NULL, *size = NULL, *press = NULL;
	int32 dx = 0, dy = 0;
	uint32 last = 0;

	while (TRUE) {
		while (input_mouse(&x, &y, &b, &z)) {
			int32 down = (b & 1) && !(mb & 1), up = !(b & 1) && (mb & 1);
			mx = x; my = y;
			if (z) {
				struct win *w = top_at(mx, my);
				if (w && w->wheel) {
					w->wheel(w, mx - w->x - 1, my - w->y - TITLE_H - 1, z, w->w - 2, w->h - TITLE_H - 1);
					dirty = 1;
				}
			}
			if (down) {
				struct win *w = top_at(mx, my);
				if (my < MENU_H) {
					int32 i = menu_hit(mx);
					if (i >= 0) wm_toggle(all[i]);
					else if (i == -2) { ui = ui == 2 ? 1 : 2; if (wm_ui_hook) wm_ui_hook(); dirty = 1; }
				} else if (w) {
					wm_front(w);
					if (my < w->y + TITLE_H + 1) {
						if (mx >= w->x + w->w - U(22)) { w->shown = 0; dirty = 1; }
						else { drag = w; dx = mx - w->x; dy = my - w->y; }
					} else if (mx >= w->x + w->w - GRIP && my >= w->y + w->h - GRIP) {
						size = w; dx = w->x + w->w - mx; dy = w->y + w->h - my;
					} else if (w->mouse) {
						press = w;
						w->mouse(w, WM_DOWN, mx - w->x - 1, my - w->y - TITLE_H - 1, w->w - 2, w->h - TITLE_H - 1);
					}
				}
			} else if (b & 1) {
				if (drag) {
					drag->x = mx - dx; drag->y = my - dy;
					if (drag->y < MENU_H) drag->y = MENU_H;
					dirty = 1;
				} else if (size) {
					size->w = mx + dx - size->x; size->h = my + dy - size->y;
					if (size->w < size->minw) size->w = size->minw;
					if (size->h < size->minh) size->h = size->minh;
					dirty = 1;
				} else if (press && press->mouse) {
					press->mouse(press, WM_DRAG, mx - press->x - 1, my - press->y - TITLE_H - 1,
						     press->w - 2, press->h - TITLE_H - 1);
				}
			} else if (up) {
				if (press && press->mouse)
					press->mouse(press, WM_UP, mx - press->x - 1, my - press->y - TITLE_H - 1,
						     press->w - 2, press->h - TITLE_H - 1);
				drag = size = press = NULL;
			}
			mb = b;
		}
		while ((k = input_key()) != 0) {
			struct win *f = wm_focus();
			if (f && f->key) { f->key(f, k); dirty = 1; }
		}
		if (tick && tick()) dirty = 1;
		/* 描き直しは多くても 30 回/秒 */
		if (dirty && wm_ms() - last >= 33) {
			redraw();
			last = wm_ms();
		}
		gfx_cursor(mx, my);
		sleepms(10);
		loops++;
	}
}
