#include "lx_string.h"

#include <string.h>
//extern void *memmove();

/**
 * Insert len bytes of string p into s, at position off, allocating
 * additional space if necessary.  del characters will be removed from
 * s at the place of insert.
 * 
 * s must already contain at least off+del bytes.
 * 
 * Returns 0 on success.
 */
char lx_strinsert (s, p, len, off, del)
    lx_s *s;
    const char *p;
    unsigned int len, off, del;
{
    char *start_from, *start_to;

    if (lx_setalloc (s, (s->len + len - del)) != 0)
	return 1;

    start_to = s->s + off;
    start_from = start_to + del;

    memmove(start_to + len, start_from, s->len - (start_from - s->s));
    memmove(start_to, p, len);
    s->len += len - del;

    return 0;
}
