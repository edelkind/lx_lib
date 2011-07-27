#include "lx_string.h"

/**
 * Adds a given unsigned number to a string buffer, in string context.
 * If you have a number with a base of more than 35, you are not
 * promised a useful result.
 *
 * Returns 0 on success.
 */

char lx_gdaddulong (gd, num, base)
	lx_gd *gd;
	unsigned long num;
	unsigned int base;
{
	unsigned long n = num;
	unsigned int len = 1;

	if (base < 2)     /* user error */
		return 2;

	for (; n >= base; len++) {
		n /= base;
	}

	{
		char numstr[len];
		lx_s stmp = {(char *)numstr}; /* buf to string, immediately */
		stmp.alloc = stmp.len = len;

		while (len--) {
			n = (num % base);
			numstr[len] = ((n < 10) ? '0' : ('a' - 10)) + n;
			num /= base;
		}

		return (lx_gdstrput (gd, &stmp));
	}
}

/** Like lx_gdaddulong(), but signed.
 */
char lx_gdaddlong (gd, num, base)
	lx_gd *gd;
	signed long num;
	unsigned int base;
{
	if (num < 0) {
		lx_gdputc (gd, '-');
		num = 0 - num;
	}

	return (lx_gdaddulong (gd, (unsigned long) num, base));
}
