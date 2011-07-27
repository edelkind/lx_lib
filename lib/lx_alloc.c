#include "lx_string.h"
#if DMALLOC
# include "/usr/local/include/dmalloc.h"
#else
# include <stdlib.h>
#endif

#include <string.h>

/** \internal
 * extra allocation amount over the normal allocation (could allow for
 * fewer allocations, hence speed execution)
 */
static unsigned int extra_buf = 0;


/**
 * Allocate a string struct not yet used.
 *
 * Returns 0 on success, 1 on error.
 */

char lx_alloc (s, elem)
	lx_s *s;
	unsigned int elem;
{
	unsigned int xelem = (elem + extra_buf);
	unsigned int slen  = xelem * sizeof(char);

	//printf ("DEBUG: lx_alloc() called for pointer %p\n", s->s);

	if ((s->s = malloc(slen)) == 0)
		return 1;
	s->alloc = xelem;
	s->len = 0;
	//printf ("DEBUG: lx_alloc(): pointer now %p\n", s->s);
	return 0;
}


/**
 * Reallocate a string struct to hold a different amount.
 *
 * if the memory cannot be allocated, str is untouched.
 * 
 * NOTES: 
 *    - extra_buf is not used here; given values are exact.
 *    - never use realloc if the string is not already allocated.
 * \deprecated
 *    this function may be renamed to lxi_realloc in the future;
 *    avoid using it in programs.
 * 
 * Returns 0 on success, 1 on error.
 */

char lx_realloc (str, elem)
	struct lx_string *str;
	unsigned int elem;
{
	char *salloc;
	unsigned int slen = elem * sizeof(char);

	//printf ("DEBUG: lx_realloc() called for pointer %p\n", str->s);
	if (!(salloc = realloc (str->s, slen))) return 1;
	str->s = salloc;  /* they may differ */
	str->alloc = elem;

	if (str->len > elem) /* user error? do it anyway */
		str->len = elem;

	//printf ("DEBUG: lx_realloc(): pointer is now %p\n", str->s);
	return 0;
}


/**
 * Allocate a string struct, used or not.
 *
 * Returns 0 on success, 1 on error.
 */

char lx_setalloc (str, elem)
	struct lx_string *str;
	unsigned int elem;
{
//	struct lx_string newalloc = {0};

	if (!(str->s)) {
		return (lx_alloc (str, elem));
	}

	if (str->alloc >= elem)
		return 0;

	if (lx_realloc (str, elem))
		return 1;

	/*
	if (lx_alloc(&newalloc, elem))
		return 1;

	memmove(newalloc.s, str->s, str->len);
	free (str->s);
	str->s = newalloc.s;
	str->alloc = newalloc.alloc;
	*/
	return 0;
}


/**
 * Add elem bytes to allocated s.
 *
 * Returns 0 on success, 1 on error
 */

char lx_plusalloc (s, elem)
	lx_s *s;
	unsigned int elem;
{
	if (!s->s) return (lx_alloc(s, elem));
	else return (lx_setalloc(s, s->len+elem));
}


/**
 * Sets the extra buffer amount for allocations.
 *
 * Any time new space actually needs to be allocated, allocate this
 * extra amount, allowing for potentially fewer allocations and hence
 * faster program execution.
 *
 * Returns the old extra buffer amount.
 */

unsigned int lx_setxbuf (x)
	unsigned int x;
{
	unsigned int obuf = extra_buf;

	extra_buf = x;
	return (obuf);
}
