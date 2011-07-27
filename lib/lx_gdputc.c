#include "lx_string.h"
#include <string.h>


/**
 * Outputs a character to a generic descriptor.
 *
 * NOTE: Remember to flush the gd.
 *
 * Returns 0 on success.
 */

char lx_gdputc (gd, c)
	lx_gd *gd;
	const char  c;
{
	lx_s stmp = {(char *)&c}; /* buf to string, immediately */
	stmp.alloc = stmp.len = 1;

	return (lx_gdstrput(gd, &stmp));
}
