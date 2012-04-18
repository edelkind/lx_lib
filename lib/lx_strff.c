#include "lx_string.h"
#include <string.h>
//extern void *memmove();
#if DMALLOC
# include "/usr/local/include/dmalloc.h"
#else
#include <stdlib.h>
//extern void *malloc();
#endif


/** Fast forward past the nth instance of a specified character.  As in \ref
 * lx_strff, but the optional output will be in the form of a lx_s value.
 *
 * @see lx_strff()
 */
char lx_strffx (lx_s *s, lx_s *out, char c, unsigned n)
{
    register unsigned int ix;
    register char *px;
    register char cx;
    char *p;
    char rv = 0;

    px = s->s;
    ix = s->len;
    cx = c;

    if (out) *p = px;

    if (!(px)) {
        return 1; /* user error */
    }

    for (;;) {
        if (!ix) return 1;
        if (*px == cx) {
            if (!--n) {
                *px++ = 0; --ix; /* advance past c */
                if (out) {
                    rv = lx_striset(out, p, s->len - ix);
                }
                (void) lx_striset (s, px, ix);
                return rv;
            }
        }
        --ix; ++px;
    }
}


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
    if (!p) return lx_strffx(s, NULL, c, n);

    /* If we only want a pointer, create a temporary lx_s variable. The stack
     * will unwind the structure, but the allocated buffer will live on in *p.
     */
    {
        char rv;
        lx_s out = {0};

        rv = lx_strffx(s, &out, c, n);
        *p = out.s;

        return rv;
    }
}
