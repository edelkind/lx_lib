#include "lx_string.h"

/**
 * Make l bytes of s lowercase (if applicable).
 *
 * Returns nothing.
 */

void lx_lowers (s, l)
	char *s;
	unsigned int l;
{
	char c;
	while (l--) {
		c = *s;
		if (c >= 'A' && c <= 'Z')
                    *s = c + ('a' - 'A');
                s++;
	}
}


/**
 * Make l bytes of s uppercase (if applicable).
 *
 * Returns nothing.
 */

void lx_uppers (s, l)
	char *s;
	unsigned int l;
{
	char c;
	while (l--) {
		c = *s;
		if (c >= 'a' && c <= 'z')
                    *s = c + ('A' - 'a');
                s++;
	}
}


/**
 * Store l lowercase bytes of s into p.
 *
 * Note that p _must_ have at least l bytes allocated to avoid overflow.
 *
 * Returns nothing.
 */

void lx_lowersp (p, s, l)
	char *p;
        const char *s;
	unsigned int l;
{
	char c;
	while (l--) {
		c = *s++;
		if (c >= 'A' && c <= 'Z')
			c += 'a' - 'A';

		*p++ = c;
	}
}


/**
 * Store l uppercase bytes of s into p.
 *
 * Note that p _must_ have at least l bytes allocated to avoid overflow.
 *
 * Returns nothing.
 */

void lx_uppersp (p, s, l)
	char *p;
        const char *s;
	unsigned int l;
{
	char c;
	while (l--) {
		c = *s++;
		if (c >= 'a' && c <= 'z')
			c += 'A' - 'a';

		*p++ = c;
	}
}


/**
 * Store l lowercase bytes of s into ss.
 *
 * Str may be dynamically allocated.
 *
 * Returns zero on success, 1 otherwise.
 */

char lx_lowerstr (ss, s, l)
	lx_s *ss;
	const char *s;
	unsigned int l;
{
	if (lx_setalloc (ss, l))
		return 1;

	lx_lowersp (ss->s, s, l);
	return 0;
}


/**
 * Store l uppercase bytes of s into ss.
 *
 * Str may be dynamically allocated.
 *
 * Returns zero on success, 1 otherwise.
 */

char lx_upperstr (ss, s, l)
	lx_s *ss;
	const char *s;
	unsigned int l;
{
	if (lx_setalloc (ss, l))
		return 1;

	lx_uppersp (ss->s, s, l);
	return 0;
}

