#include "lx_string.h"
extern void *memmove();
extern void *malloc();

#if 0
	*** lx_strfw ***
	move the string forward n bytes.  The place in memory is not
	modified, nor is the allocation.

	if p != 0, a pointer to the removed portion will be kept.

	returns 0 on success.
#endif

char lx_strfw (s, p, n)
	lx_s *s;
	char **p;
	unsigned int n;
{
	if (s->len < n) n = s->len;

	if (p) {
		if (!(*p = malloc(n + 1))) return 1;
		memcpy (*p, s->s, n);
		*(*p + n) = 0;
	}

	s->len -= n;
	memmove (s->s, s->s + n, s->len);
	return 0;
}
