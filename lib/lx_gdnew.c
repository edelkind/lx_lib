#include "lx_string.h"

#if DMALLOC
# include "/usr/local/include/dmalloc.h"
#else
extern void *malloc();
#endif

#if 0
	*** lx_gdnew ***
	processes a new descriptor into a generic descriptor
	NOTE: Do not mix usage of the generic descriptor with normal
	      descriptors.  You may have problems if you do.
	returns 0 on success
#endif

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
