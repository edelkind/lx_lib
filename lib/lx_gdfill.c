#include "lx_string.h"

extern int read();

#if 0
	*** lx_gdfill ***
	fills up a generic descriptor
	returns 0 on success
#endif

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
