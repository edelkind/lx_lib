#include "lx_string.h"

extern void *memmove();

#if 0
	add a string buffer element to an array of string buffers
	returns 0 on success
#endif

char lx_sa_add (sa, s)
	lx_sa *sa;
	lx_s *s;
{
	if (!(sa->sarray)) {
		if (lx_sa_alloc (sa, 1))
			return 1;
	} else {
		if (lx_sa_setalloc (sa, sa->elem+1))
			return 1;
	}

	sa->elem++;

	sa->sarray[sa->elem-1].s = 0;
	//lx_alloc(sa->sarray[sa->elem-1], s->len);
	lx_strcopy(&sa->sarray[sa->elem-1], s);
	//memmove(&(sa->sarray[sa->elem-1]), s);
	return 0;
}
