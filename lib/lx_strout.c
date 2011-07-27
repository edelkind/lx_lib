#include "lx_string.h"
#include <stdio.h>
//extern unsigned int fwrite();

#include <unistd.h>
//extern int write();

/**
 * Print str to a given file descriptor (fd).
 *
 * Returns the number of bytes written, or -1 on error.
 */
int lx_strout (fd, str)
	int fd;
	struct lx_string *str;
{
	if (!str->s || str->len == 0) return 0;
	return (write (fd, str->s, str->len));
}

/**
 * Print str to a given FILE* stream.
 *
 * Returns the number of characters written; short/0 count on error (see fwrite()).
 */
unsigned int lx_fstrout (fs, str)
	void *fs;
	struct lx_string *str;
{
	if (!str->s || str->len == 0) return 0;
	return (fwrite (str->s, sizeof(char), str->len, fs));
}
