#include "lx_string.h"

/**
 * Ensure that s ends in a binary 0.  If not, add one.
 *
 * Returns 0 on success.
 */

char lx_check0 (s)
	lx_s *s;
{
	if (s->s[s->len-1]) return (lx_cadd(s, 0));
	return 0;
}
