#include "lx_string.h"

#if 0
	*** lx_cadd ***
	adds a given character to a string buffer
	returns 0 on success.
#endif

char lx_cadd (s_dest, c)
	struct lx_string *s_dest;
	char c;
{

	if (!(s_dest->s)) {
		if (lx_alloc (s_dest, 1))
			return 1;
		s_dest->len = 0;
	}
	
	else if (s_dest->len == s_dest->alloc) {
		if (lx_setalloc (s_dest, s_dest->len+1))
			return 1;
	}

	*(s_dest->s + s_dest->len) = c;
	s_dest->len++;

	return 0;
}
