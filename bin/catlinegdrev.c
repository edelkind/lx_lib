#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include "lx_string.h"

#define BLOCKSIZE 8192

extern void p_time ();

int main(void) {
	lx_gd gd_stdin;
	lx_gd gd_stdout;
	lx_s s = {0};
	unsigned char match;

	struct tms tstart, tend;

	times(&tstart);
	lx_gdnew (&gd_stdin, 0, BLOCKSIZE);
	lx_gdnew (&gd_stdout, 1, BLOCKSIZE);

	do {
		if (lx_getln(&s, &gd_stdin, &match, BLOCKSIZE)) {
			fprintf (stderr, "lx_getln: %s\n", strerror(errno));
			exit (1);
		}

		lx_strrev (&s);
		lx_gdstrput (&gd_stdout, &s);
	} while (match);

	lx_gdflush (&gd_stdout);

	times(&tend);
	p_time (&tstart, &tend);

	return 0;
}
