#include "lx_string.h"

extern int read();

/**
 * Read from generic descriptor.
 *
 * Will read at MOST gd->n+gd->alloc+gd->p, which is the default
 * if amount == 0.
 * 
 *  \deprecated AVOID ME.  USE lx_gdread() INSTEAD.
 *
 * Returns 0 on success.
 */

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

/**
 * Reads from generic descriptor gd, placing the result into s.
 *     offset is the offset into s at which to begin storing data.
 * 
 * Return values are similar to those of read():
 *         the amount read will be returned, or
 *         -1 on error (errno will be set)
 */
int lx_gdread (s, gd, amount, offset)
	lx_s *s;
	register lx_gd *gd;
	int amount;
        unsigned int offset;
{
	unsigned int amt = amount;

	s->len = offset;
	if (lx_setalloc (s, amt+offset))
		return -1;

	if (gd->n) {
		lx_gd2s(s, gd, &amt);
		if (amt == 0) return amount;
	}

	if (!(gd->n = read (gd->fd, gd->buf, gd->a)))
		return amount - amt;

	if (gd->n == -1) {
		gd->n = 0;
		return -1;
	}

	lx_gd2s(s, gd, &amt);
	return amount - amt;
}

