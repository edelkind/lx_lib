#if 0
	*** lx_strlen ***
	same as strlen() (works on traditional strings)
	should be the fastest full c version, but significantly slower
	than the asm version
	returns the string length.
#endif

unsigned int lx_strlen(s)
	register char *s;
{
	register char *p = s;

	for (;;) {
		if (!*p) return (p-s); p++;
		if (!*p) return (p-s); p++;
		if (!*p) return (p-s); p++;
	}
}
