#include "lx_string.h"
extern char *memmove();

#if 0
	*** lx_strcopy ***
	copies one buffer to another
	returns 0 if successful
#endif

char lx_strcopy (dest, src)
	struct lx_string *dest;
	struct lx_string *src;
{
	if (!(src->s))   /* user error */
		return 255;

	//if ( (!(dest->s)) || (dest->len < src->len) ) {
		if (lx_setalloc(dest, src->len))
			return 1;
	//}

	/* memmove is usually implemented in asm, so go with the faster one */
	memmove (dest->s, src->s, src->len);
	dest->len = src->len;
	return 0;
}
