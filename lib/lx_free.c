#include "lx_string.h"
extern void free ();

/**
 * Frees string structure, and sets string back to 0.
 *
 * Returns nothing.
 */

void lx_free (s)
	lx_s *s;
{
	//printf ("DEBUG: lx_free() called, for pointer %p\n", str->s);
	if (!(s->s))
		return;

	free (s->s);
	s->s = 0;
}

/**
 * Frees string structure using lx_free, but zeroes structure first.
 *
 * Returns nothing.
 */

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
