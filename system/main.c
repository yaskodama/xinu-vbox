/*  main.c  - main, greeter */

#include <xinu.h>

/* Sample process that prints a greeting N times with a small delay. */
process greeter(char *name, int32 count)
{
	int32 i;
	for (i = 1; i <= count; i++) {
		kprintf("[%s] hello from Xinu! (%d/%d)\n", name, i, count);
		sleepms(300);
	}
	return OK;
}

process	main(void)
{
	pid32	shpid;		/* Shell process ID */
	pid32	g1, g2;

	printf("\n\n");

	/* --- Sample program: spawn two cooperating processes --- */
	kprintf("=== Sample: two greeter processes running concurrently ===\n");
	g1 = create((void *)greeter, 4096, 50, "greeter-A", 2, "Alice", 3);
	g2 = create((void *)greeter, 4096, 50, "greeter-B", 2, "Bob",   3);
	resume(g1);
	resume(g2);
	/* Wait long enough for both to finish before launching the shell. */
	sleepms(2500);
	kprintf("=== Sample finished, starting shell ===\n\n");

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
