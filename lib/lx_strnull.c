#include "lx_string.h"

#include <string.h>
//extern void *memset ();

/**
 * lx_free() and nullify the structure of s.
 */
void lx_strnull(s)
	lx_s *s;
{
	if (s->s) lx_free (s);
	memset (s, 0, sizeof(lx_s));
}

/**
 * lx_zfree() and nullify the structure of s.
 */
void lx_strznull(s)
	lx_s *s;
{
	if (s->s) lx_zfree(s);
	memset (s, 0, sizeof(lx_s));
}
