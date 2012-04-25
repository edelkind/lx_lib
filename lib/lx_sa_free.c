#include <stdlib.h>

#include "lx_string.h"

void
lx_sa_free(lx_sa *sa)
{
    if (!sa->sarray) return;
    lx_sa_empty(sa);
    free(sa->sarray);
    sa->sarray = 0;
}

void
lx_sa_zfree(lx_sa *sa)
{
    if (!sa->sarray) return;
    lx_sa_zempty(sa);
    free(sa->sarray);
    sa->sarray = 0;
}
