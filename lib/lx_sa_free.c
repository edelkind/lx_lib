#include <stdlib.h>

#include "lx_string.h"

void
lx_sa_free(lx_sa *sa)
{
    int elem;

    if (!sa->sarray) return;

    for (elem = sa->elem; elem;)
        lx_free(&sa->sarray[--elem]);

    free(sa->sarray);
    sa->sarray = 0;
}

void
lx_sa_zfree(lx_sa *sa)
{
    int elem;

    if (!sa->sarray) return;

    for (elem = sa->elem; elem;)
        lx_zfree(&sa->sarray[--elem]);

    free(sa->sarray);
    sa->sarray = 0;
}
