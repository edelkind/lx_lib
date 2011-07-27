#include "lx_string.h"

extern void *memset();

/**
 * Sets the used contents of s to zero.
 */
void lx_zero (s)
	lx_s *s;
{
	memset (s->s, 0, s->len);
}

/**
 * Sets the allocated contents of s to zero.
 */
void lx_zeroa (s)
	lx_s *s;
{
	memset (s->s, 0, s->alloc);
}
