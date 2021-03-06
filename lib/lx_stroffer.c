#include "lx_string.h"
#include <string.h>
//extern void *memmove();
#if DMALLOC
# include "/usr/local/include/dmalloc.h"
#else
#include <stdlib.h>
//extern void *malloc();
#endif

/**
 * Offers a string buffer as a pointer.
 *
 * Returns a pointer to a newly allocated C string, or 0 on error
 * (out-of-memory or unallocated-string-buffer).
 */
void *lx_stroffer (s)
	const lx_s *s;
{
	char *sp;

	if (!s->s)
		return 0;
	
	if (!(sp = malloc ((s->len+1) * sizeof(char))))
		return 0;

	memmove (sp, s->s, s->len);
	*(sp + s->len) = 0;

	return ((void *)sp);
}
