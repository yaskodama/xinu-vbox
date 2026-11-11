/*  main.c  - main, greeter */

#include <xinu.h>

/* ことのはの開発環境（ウィンドウシステム＋ブラウザ＋デバッガ）。~/kotonoha/xinu/install.sh で組み込む */
extern	process	kgui_main(void);
extern	int32	gfx_init(void);

process	main(void)
{
	pid32	shpid;		/* Shell process ID */

	printf("\n\n");

	/* --- 画面があれば、ことのはの開発環境を別のプロセスで動かす（シェルはシリアルのまま） --- */
	if (gfx_init() == OK) {
		resume(create(kgui_main, 65536, 30, "kgui", 0));
		kprintf("ことのはの開発環境を画面に出しました\n");
	}

	/* Create a local file system on the RAM disk */

	lfscreate(RAM0, 40, 20480);

	/* Run the Xinu shell */

	recvclr();
	resume(shpid = create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
	    if (receive() == shpid) {
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(shpid = create(shell, 4096, 20, "shell", 1, CONSOLE));
	    }
	}
	return OK;
}
