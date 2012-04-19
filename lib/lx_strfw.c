#include "lx_string.h"
#include <string.h>
//extern void *memmove();
#include <stdlib.h>
//extern void *malloc();

/**
 * Move the string forward n bytes.  The place in memory is not
 * modified, nor is the allocation.
 * 
 * If \a out != NULL, it will be used to store the removed portion.
 * 
 * Returns 0 on success, or 1 on ENOMEM.
 */
char lx_strfwx (s, out, n)
    lx_s *s;
    lx_s *out;
    unsigned int n;
{
    int rv = 0;

    if (s->len < n) n = s->len;

    if (out) {
        rv = lx_striset(out, s->s, n);
    }

    s->len -= n;
    memmove (s->s, s->s + n, s->len);
    return rv;
}

/** Move the string forward n bytes.
 *
 * If p != 0, a pointer to the removed portion will be kept (allocated with
 * malloc()).
 * 
 * @see lx_strfwx()
 */
char lx_strfw (s, p, n)
    lx_s *s;
    char **p;
    unsigned int n;
{
    if (!p) return lx_strfwx(s, NULL, n);

    {
        lx_s tmp = {0};
        char rv;

        rv = lx_strfwx(s, &tmp, n);
        *p = tmp.s; /* doesn't matter if strfwx failed here */
        return rv;
    }
}
