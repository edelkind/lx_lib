#include "lx_string.h"
extern void *memset ();

#if 0
	*** lx_strnull ***
	free and nullify a string
	returns nothing
#endif

void lx_strnull(s)
	lx_s *s;
{
	if (s->s) lx_free (s);
	memset (s, 0, sizeof(lx_s));
}

#if 0
	*** lx_strznull ***
	zfree and nullify a string
	returns nothing
#endif

void lx_strznull(s)
	lx_s *s;
{
	if (s->s) lx_zfree(s);
	memset (s, 0, sizeof(lx_s));
}
