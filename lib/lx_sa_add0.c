#include "lx_string.h"

/** add a 0-termination after the last recorded element.
 */
char
lx_sa_post0(lx_sa *sa)
{
    if (lx_sa_plusalloc(sa, 1))
        return 1;
    sa->sarray[sa->elem] = 0;
    return 0;
}

/** add a 0-termination to each element (but do not add a 0-termination
 * element)
 */
char
lx_sa_each_post0(lx_sa *sa)
{
    int i, elem;

    if (!sa->sarray)
        return 1;

    elem = sa->elem;
    for (i = 0; i < elem; i++) {
        if (lx_post0(sa->sarray[i]))
            return 1;
    }

    return 0;
}

/** add a 0-termination to each element, and add a 0-termination element.
 * returns a pointer to the sarray, cast as (char **) -- it can now be used as
 * such.
 */
const char **
lx_sa_each_post0_charpp(lx_sa *sa)
{
    if (    lx_sa_each_post0(sa) ||
            lx_sa_post0(sa))
        return (void*)0;

    return (const char**)sa->sarray;
}

/** Like \ref lx_sa_post0(), but also increments \a elem, meaning that it's
 * counted as an actual array.
 */
char
lx_sa_add0(lx_sa *sa)
{
    if (lx_sa_post0(sa))
        return 1;
    sa->elem++;
    return 0;
}

