#include "lx_string.h"

#include <string.h>


#if 0
	add a normal string to an array of string buffers
	note that the source string is copied.
	returns 0 on success
#endif

char lx_sa_adds (sa, src)
	lx_sa *sa;
	char *src;
{
	lx_s tmp = {0};

	if (lx_strset (&tmp, src)) return 1;

	return (lx_sa_add (sa, &tmp));
}
