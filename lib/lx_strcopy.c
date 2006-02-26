#include "lx_string.h"

#include <string.h>

#if 0
	*** lx_strcopy ***
	copies one buffer to another
	returns 0 if successful
#endif

char lx_strcopy (dest, src)
	struct lx_string *dest;
	struct lx_string *src;
{
	if (lx_setalloc(dest, src->len))
		return 1;

	/* memmove is usually implemented in asm, so go with the faster one */
	memmove (dest->s, src->s, src->len);
	dest->len = src->len;
	return 0;
}


#if 0
	copies the first l bytes of one buffer to another
	returns 0 on success
#endif

char lx_strncopy (dest, src, l)
	lx_s *dest, *src;
	unsigned int l;
{
	lx_s xsrc; /* mirrored */
	lx_mirror (&xsrc, src);

	if (xsrc.len > l)
		xsrc.len = l;

	return (lx_strcopy (dest, &xsrc));
}
