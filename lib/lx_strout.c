#include <stdio.h>  /* FILE declaration */
#include "lx_string.h"
extern int write();
extern unsigned int fwrite();

#if 0
	*** lx_strout ***
	print a string to a given file descriptor
	returns the number of bytes written, or -1 on error
#endif

int lx_strout (fd, str)
	int fd;
	struct lx_string *str;
{
	if (!str->s || str->len == 0) return 0;
	return (write (fd, str->s, str->len));
}

#if 0
	*** lx_fstrout ***
	print a string to a given stream
	returns the number of characters written; short/0 count on error
#endif

unsigned int lx_fstrout (fs, str)
	FILE *fs;
	struct lx_string *str;
{
	if (!str->s || str->len == 0) return 0;
	return (fwrite (str->s, sizeof(char), str->len, fs));
}
