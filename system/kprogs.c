/* kprogs.c - 組み込んだことのはのプログラムの一覧（install.sh が生成） */
#include <xinu.h>
#include "krt.h"
extern struct kprogram kp0_prog;
extern struct kprogram kp1_prog;
extern struct kprogram kp2_prog;
extern struct kprogram kp3_prog;
extern struct kprogram kp4_prog;
extern struct kprogram kp5_prog;
extern struct kprogram kp6_prog;
extern struct kprogram kp7_prog;
extern struct kprogram kp8_prog;
struct kprogram *kprogs[32] = { &kp0_prog, &kp1_prog, &kp2_prog, &kp3_prog, &kp4_prog, &kp5_prog, &kp6_prog, &kp7_prog, &kp8_prog, };	/* Xinu の中でコンパイルしたものを後ろに足す（KPROGS_MAX） */
int32 nkprogs = 9;
