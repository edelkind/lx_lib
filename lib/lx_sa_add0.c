#include "lx_string.h"

/** add a 0-termination element after the last recorded element.
 */
char
lx_sa_post0(lx_sa *sa)
{
    if (lx_sa_plusalloc(sa, 1))
        return 1;
    sa->sarray[sa->elem].s = 0;
    return 0;
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

