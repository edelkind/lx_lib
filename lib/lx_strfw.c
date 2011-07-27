#include "lx_string.h"
#include <string.h>
//extern void *memmove();
#include <stdlib.h>
//extern void *malloc();

/**
 * Move the string forward n bytes.  The place in memory is not
 * modified, nor is the allocation.
 * 
 * If p != 0, a pointer to the removed portion will be kept (allocated with
 * malloc()).
 * 
 * Returns 0 on success, or 1 on ENOMEM.
 */
char lx_strfw (s, p, n)
	lx_s *s;
	char **p;
	unsigned int n;
{
	if (s->len < n) n = s->len;

	if (p) {
		if (!(*p = malloc(n + 1))) return 1;
		memmove (*p, s->s, n);
		*(*p + n) = 0;
	}

	s->len -= n;
	memmove (s->s, s->s + n, s->len);
	return 0;
}
