#include "lx_string.h"

#include <string.h>

/**
 * Adds a given string to a string buffer.
 *
 * Returns 0 on success.
 */

char lx_stradd (s_dest, src)
	struct lx_string *s_dest;
	const char *src;
{
	if (!(s_dest->s))
		return (lx_strset (s_dest, src));

	return (lx_striadd(s_dest, src, strlen(src)));
}

/**
 * Adds the specified amount of a given string to a string buffer.
 *
 * Returns 0 on success.
 */

char lx_striadd (s_dest, src, len)
	lx_s *s_dest;
	const char *src;
	unsigned int len;
{
	struct lx_string s_src = {0};

	s_src.s = (char*)src;
	s_src.len = len;
	s_src.alloc = s_src.len;

	return (lx_strcat (s_dest, &s_src));
}
