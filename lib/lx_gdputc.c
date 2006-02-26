#include "lx_string.h"
#include <string.h>


#if 0
	*** lx_gdputc ***
	outputs a character to a generic descriptor
	NOTE: remember to flush the gd
	returns 0 on success
#endif

char lx_gdputc (gd, c)
	lx_gd *gd;
	const char  c;
{
	lx_s stmp = {(char *)&c}; /* buf to string, immediately */
	stmp.alloc = stmp.len = 1;

	return (lx_gdstrput(gd, &stmp));
}
