#include "lx_string.h"

extern void *memcpy();

#if 0
	*** lx_mirror ***
	mirrors a string buffer
	NOTE: this does not copy the string buffer; this copies the
	      _structure_ itself.  sd->s and ss->s will hold exactly the
	      same values.
	returns nothing.
#endif

void lx_mirror(sd, ss)
	lx_s *sd;
	const lx_s *ss;
{
	(void) memcpy (sd, ss, sizeof(lx_s));
}
