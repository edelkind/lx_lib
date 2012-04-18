#include "lx_string.h"

#include <unistd.h>
#include <errno.h>
//extern int read();

/**
 * Fills up a generic descriptor.  If read() returns with EINTR, the read is retried.
 *
 * Returns 0 on success.
 */

char lx_gdfill (gd)
	lx_gd *gd;
{
	register int i;

	i = gd->n;

RETRY:
	if ((i = read(gd->fd, gd->buf+i, gd->a-i)) == -1) {
            if (errno == EINTR)
                goto RETRY;
            return 1;
        }

	gd->n += i;

	return 0;
}
