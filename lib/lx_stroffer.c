#include "lx_string.h"
extern void *memmove();
#if DMALLOC
# include "/usr/local/include/dmalloc.h"
#else
extern void *malloc();
#endif

#if 0
	*** lx_stroffer ***
	offers a string buffer as a pointer.
	returns a pointer to a newly created string, or 0 on error.
#endif

void *lx_stroffer (s)
	lx_s *s;
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
