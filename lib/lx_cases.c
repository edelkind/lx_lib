
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


#if 0
	*** lx_lowersp ***
	store l lowercase bytes of s into p
	note that p _must_ have at least l bytes allocated to avoid overflow
	returns nothing
#endif

void lx_lowersp (p, s, l)
	char *p, *s;
	unsigned int l;
{
	char c;
	while (l--) {
		c = *s++;
		if (c >= 'A' && c <= 'Z')
			c += 'a' - 'A';

		*p++ = c;
	}
}


#if 0
	*** lx_uppersp ***
	store l uppercase bytes of s into p
	note that p _must_ have at least l bytes allocated to avoid overflow
	returns nothing
#endif

void lx_uppersp (p, s, l)
	char *p, *s;
	unsigned int l;
{
	char c;
	while (l--) {
		c = *s++;
		if (c >= 'a' && c <= 'z')
			c += 'A' - 'a';

		*p++ = c;
	}
}


#if 0
	*** lx_lowerstr ***
	store l lowercase bytes of s into ss
	str may be dynamically allocated.
	returns zero on success, 1 otherwise
#endif

char lx_lowerstr (ss, s, l)
	lx_s *ss;
	char *s;
	unsigned int l;
{
	char c;

	if (lx_setalloc (ss, l))
		return 1;

	lx_lowersp (ss->s, s, l);
	return 0;
}


#if 0
	*** lx_upperstr ***
	store l uppercase bytes of s into ss
	str may be dynamically allocated.
	returns zero on success, 1 otherwise
#endif

char lx_upperstr (ss, s, l)
	lx_s *ss;
	char *s;
	unsigned int l;
{
	char c;

	if (lx_setalloc (ss, l))
		return 1;

	lx_uppersp (ss->s, s, l);
	return 0;
}

