#include "lx_string.h"

extern void *memcpy();

#if 0
	*** lx_gd2s ***
	copies at most *amt bytes from gd to s
	advances gd, and adjusts *amt to the proper amount left
	does not check size of s; everything must be set up beforehand
	returns nothing
#endif

void lx_gd2s (s, gd, amt)
	lx_s *s;
	register lx_gd *gd;
	unsigned int *amt;
{
	register int amount = *amt;

	if (amount < gd->n) {
		memcpy (s->s+s->len, gd->buf, amount);
		LX_gdff (gd, amount);
		s->len += amount;
		amount = 0;
	} else {
		memcpy (s->s+s->len, gd->buf, gd->n);
		s->len += gd->n;
		amount -= gd->n;
		LX_gdrw (gd);
	}
	*amt = amount; return;
}

