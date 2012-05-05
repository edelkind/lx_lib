#include "lx_string.h"


/**
 * Adds every element from \a src to \a sa.  Uses \ref lx_sa_adds0(), so that
 * each will be null-terminated.
 *
 * \sa lx_sa_adds0()
 */
char
lx_sa_addpp (lx_sa *sa, const char *const *src)
{
    const char *p;

    for (; (p = *src); src++) {
        if (lx_sa_adds0(sa, p))
            return 1;
    }

    return 0;
}

char
lx_sa_addppn(lx_sa *sa, const char *const *src, int n)
{
    int i;
    for (i=0; i < n; i++, src++) {
        if (lx_sa_adds0(sa, *src))
            return 1;
    }

    return 0;
}
