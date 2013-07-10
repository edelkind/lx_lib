#include "lx_string.h"

#include <string.h>
//extern void *memmove();

/**
 * Add a string buffer element to an array of string buffers.
 *
 * Returns 0 on success.
 */
char lx_sa_add (lx_sa *sa, const lx_s *s)
{
	if (!(sa->sarray)) {
		if (lx_sa_alloc (sa, 1))
			return 1;
	} else {
		if (lx_sa_setalloc (sa, sa->elem+1))
			return 1;
	}

        if ( !(sa->sarray[sa->elem] = sa->_new()) )
            return 1;

	//lx_alloc(sa->sarray[sa->elem-1], s->len);
	if (lx_strcopy(sa->sarray[sa->elem], s))
            return 1;
	//memmove(&(sa->sarray[sa->elem-1]), s);

	sa->elem++;
	return 0;
}

char lx_sa_addsa (lx_sa *dest, const lx_sa *src)
{
    int i;

    for (i = 0; i < src->elem; i++) {
        if (lx_sa_add(dest, src->sarray[i]))
            return 1;
    }

    return 0;
}
