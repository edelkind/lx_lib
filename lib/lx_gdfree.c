#include "lx_string.h"

#include <unistd.h>
//extern int close();
#if DMALLOC
# include "/usr/local/include/dmalloc.h"
#else
#include <stdlib.h>
//extern void *malloc();
//extern void free();
#endif

/**
 * Frees a generic descriptor.
 *
 * Any current bufferage will be lost.
 *
 * gd _must_ have been previously set with lx_gdnew().
 *
 * Returns 0 on success, 1 on close error.
 * If close returns an error, the gd will still be freed, but gd->fd
 *   will still point to the problematic fd.
 */

char lx_gdfree (gd)
	register lx_gd *gd;
{
    if (!gd->buf)
        return 0;

    gd->a = 0;
    gd->n = 0;
    gd->p = 0;
    free (gd->buf);
    gd->buf = 0;
    if (close(gd->fd)) return 1;
    gd->fd = -1; return 0;
}
