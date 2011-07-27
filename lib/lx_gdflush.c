#include <errno.h>
#include "lx_string.h"

#include <unistd.h>
//extern int write ();

/**
 * Flush generic descriptor output.
 *
 * Returns 0 on success.
 */

char lx_gdflush (gd)
	lx_gd *gd;
{
	register int ret;

	/* AIX can't handle 0-length writes */
	if (!gd->n) return 0;

	for (;;) {
		ret = write (gd->fd, gd->buf+gd->p, gd->n);

		if (ret == gd->n) { LX_gdrw(gd); return 0; }

		if (ret == -1) {
			if (errno == EINTR) continue;
			return 1;
		}

		LX_gdff(gd, ret);
	}
}
