#include "lx_string.h"

/**
 * Find the index of a specified character.
 *
 * n should be a positive integer, referring to which occurrence
 * the function should find (i.e. 1 for first, 2 for second, etc).
 *
 * Returns the index, or -1 if there was none.
 */

long lx_strindex (s, c, n)
	lx_s *s;
	char c;
	unsigned int n;
{
	unsigned int l = s->len;
	register char *p = s->s;

	for (;;) {
		if (!l--) return -1; if (*p == c) { if (!--n) break; } p++;
		if (!l--) return -1; if (*p == c) { if (!--n) break; } p++;
		if (!l--) return -1; if (*p == c) { if (!--n) break; } p++;
	}

	return ((char *)p - s->s);
}


/**
 * Find the index of one of a set of specified characters.
 *
 * n should be a positive integer, referring to which occurrence
 * the function should find (i.e. 1 for first, 2 for second, etc).
 *
 * Returns the index, or -1 if there was none.
 */

long lx_strsindex (s, set, setl, n)
	lx_s *s;
	const char *set;
	unsigned int setl, n;
{
	unsigned int sl, l = s->len;
	register char *p = s->s;
	register const char *x;
	char c;

	for (;; p++, l--) {
	    if (!l) return -1;
	    x = set;
	    sl = setl;
	    c = *p;

	    for (;;) {
		if (!sl--) break; if (*x == c) { if (!--n) goto out; } x++;
		if (!sl--) break; if (*x == c) { if (!--n) goto out; } x++;
	    }
	}

out:
	return ((char *)p - s->s);
}

