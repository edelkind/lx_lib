#include "lx_string.h"
extern void *memmove();

#if 0
	*** lx_strset ***
	set a string buffer to a given string
	returns 0 on success.
#endif

char lx_strset (s_dest, src)
	struct lx_string *s_dest;
	char *src;
{
	struct lx_string s_src = {0};

	s_src.s = src;
	s_src.len = lx_strlen(src);
	s_src.alloc = s_src.len;

	return (lx_strcopy (s_dest, &s_src));
}

#if 0
	*** lx_strnset ***
	set a string buffer to at most n chars of a given string
	returns 0 on success.
#endif

char lx_strnset (s_dest, src, n)
	lx_s *s_dest;
	register char *src;
	register unsigned int n;
{
	register int len = 0;
	lx_s s_src = {0};

	s_src.s = src;
	for (;;) {
		if (!(*src) || !n)
			break;
		++len; ++src; --n;
	}
	s_src.len = s_src.alloc = len;

	return (lx_strcopy (s_dest, &s_src));
}

#if 0
	*** lx_striset ***
	set a string buffer (s_dest) to exactly n chars of a given string (src)
	if src is shorter than n, you will have problems; use lx_strnset
	instead.
	returns 0 on success.
#endif

char lx_striset (s_dest, src, n)
	struct lx_string *s_dest;
	char *src;
	unsigned int n;
{
	if (lx_setalloc (s_dest, n))
		return 1;

	s_dest->len = n;
	memmove (s_dest->s, src, n);
	return (0);
}

