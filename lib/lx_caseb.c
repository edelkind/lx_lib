
/**
 * Make a particular byte lowercase, if applicable.
 *
 * Returns the new character.
 */

char lx_lowerb (c)
	register char c;
{
	if (c < 'A' || c > 'Z') return c;

	return (c + ('a'-'A'));
}


/**
 * Make a particular byte uppercase, if applicable.
 *
 * Returns the new character.
 */

char lx_upperb (c)
	register char c;
{
	if (c < 'a' || c > 'z') return c;

	return (c + ('A'-'a'));
}

