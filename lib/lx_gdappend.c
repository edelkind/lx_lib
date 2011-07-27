#include "lx_string.h"

#include <string.h>


/**
 * Appends the specified amount from a generic descriptor to a string
 * buffer.
 *
 * If the specified amount does not exist in the generic descriptor,
 * you will have problems.
 * 
 * Returns 0 on success.
 */

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
