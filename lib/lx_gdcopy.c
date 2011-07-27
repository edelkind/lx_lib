#include "lx_string.h"

#include <string.h>
//extern void *memcpy ();


/**
 * Copies the specified amount from a generic descriptor into a string
 * buffer.
 *
 * If the specified amount does not exist in the generic descriptor,
 * you will have problems.
 *
 * If the string buffer is not empty, it will be overwritten.
 * 
 * Returns 0 on success.
 */

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
