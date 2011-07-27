#include "lx_string.h"

#if DMALLOC
# include "/usr/local/include/dmalloc.h"
#else
#include <stdlib.h>
//extern void *malloc();
#endif

/**
 * Processes a new descriptor into a generic descriptor.
 * 
 * NOTE: Do not mix usage of the generic descriptor with normal
 *       descriptors.  You may have problems if you do.
 * 
 * Returns 0 on success.
 */

char lx_gdnew (gd, fd, size)
	register lx_gd *gd;
	int fd;
	register unsigned int size;
{
	gd->fd = fd;
	gd->a = (size) ? size : GD_DEFAULT_SIZE;
	gd->n = 0;
	gd->p = 0;
	gd->buf = malloc(gd->a * sizeof(char));
	if (!gd->buf) return 1;
	return 0;
}
