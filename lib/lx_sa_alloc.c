#include "lx_string.h"

#include <stdlib.h>
#include <string.h>

/* extra allocation amount over the normal allocation (could allow for
   fewer allocations, hence speed execution) */
static unsigned int extra_sa_buf = 0;


/**
 * Allocate an array of string structs not yet used.
 *
 * Returns 0 on success, 1 on error.
 */

char lx_sa_alloc (sa, elem)
	struct lx_stringarray *sa;
	unsigned int elem;
{
	unsigned int xelem = (elem + extra_sa_buf);
	unsigned int slen  = xelem * sizeof(lx_s);

	if (sa->sarray) /* user error */
		return 255;

	if ((sa->sarray = (lx_s *)malloc(slen)) == 0)
		return 1;
	sa->alloc = xelem;
	sa->elem = 0;
	return 0;
}


/**
 * Reallocate a (previously used!) string struct array.
 *
 * If it cannot be allocated, it is left untouched.
 * 
 * NOTES:
 *    Extra_sa_buf is not used here; given values are exact.
 *    Never use realloc if the string is not already allocated.
 *    \deprecated This function may be renamed to lxi_sa_realloc in the future;
 *      avoid using it in programs.
 * 
 * Returns 0 on success, 1 on error.
 */

char lx_sa_realloc (sa, elem)
	struct lx_stringarray *sa;
	unsigned int elem;
{
	unsigned int slen  = elem * sizeof(lx_s);
	void *sa_alloc;

	if (!(sa_alloc = realloc (sa->sarray, slen))) return 1;
	sa->sarray = sa_alloc;  /* they may differ */
	sa->alloc = elem;

	if (sa->elem > elem) /* user error? do it anyway (memory leak) */
		sa->elem = elem;

	return 0;
}


/**
 * Allocate an array of string structs, used or not.
 *
 * Returns 0 on success, 1 on error.
 */

char lx_sa_setalloc (sa, elem)
	struct lx_stringarray *sa;
	unsigned int elem;
{
//	struct lx_stringarray newalloc = {0};

	if (!(sa->sarray))
		return (lx_sa_alloc (sa, elem));

	if (sa->alloc >= elem)
		return 0;

	if (lx_sa_realloc (sa, elem))
		return 1;

	/*
	if (lx_sa_alloc(&newalloc, elem))
		return 1;

	memmove(newalloc.sarray, sa->sarray, (sa->elem*sizeof(lx_s)));
	free (sa->sarray);
	sa->sarray = newalloc.sarray;
	sa->alloc = newalloc.alloc;
	*/
	return 0;
}


/**
 * Add elem elements to allocated sa.
 *
 * Returns 0 on success, 1 on error.
 */

char
lx_sa_plusalloc(lx_sa *sa, unsigned int elem)
{
	if (!(sa->sarray)) return (lx_sa_alloc (sa, elem));
	else return (lx_sa_setalloc (sa, sa->elem+elem));
}


/**
 * Sets the extra buffer array amount for allocations.
 *
 * Any time new space actually needs to be allocated, allocate this
 * extra amount, allowing for potentially fewer allocations and hence
 * faster program execution.
 *
 * Returns the old extra buffer array amount.
 */

unsigned int lx_sa_setxbuf (x)
	unsigned int x;
{
	unsigned int obuf = extra_sa_buf;

	extra_sa_buf = x;
	return (obuf);
}
