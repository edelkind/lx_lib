#include "lx_string.h"

#include <unistd.h>
//extern int read();

/**
 * Fills up a generic descriptor.
 *
 * Returns 0 on success.
 */

char lx_gdfill (gd)
	lx_gd *gd;
{
	register int i;

	i = gd->n;

	if ((i = read(gd->fd, gd->buf+i, gd->a-i)) == -1)
		return 1;

	gd->n += i;

	return 0;
}
