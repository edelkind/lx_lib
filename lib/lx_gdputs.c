#include "lx_string.h"

extern int strlen();

#if 0
	*** lx_gdputs ***
	outputs a string to a generic descriptor
	NOTE: remember to flush the gd
	returns 0 on success
#endif

char lx_gdputs (gd, s)
	lx_gd *gd;
	char  *s;
{
	lx_s stmp = {s}; /* buf to string, immediately */
	stmp.alloc = stmp.len = strlen(s);

	return (lx_gdstrput(gd, &stmp));
}
