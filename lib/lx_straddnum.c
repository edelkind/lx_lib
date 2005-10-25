#include "lx_string.h"

#if 0
	*** lx_straddlong ***
	adds a given unsigned number to a string buffer, in string context
	if you have a number with a base of more than 35, you are not
	promised a useful result.
	returns 0 on success.
#endif

char lx_straddulong (s_dest, num, base)
	struct lx_string *s_dest;
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
		char numstr[len+1];

		numstr[len] = 0;
		while (len--) {
			n = (num % base);
			numstr[len] = ((n < 10) ? '0' : ('a' - 10)) + n;
			num /= base;
		}

		return (lx_stradd (s_dest, (char *)numstr));
	}
}

char lx_straddlong (s_dest, num, base)
	struct lx_string *s_dest;
	long num;
	unsigned int base;
{
	if (num < 0) {
		if (lx_cadd(s_dest, '-')) return 1;
		num = -num;
	}

	return lx_straddulong(s_dest, num, base);
}

