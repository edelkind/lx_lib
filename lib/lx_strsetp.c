#include <stdarg.h>
#include "lx_string.h"

#if 0
	*** lx_strsetp ***
	sets a string buffer to given strings
	returns 0 on success
#endif

char lx_strsetp (lx_s *s_dest, char *src, ...)
	/* lx_s *s_dest; */
	/* char *src; */
{
	va_list ap;

	va_start (ap, src);

	if (s_dest->s)
		lx_free (s_dest);

	for (;;) {
		if (!src) break;

		lx_stradd (s_dest, src);
		src = va_arg (ap, char *);
	}

	va_end (ap);
	return 0;
}
