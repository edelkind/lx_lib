/* cat_gdemu: emulate cat(1) */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/times.h>
#include <unistd.h>
#include "lx_string.h"

#define BLOCKSIZE 8192

#define GDIN_FILENO 0
#define GDOUT_FILENO 1

extern void p_time ();

int main(void) {
	lx_gd gd;

	struct tms tstart, tend;

	times(&tstart);
	lx_gdnew (&gd, GDIN_FILENO, BLOCKSIZE);

	for (;;) {
		if (lx_gdfill(&gd)) _exit(1);
		if (gd.n == 0) break;
		gd.fd = GDOUT_FILENO;
		lx_gdflush(&gd);
		gd.fd = GDIN_FILENO;
	}

	times(&tend);
	p_time (&tstart, &tend);

	return 0;
}
