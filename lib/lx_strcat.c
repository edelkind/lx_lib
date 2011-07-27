#include "lx_string.h"

/**
 * Concatenate two strings, each of specified respective lengths....
 *
 * Inner function -- made to be called by lx_strcat().
 *
 * \deprecated May be renamed in the future.
 */

void lx_strcatb (s1, s2, len1, len2)
	register char *s1;
	register char *s2;
	unsigned int len1;
	register unsigned int len2;
{
	s1 += len1;

	for (;;) {
		if (!len2--) return; *s1++ = *s2++;
		if (!len2--) return; *s1++ = *s2++;
		if (!len2--) return; *s1++ = *s2++;
	}

}


/**
	Concatenate two strings, allocating space if necessary.

	Returns 0 on success.
 */

char lx_strcat (s1, s2)
	struct lx_string *s1;
	struct lx_string *s2;
{
	/* if there isn't enough space allocated, allocate it */
	if (lx_setalloc(s1, (s1->len + s2->len)) != 0)
		return 1;

	lx_strcatb(s1->s, s2->s, s1->len, s2->len);
	s1->len += s2->len;
	return 0;
}


