#include "lx_string.h"

#if 0
	*** lx_strrev ***
	reverse a string struct
	note that the string struct must already have value.
	returns nothing
#endif

void lx_strrev (s)
	lx_s *s;
{
	register unsigned int beg = 0;
	register unsigned int end = s->len;
	register char c;
	char *sp = s->s;

	while (end > beg) {
		c = sp[beg];
		sp[beg] = sp[end-1];
		sp[end-1] = c;
		beg++; end--;
	}
}
