#include "lx_string.h"
extern void *memmove();
#if DMALLOC
# include "/usr/local/include/dmalloc.h"
#else
extern void *malloc();
#endif

#if 0
	*** lx_strff ***
	fast forward past the nth instance of a specified character 
	unless p == 0, a pointer to the previous beginning will be kept.
	the specified character will become the 0-termination for the new ptr.
	returns 0 on success.
#endif

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
