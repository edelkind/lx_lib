#include "lx_string.h"

extern void *memcpy();

#if 0
	*** lx_gdstrput ***
	add a string to the end of a generic descriptor
	flush if necessary
	returns 0 on success
#endif

char lx_gdstrput (gd, ss1)
	lx_gd *gd;
	const lx_s  *ss1;
{
	register unsigned int left;
	lx_s ss2; /* no need for initialization with a mirror */
	lx_mirror (&ss2, ss1);

	for (;;) {
		left = gd->a - gd->n;

		if (!left) {
			left = lx_gdflush(gd); /* temp use of left */
			if (left) return (left);
			left = gd->a; /* gd->n == 0 */
		}

		if (left >= ss2.len) {
			LX_gdaddstr (gd, ss2.s, ss2.len);
			return 0;
		} else {
			LX_gdaddstr (gd, ss2.s, left);
			ss2.s += left;
			ss2.len -= left;
			ss2.alloc -= left;
		}
	}
}
