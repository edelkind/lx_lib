#include "lx_string.h"

#include <string.h>

/**
 * Pop an element off the back of the string array.
 *
 * \returns 0 on success, or 1 on range error.
 *
 * \sa lx_sa_pop_index()
 */
char
lx_sa_pop_back (lx_sa *sa, lx_s **destp)
{
#if 0
    if (!(sa->sarray) || !sa->elem)
        return 1;

    if (destp) {
        if (destp->s)
            lx_free(destp);

        *destp = sa->sarray[sa->elem-1];
    } else {
        lx_free(&sa->sarray[sa->elem-1]);
    }

    sa->elem--;

    return 0;
#endif
    return lx_sa_pop_index(sa, destp, -1);
}

/**
 * Pop an element from a specified index.  The index may be negative, in which
 * case it is taken as an offset from the end of the array.
 *
 * If \a destp is not null, it will be set to be a pointer to the popped
 * element.  These contents (including the lx_s structure itself) will no
 * longer be tracked by the string array, so they must be freed by the caller
 * when no longer required (e.g. by lx_destroy()).
 *
 * If \a destp is null, the element will be destroyed with \a sa->_delete().
 *
 * \returns 0 on success, or 1 on range error.
 */
char
lx_sa_pop_index (lx_sa *sa, lx_s **destp, int index)
{
    if (index < 0)
        index = sa->elem + index;

    if (!(sa->sarray) || index < 0 || sa->elem <= index)
        return 1;

    if (destp) {
        *destp = sa->sarray[index];
        sa->sarray[index] = 0;
    } else {
        sa->_delete(sa->sarray[index]);
    }

    sa->elem--;

    if (index < sa->elem)
        memmove(sa->sarray + index, sa->sarray + index + 1, (sa->elem - index)*sizeof(sa->sarray[0]));

    return 0;
}

/**
 * Pop an element off the front of the string array.
 *
 * \returns 0 on success, or 1 on range error.
 *
 * \sa lx_sa_pop_index()
 */
char
lx_sa_pop_front(lx_sa *sa, lx_s **destp)
{
    return lx_sa_pop_index(sa, destp, 0);
}
