#include <stdlib.h>

#include "lx_string.h"

void
lx_sa_empty(lx_sa *sa)
{
    int elem;

    if (!sa->sarray) return;

    for (elem = sa->elem; elem;)
        sa->_delete(sa->sarray[--elem]);
    sa->elem = 0;
}

#if 0
void
lx_sa_zempty(lx_sa *sa)
{
    int elem;

    if (!sa->sarray) return;

    for (elem = sa->elem; elem;)
        lx_zfree(&sa->sarray[--elem]);
    sa->elem = 0;
}
#endif
