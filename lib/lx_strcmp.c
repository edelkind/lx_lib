#include "lx_string.h"

#if 0
	*** lx_strcmp ***
	compares two lx_string strings
	returns 0 on match, 1 on no match
#endif

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


#if 0
	*** lx_strscmp ***
	compares two lx_string strings
	returns 0 on match, 1 on no match
#endif

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
