
#if 0
	*** lx_lowerb ***
	make a particular byte lowercase, if applicable
	returns the new character
#endif

char lx_lowerb (c)
	register char c;
{
	if (c < 'A' || c > 'Z') return;

	c += ('a'-'A');
}


#if 0
	*** lx_upperb ***
	make a particular byte uppercase, if applicable
	returns the new character
#endif

char lx_upperb (c)
	register char c;
{
	if (c < 'a' || c > 'z') return;

	c += ('A'-'a');
}

