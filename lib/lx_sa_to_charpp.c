#include <stdlib.h>
#include "lx_string.h"

/** Place a (char**) array in \a dest that points to all elements of \a sa.
 *
 * Sample usage:
 * \code
 *   lx_s tmp = {0};
 *   char *pp;
 *   lx_sa_to_charpp(sa, &tmp);
 *   pp = (char **)tmp.s;
 *   execvp(pp[0], pp);
 *   *errno_save = errno;
 *   lx_free(&tmp);
 *   return -1
 * \endcode
 *
 * \note The object data is not copied; Do not use after freeing \a sa.
 *
 * \retval 0 success
 * \retval 1 ENOMEM
 */
char
lx_sa_to_charpp(lx_sa *sa, lx_s *dest)
{
    int i, elem;
    char **pp;

    if (!sa->sarray)
        return 1;
    elem = sa->elem;
    if (lx_setalloc(dest, (elem+1) * sizeof(char *)))
        return 1;

    pp = (char**) dest->s;
    for (i=0; i < elem; i++) {
        pp[i] = sa->sarray[i].s;
    }
    pp[elem] = 0;

    return 0;
}
