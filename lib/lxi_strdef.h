/** @file */

#include "lxi_strbuf.h"

/** \todo make this file more useful */

#define lx_isempty(strbuf) (!((strbuf).s)) /**< test if lx_s is uninitialized */

#define lx_addnl(strbuf) lx_cadd(strbuf, '\n') /**< add a newline */

/** Allocate a new lx_s that will be destroyed automatically upon scope exit */
#define auto_lx_s(s) lx_s (s) __attribute__((cleanup(lx_free)))
/** Allocate a new lx_sa that will be destroyed automatically upon scope exit */
#define auto_lx_sa(sa) lx_sa (sa) __attribute__((cleanup(lx_sa_free)))

#if 0
static inline int
lx_sa_new_elem(lx_sa *sa, lx_s **itemp)
{
    lx_s *item = *itemp;

    if (item) {
        if (item->s)
            lx_free(item)
    } else {
        item = sa->_new();
        if (!item)
            return 1;
        *itemp = item;
    }

    return 0;
}
#endif
