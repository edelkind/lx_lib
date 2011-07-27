#include "lx_string.h"
extern void *memmove();
#if DMALLOC
# include "/usr/local/include/dmalloc.h"
#else
extern void *malloc();
#endif

/**
 * Fast forward past the nth instance of a specified character.
 * The current implementation copies the remaining data to the beginning of s
 * (without reallocating).
 * 
 * If p is not null, it will hold a pointer to the previous beginning
 * (allocated with malloc()).
 * 
 * p[index] (the index of the specified character) will be the 0-termination
 * for the new ptr.
 * 
 * Returns 0 on success.
 */

char lx_strff (s, p, c, n)
	struct lx_string *s;
	char **p;
	char c;
	unsigned int n;
{
	register unsigned int ix;
	register char *px;
	register char cx;

	px = s->s;
	ix = s->len;
	cx = c;

	if (p) *p = px;

	if (!(px)) {
		return 1; /* user error */
	}

	for (;;) {
		if (!ix) return 1;
		if (*px == cx) {
			if (!--n) {
				*px++ = 0; --ix; /* advance past c */
				if (p) {
					char *q = *p;
					*p = (char *)malloc(s->len - ix);
					memmove(*p, q, s->len - ix);
				}
				lx_striset (s, px, ix);
				return 0;
			}
		}
		--ix; ++px;
	}
}
