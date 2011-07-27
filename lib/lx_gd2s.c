#include "lx_string.h"

#include <string.h>

/**
 * Copies at most *amt bytes from gd to s.
 *
 * Advances gd, and adjusts *amt to the proper amount left.
 * Does not check size of s; everything must be set up beforehand.
 */

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

