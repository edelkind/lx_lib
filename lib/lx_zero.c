#include "lx_string.h"

extern void *memset();

void lx_zero (s)
	lx_s *s;
{
	memset (s->s, 0, s->len);
}

void lx_zeroa (s)
	lx_s *s;
{
	memset (s->s, 0, s->alloc);
}
