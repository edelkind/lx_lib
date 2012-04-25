#include "lx_string.h"

#include <string.h>

/**
 * Copies one buffer to another.
 *
 * Returns 0 if successful.
 */

char lx_strcopy (dest, src)
	struct lx_string *dest;
	const struct lx_string *src;
{
	if (lx_setalloc(dest, src->len))
		return 1;

	/* memmove is usually implemented in asm, so go with the faster one */
	memmove (dest->s, src->s, src->len);
	dest->len = src->len;
	return 0;
}


/**
 * Copies the first l bytes of one buffer to another.
 *
 * Returns 0 on success.
 */

char lx_strncopy (dest, src, l)
	lx_s *dest;
        const lx_s *src;
	unsigned int l;
{
	lx_s xsrc; /* mirrored */
	lx_mirror (&xsrc, src);

	if (xsrc.len > l)
		xsrc.len = l;

	return (lx_strcopy (dest, &xsrc));
}
