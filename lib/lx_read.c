#include "lx_string.h"

extern int read();

#if 0
	*** lx_read ***
	read from generic descriptor
	will read at MOST gd->n+gd->alloc+gd->p, which is the default
	if amount == 0.
	returns 0 on success
#endif

char lx_read (s, gd, amount)
	lx_s *s;
	register lx_gd *gd;
	unsigned int amount;
{
	if (!amount) amount = (s->s) ? (s->alloc) : (gd->a+gd->p+gd->n);

	s->len = 0;
	if (lx_setalloc (s, amount))
		return 1;

	if (gd->n) {
		lx_gd2s(s, gd, &amount);
		if (amount == 0) return 0; /* amount == gd->n */
	}

	if (!(gd->n = read (gd->fd, gd->buf, gd->a)))
		return 0;

	if (gd->n == -1) {
		gd->n = 0;
		return 1;
	}

	lx_gd2s(s, gd, &amount);
	return 0;

}

