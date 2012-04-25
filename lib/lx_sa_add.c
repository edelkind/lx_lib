#include "lx_string.h"

#include <string.h>
//extern void *memmove();

/**
 * Add a string buffer element to an array of string buffers.
 *
 * Returns 0 on success.
 */
char lx_sa_add (sa, s)
	lx_sa *sa;
	const lx_s *s;
{
	if (!(sa->sarray)) {
		if (lx_sa_alloc (sa, 1))
			return 1;
	} else {
		if (lx_sa_setalloc (sa, sa->elem+1))
			return 1;
	}

	sa->sarray[sa->elem].s = 0;
	//lx_alloc(sa->sarray[sa->elem-1], s->len);
	if (lx_strcopy(&sa->sarray[sa->elem], s))
            return 1;
	//memmove(&(sa->sarray[sa->elem-1]), s);

	sa->elem++;
	return 0;
}
