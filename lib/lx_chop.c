#include "lx_string.h"

#include <string.h>

/**
 * Delete the last n characters from a string buffer.
 *
 * Returns 0 on success.
 */

char lx_chop (s, n)
	struct lx_string *s;
	unsigned int n;
{

	if (s->len >= n) { s->len -= n; return 0; }

	return 1;
}

/**
 * Delete all ending characters from a string buffer matching one in cstr.
 *
 * Returns 0 on success.
 */

char lx_chomp (s, cstr)
	lx_s *s;
	char *cstr;
{
	lx_s ns = {0};
	register unsigned int len;
	register unsigned int slen;
	register unsigned int nchop;
	register unsigned int ichop;

	if (!cstr) return 0;

	if (lx_strset (&ns, cstr)) return 1;

	ichop = nchop = 0;
	for (;;) {
		len = ns.len;
		slen = s->len - nchop;

		for (;;) {
			if (!len || !slen) break; --len;
				if (ns.s[len] == s->s[slen-1])
					{--slen; ++nchop;}
		}

		if (ichop == nchop) break;
		ichop = nchop;
	}

	lx_free (&ns);
	s->len -= nchop;
	return 0;
}

/**
 * Removes all whitespace characters from the end of a string buffer.
 *
 * Returns nothing.
 */

void lx_chomp_ws (s)
	lx_s *s;
{

	for (;;) {
		if (!(s->len)) return;
		switch ((s->s)[s->len-1]) {
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				--(s->len); break;
			default:
				return;
		}
	}
}

/**
 * Delete all beginning characters matching one in cstr.
 *
 * Returns 0 on success.
 */

char lx_chompf (s, cstr)
	lx_s *s;
	char *cstr;
{
	lx_s ns = {0};
	register unsigned int len;
	register unsigned int slen;
	register unsigned int nchop;
	register unsigned int ichop;

	if (!cstr) return 0;

	if (lx_strset (&ns, cstr)) return 1;

	ichop = nchop = 0;
	for (;;) {
		slen = s->len - nchop;
		len  = ns.len;

		if (!slen || !len) break;
		for (;;) {
			if (s->s[nchop] == ns.s[--len])
				{ ++nchop; break; }
			if (!len) break;
		}

		if (ichop == nchop) break;
		ichop = nchop;
	}

	lx_free (&ns);

	if (nchop) memmove (s->s, s->s+nchop, slen);
	s->len -= nchop;
	return 0;
}

/**
 * Delete all beginning whitespace characters.
 *
 * Returns 0 on success.
 */

char lx_chompf_ws (s)
	lx_s *s;
{
	return (lx_chompf (s, " \t\r\n"));
}
