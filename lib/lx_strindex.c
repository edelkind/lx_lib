#include "lx_string.h"

#if 0
	*** lx_strindex ***
	find the index of a specified character
	n should be a positive integer, referring to which occurrence
	the function should find (i.e. 1 for first, 2 for second, etc)
	returns the index, or -1 if there was none.
#endif

long lx_strindex (s, c, n)
	lx_s *s;
	char c;
	unsigned int n;
{
	unsigned int l = s->len;
	register unsigned char *p = s->s;

	for (;;) {
		if (!l--) return -1; if (*p == c) { if (!--n) break; } p++;
		if (!l--) return -1; if (*p == c) { if (!--n) break; } p++;
		if (!l--) return -1; if (*p == c) { if (!--n) break; } p++;
	}

	return ((char *)p - s->s);
}


#if 0
	*** lx_strsindex ***
	find the index of one of a set of specified characters
	n should be a positive integer, referring to which occurrence
	the function should find (i.e. 1 for first, 2 for second, etc)
	returns the index, or -1 if there was none.
#endif

long lx_strsindex (s, set, setl, n)
	lx_s *s;
	char *set;
	unsigned int setl, n;
{
	unsigned int sl, l = s->len;
	register unsigned char *p = s->s;
	register unsigned char *x;
	unsigned char c;

	for (;;) {
	    if (!l--) return -1;
	    x = set;
	    sl = setl;
	    c = *p++;

	    for (;;) {
		if (!sl--) break; if (*x == c) { if (!--n) goto out; } x++;
		if (!sl--) break; if (*x == c) { if (!--n) goto out; } x++;
	    }
	}

out:
	return ((char *)p - s->s);
}

