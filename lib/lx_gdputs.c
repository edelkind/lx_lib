#include "lx_string.h"

#include <string.h>

/**
 * Outputs a string to a generic descriptor.
 *
 * NOTE: Remember to flush the gd.
 *
 * returns 0 on success
 */

char lx_gdputs (gd, s)
	lx_gd *gd;
	const char  *s;
{
	lx_s stmp = {(char *)s}; /* buf to string, immediately */
	stmp.alloc = stmp.len = strlen(s);

	return (lx_gdstrput(gd, &stmp));
}

/**
 * Outputs n bytes to a generic descriptor.
 *
 * NOTE: Remember to flush the gd.
 *
 * returns 0 on success
 */

char lx_gdputsn (gd, s, n)
	lx_gd *gd;
	const char  *s;
	unsigned int n;
{
	lx_s stmp = {(char *)s}; /* buf to string, immediately */
	stmp.alloc = stmp.len = n;

	return (lx_gdstrput(gd, &stmp));
}

