
#if 0
	*** lx_lowers ***
	make l bytes of s lowercase (if applicable)
	returns nothing
#endif

void lx_lowers (s, l)
	char *s;
	unsigned int l;
{
	char c;
	while (l--) {
		c = *s;
		if (c < 'A' || c > 'Z') continue;
		*s++ = c + ('a' - 'A');
	}
}


#if 0
	*** lx_uppers ***
	make l bytes of s uppercase (if applicable)
	returns nothing
#endif

void lx_uppers (s, l)
	char *s;
	unsigned int l;
{
	char c;
	while (l--) {
		c = *s;
		if (c < 'a' || c > 'z') continue;
		*s++ = c + ('A' - 'a');
	}
}
