#include <errno.h>
#include "lx_string.h"

extern int write ();

#if 0
	*** lx_gdflush ***
	flush generic descriptor output
	returns 0 on success
#endif

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
