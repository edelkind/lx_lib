#include "lx_string.h"
extern void *memmove();

/**
 * Set s_dest to the contents of a given C string.
 *
 * src is copied into s_dest.
 *
 * Returns 0 on success, 1 on ENOMEM.
 */

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

/**
 * Set a s_dest to at most n chars of a given C string.
 *
 * The relevant contents of src are copied into s_dest.
 *
 * Returns 0 on success, 1 on ENOMEM.
 */

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

/**
 * Set a string buffer (s_dest) to exactly n chars of a given C string (src).
 *
 * If src is shorter than n, you will have problems; use lx_strnset()
 * instead.
 *
 * Returns 0 on success.
 */

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

