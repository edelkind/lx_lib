#include "lx_string.h"

/**
 * Reverse the contents of a string struct.
 *
 * Note that the string struct must already have value.
 */

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
