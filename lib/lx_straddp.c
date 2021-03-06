#include <stdarg.h>
#include "lx_string.h"

/**
 * Adds given strings to a string buffer.
 *
 * Returns 0 on success.
 */

char lx_straddp (lx_s *s_dest, char *src, ...)
	/* lx_s *s_dest; */
	/* char *src; */
{
	va_list ap;

	va_start (ap, src);

	for (;;) {
		if (!src) break;

		lx_stradd (s_dest, src);
		src = va_arg (ap, char *);
	}

	va_end (ap);
	return 0;
}
