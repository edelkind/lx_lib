#include "lx_string.h"

#include <string.h>


/**
 * Add a C string to an array of string buffers.
 *
 * Note that the source string is copied.
 *
 * Returns 0 on success.
 */
char lx_sa_adds (sa, src)
	lx_sa *sa;
	char *src;
{
	lx_s tmp = {0};

	if (lx_strset (&tmp, src)) return 1;

	return (lx_sa_add (sa, &tmp));
}

/** Like \ref lx_sa_adds(), but adds a terminating 0.
 *
 * \sa lx_sa_adds()
 * \sa lx_post0()
 */
char
lx_sa_adds0 (lx_sa *sa, char *src)
{
	lx_s tmp = {0};

	if (    lx_strset (&tmp, src) ||
	        lx_sa_add (sa, &tmp) ||
                lx_post0(&sa->sarray[sa->elem-1]) )
            return 1;

        return 0;
}
