/* input.h - キーボードとマウス */
#ifndef INPUT_H
#define INPUT_H
#define KEY_UP		0x101
#define KEY_DOWN	0x102
#define KEY_LEFT	0x103
#define KEY_RIGHT	0x104
#define KEY_PGUP	0x105
#define KEY_PGDN	0x106
#define KEY_F5		0x110
#define KEY_F7		0x111
#define KEY_F8		0x112
void	input_init(void);
int32	input_mouse(int32 *x, int32 *y, int32 *buttons, int32 *wheel);
int32	input_key(void);
#endif
