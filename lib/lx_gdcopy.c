#include "lx_string.h"

extern void *memcpy ();


#if 0
	*** lx_gdicopy ***
	copies the specified amount from a generic descriptor into a string
	buffer.
	if the specified amount does not exist in the generic descriptor,
	you will have problems.
	if the string buffer is not empty, it will be overwritten.

	returns 0 on success.
#endif

char lx_gdicopy (s, gd, amount)
	lx_s *s;
	lx_gd *gd;
	unsigned int amount;
{
	if (lx_setalloc(s, amount))
		return 1;

	memcpy(s->s, gd->buf, amount);
	s->len = amount;
	return 0;
}
