/**
 * Same as strlen() (works on C strings).
 *
 * \todo Could be optimized with 4-byte or 8-byte reads and casts.  On x86,
 * could also be asm-optimized for 16-bit processing (ax->al|ah).
 *
 * Returns the string length.
 */

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
