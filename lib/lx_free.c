#include "lx_string.h"
extern void free ();

#if 0
	***lx_free***
	frees string structure, and sets string back to 0
	returns nothing.
#endif

void lx_free (s)
	lx_s *s;
{
	//printf ("DEBUG: lx_free() called, for pointer %p\n", str->s);
	if (!(s->s))
		return;

	free (s->s);
	s->s = 0;
}

#if 0
	*** lx_zfree ***
	frees string structure using lx_free, but zeroes structure first
	returns nothing.
#endif

void lx_zfree (s)
	lx_s *s;
{
	register unsigned int i;
	register char *p = s->s;

	if (!p)
		return;

	i = s->len;
	for (;;) {
		if (!i--) break; *p++ = 0;
		if (!i--) break; *p++ = 0;
		if (!i--) break; *p++ = 0;
	}

	lx_free (s);
}
