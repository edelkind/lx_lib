#include "lx_string.h"

/**
 * Compares two lx_string strings.
 *
 * Returns 0 on match, 1 on no match.
 */

char lx_strcmp (s1, s2)
	struct lx_string *s1;
	struct lx_string *s2;
{
	register char *p1;
	register char *p2;
	register int len = s1->len;

	if (len != s2->len)
		return (1);

	p1 = s1->s;
	p2 = s2->s;

	for (;;) {
		if (!len) /* EOS */
			return 0;

		if (*p1++ != *p2++)
			return 1;

		len--;
	}
}


/**
 * Compares an lx_string string and a character pointer.
 *
 * Returns 0 on match, 1 on no match.
 */

char lx_strscmp (s1, s2)
	struct lx_string *s1;
	char *s2;
{
	register char *p1;
	register char *p2;
	register int len = s1->len;

	p1 = s1->s;
	p2 = s2;

	for (;;) {
		if (!len) { /* EOS */
			if (*p2 == 0) return 0;  /* end of p2 */
			else return 1;           /* p2 continues */
		}

		if (!*p2)   /* p1 continues */
			return 1;

		if (*p1++ != *p2++)
			return 1;

		len--;
	}
}


/**
 * Compares two lx_string strings, case insensitively.
 *
 * Returns 0 on match, 1 on no match.
 */

char lx_stricmp (s1, s2)
	struct lx_string *s1;
	struct lx_string *s2;
{
	register char *p1;
	register char *p2;
	register int len = s1->len;

	if (len != s2->len)
		return (1);

	p1 = s1->s;
	p2 = s2->s;

	for (;;) {
		if (!len) /* EOS */
			return 0;

		if (lx_lowerb(*p1++) != lx_lowerb(*p2++))
			return 1;

		len--;
	}
}


/**
 * Compares two lx_string strings, comparing the right one as lowercase.
 *
 * Returns 0 on match, 1 on no match.
 */

char lx_strlcmp (s1, s2)
	struct lx_string *s1;
	struct lx_string *s2;
{
	register char *p1;
	register char *p2;
	register int len = s1->len;

	if (len != s2->len)
		return (1);

	p1 = s1->s;
	p2 = s2->s;

	for (;;) {
		if (!len) /* EOS */
			return 0;

		if (*p1++ != lx_lowerb(*p2++))
			return 1;

		len--;
	}
}


/**
 * Compares two lx_string strings, up to l bytes.
 *
 * Returns 0 on match, 1 on no match.
 */

char lx_strncmp (s1, s2, l)
	lx_s *s1, *s2;
	unsigned int l;
{
	lx_s x1, x2; /* mirrored */
	lx_mirror (&x1, s1);
	lx_mirror (&x2, s2);

	if (x1.len > l) x1.len = l;
	if (x2.len > l) x2.len = l;

	return (lx_strcmp (&x1, &x2));
}


/**
 * Compares two lx_string strings, up to l bytes, case insensitively.
 *
 * Returns 0 on match, 1 on no match.
 */

char lx_strnicmp (s1, s2, l)
	lx_s *s1, *s2;
	unsigned int l;
{
	lx_s x1, x2; /* mirrored */
	lx_mirror (&x1, s1);
	lx_mirror (&x2, s2);

	if (x1.len > l) x1.len = l;
	if (x2.len > l) x2.len = l;

	return (lx_stricmp (&x1, &x2));
}


/**
 * Compares two lx_string strings, up to l bytes, testing the
 * right as lowercase.
 *
 * Returns 0 on match, 1 on no match.
 */

char lx_strnlcmp (s1, s2, l)
	lx_s *s1, *s2;
	unsigned int l;
{
	lx_s x1, x2; /* mirrored */
	lx_mirror (&x1, s1);
	lx_mirror (&x2, s2);

	if (x1.len > l) x1.len = l;
	if (x2.len > l) x2.len = l;

	return (lx_strlcmp (&x1, &x2));
}


/**
 * Compares l bytes of two character pointers.
 *
 * Does not check for embedded binary zeroes -- checks the entire
 * string length, until a difference is found.
 *
 * Returns 0 on match.
 */

char lx_strnpcmp (p1, p2, l)
	register char *p1, *p2;
	unsigned int l;
{
	for (;;) {
		if (!l--) return 0; if (*p1++ != *p2++) break; 
		if (!l--) return 0; if (*p1++ != *p2++) break; 
		if (!l--) return 0; if (*p1++ != *p2++) break; 
	}

	return 1;
}


/**
 * Compares l bytes of two char* pointers, case insensitively.
 *
 * Does not check for embedded binary zeroes -- checks the entire
 * string length, until a difference is found.
 *
 * Returns 0 on match.
 */

char lx_strnipcmp (p1, p2, l)
	register char *p1, *p2;
	unsigned int l;
{
	for (;;) {
		if (!l--) return 0; if (lx_lowerb(*p1++) != lx_lowerb(*p2++)) break; 
		if (!l--) return 0; if (lx_lowerb(*p1++) != lx_lowerb(*p2++)) break; 
		if (!l--) return 0; if (lx_lowerb(*p1++) != lx_lowerb(*p2++)) break; 
	}

	return 1;
}


/**
 * Compares l bytes of two character pointers, testing the
 * right as lowercase.
 *
 * Does not check for embedded binary zeroes -- checks the
 * entire string length, until a difference is found.
 *
 * Returns 0 on match.
 */

char lx_strnlpcmp (p1, p2, l)
	register char *p1, *p2;
	unsigned int l;
{
	for (;;) {
		if (!l--) return 0; if (*p1++ != lx_lowerb(*p2++)) break; 
		if (!l--) return 0; if (*p1++ != lx_lowerb(*p2++)) break; 
		if (!l--) return 0; if (*p1++ != lx_lowerb(*p2++)) break; 
	}

	return 1;
}

