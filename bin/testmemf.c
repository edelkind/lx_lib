#include <sys/times.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "lx_string.h"

#define SIZE 65536 /* 64k */
#define NCPY 3000  /* times to copy data (multiple of 3) */
#define EACH 3

extern char *r_time();

int main(void) {
	struct tms tstart, tend;
	register int ncpy;
	int each;
	char *from;
	char *to;

	from = malloc (SIZE+1);
	to   = malloc (SIZE+1);

	if (!from || !to) {
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
	printf ("strlen = %u\n", (unsigned) strlen (from));

	each = EACH;
	do {
		printf ("testing memcpy ... "); fflush(stdout);
		times (&tstart);
		for (ncpy = NCPY; ncpy > 0; ncpy-=3) {
			memcpy (to, from, SIZE);
			memcpy (to, from, SIZE);
			memcpy (to, from, SIZE);
		}
		times (&tend);
		printf ("\t%s\n", r_time (&tstart, &tend));
	} while (--each);

	each = EACH;
	do {
		printf ("testing memmove ... "); fflush(stdout);
		times (&tstart);
		for (ncpy = NCPY; ncpy > 0; ncpy-=3) {
			memmove (to, from, SIZE);
			memmove (to, from, SIZE);
			memmove (to, from, SIZE);
		}
		times (&tend);
		printf ("\t%s\n", r_time (&tstart, &tend));
	} while (--each);

	each = EACH;
	do {
		printf ("testing strcpy ... "); fflush(stdout);
		times (&tstart);
		for (ncpy = NCPY; ncpy > 0; ncpy-=3) {
			strcpy (to, from);
			strcpy (to, from);
			strcpy (to, from);
		}
		times (&tend);
		printf ("\t%s\n", r_time (&tstart, &tend));
	} while (--each);

	each = EACH;
	do {
		printf ("testing strncpy ... "); fflush(stdout);
		times (&tstart);
		for (ncpy = NCPY; ncpy > 0; ncpy-=3) {
			strncpy (to, from, SIZE);
			strncpy (to, from, SIZE);
			strncpy (to, from, SIZE);
		}
		times (&tend);
		printf ("\t%s\n", r_time (&tstart, &tend));
	} while (--each);

	each = EACH;
	do {
		lx_s sfrom; /* explicitly defined */
		lx_s sto;   /* explicitly defined */

		sfrom.s     = from;
		sto.s       = to;
		sfrom.len   = sto.len   = SIZE;
		sfrom.alloc = sto.alloc = SIZE;

		printf ("testing lx_strcopy ... "); fflush(stdout);
		times (&tstart);
		for (ncpy = NCPY; ncpy > 0; ncpy-=3) {
			lx_strcopy (&sto, &sfrom);
			lx_strcopy (&sto, &sfrom);
			lx_strcopy (&sto, &sfrom);
		}
		times (&tend);
		printf ("\t%s\n", r_time (&tstart, &tend));
	} while (--each);

	return 0;
}
