#include <stdio.h>  /* FILE declaration */
#include <stdarg.h>
#include "lx_string.h"
extern int write ();
extern unsigned int fwrite ();
extern void *memset();

#if 0
	*** lx_strnout ***
	print multiple strings to a given fd
	must be zero-terminated
	returns the number of characters written

	DON'T USE THIS RIGHT NOW.  IT'S BAD.
#endif

int lx_strnout (int fd, ...)
{
	va_list ap;
	struct lx_string *str = {0};
	int len = 0;

	va_start (ap, fd);

	for (;;) {
		/* set str to zero */
		memset(str, 0, sizeof (struct lx_string));

		str = va_arg(ap, struct lx_string *);
		if (*str->s == 0)
			return (len);

		if (str->alloc != 0) {
			/* it's a string structure */
			len += lx_strout (str);
			continue;
		}

		/* if control reaches here, it should be a normal string
		   ... unless, of course, it was used incorrectly */

		len += write (fd, (char *)str, lx_strlen((char *)str));
	}
}

