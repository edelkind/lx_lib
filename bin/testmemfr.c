#include <sys/times.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "lx_string.h"

#define SIZE 65536 /* 64k */
#define NCPY 6000  /* times to reverse data (multiple of 3) */
#define EACH 3

extern char *r_time();

int main(void) {
	struct tms tstart, tend;
	register int ncpy;
	int each;
	char *from;

	from = malloc (SIZE+1);

	if (!from) {
		fprintf (stderr, "malloc: %s\n", strerror(errno));
		_exit (1);
	}

	printf ("Using values: %d bytes; %d times\n\n", SIZE, NCPY);
	printf ("setting string ... "); fflush (stdout);
	{
		char *p = from;
		register char r;
		ncpy = SIZE; /* temp */
		while (ncpy--) {
			srand (rand());
			r = (rand() % 255) + 1; /* return 0-254, add 1 */
			*p++ = r;
		}

		*p = 0;
	}
	printf ("strlen = %d\n", strlen (from));

	each = EACH;
	do {
		lx_s sfrom; /* explicitly defined */

		sfrom.s     = from;
		sfrom.len   = SIZE;
		sfrom.alloc = SIZE;

		printf ("testing lx_strrev ... "); fflush(stdout);
		times (&tstart);
		for (ncpy = NCPY; ncpy > 0; ncpy-=3) {
			lx_strrev (&sfrom);
			lx_strrev (&sfrom);
			lx_strrev (&sfrom);
		}
		times (&tend);
		printf ("\t%s\n", r_time (&tstart, &tend));
	} while (--each);

	return 0;
}
