#include "lx_string.h"

#if 0
	*** lx_strcatb ***
	concatenate two strings, each of specified respective lengths
	inner function -- made to be called by lx_strcat
	no return value
#endif

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


#if 0
	*** lx_strcat ***
	concatenate two strings, allocating space if necessary
	returns 0 on success
#endif

char lx_strcat (s1, s2)
	struct lx_string *s1;
	struct lx_string *s2;
{
	if (!(s1->s) || !(s2->s))
		return 255;

	/* if there isn't enough space allocated, allocate it */
	if (lx_setalloc(s1, (s1->len + s2->len)) != 0)
		return 1;

	lx_strcatb(s1->s, s2->s, s1->len, s2->len);
	s1->len += s2->len;
	return 0;
}


