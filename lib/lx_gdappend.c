#include "lx_string.h"

#include <string.h>


#if 0
	*** lx_gdiappend ***
	appends the specified amount from a generic descriptor to a string
	buffer.
	if the specified amount does not exist in the generic descriptor,
	you will have problems.

	returns 0 on success.
#endif

char lx_gdiappend (s, gd, amount)
	lx_s *s;
	lx_gd *gd;
	unsigned int amount;
{
	if (lx_plusalloc(s, amount))
		return 1;

	memcpy(s->s+s->len, gd->buf, amount);
	s->len += amount;
	return 0;
}
