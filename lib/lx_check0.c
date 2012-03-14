#include "lx_string.h"

/**
 * Ensure that s ends in a binary 0.  If not, add one.
 *
 * Returns 0 on success.
 */

char lx_check0 (s)
	lx_s *s;
{
	if (s->s[s->len-1]) return (lx_cadd(s, 0));
	return 0;
}

/**
 * Null-terminate s without adding to the length.
 *
 * Returns 0 on success, 1 if out of memory.
 */
char lx_post0 (s)
    lx_s *s;
{
    if (lx_setalloc(s, s->len+1))
        return 1;
    s->s[s->len] = 0;

    return 0;
}
