#include "lx_string.h"

#if 0
	*** lx_check0 ***
	Ensure that s ends in a binary 0.  If not, add one.
	returns 0 on success.
#endif

char lx_check0 (s)
	lx_s *s;
{
	if (s->s[s->len-1]) return (lx_cadd(s, 0));
	return 0;
}
