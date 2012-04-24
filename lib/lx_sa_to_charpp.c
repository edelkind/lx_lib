#include <stdlib.h>
#include "lx_string.h"

/** return a newly allocated array that points 
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
