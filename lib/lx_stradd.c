#include "lx_string.h"

#include <string.h>

#if 0
	*** lx_stradd ***
	adds a given string to a string buffer
	returns 0 on success.
#endif

char lx_stradd (s_dest, src)
	struct lx_string *s_dest;
	char *src;
{
	if (!(s_dest->s))
		return (lx_strset (s_dest, src));

	return (lx_striadd(s_dest, src, strlen(src)));
}

#if 0
	*** lx_striadd ***
	adds the specified amount of a given string to a string buffer
	returns 0 on success.
#endif

char lx_striadd (s_dest, src, len)
	lx_s *s_dest;
	char *src;
	unsigned int len;
{
	struct lx_string s_src = {0};

	s_src.s = src;
	s_src.len = len;
	s_src.alloc = s_src.len;

	return (lx_strcat (s_dest, &s_src));
}
