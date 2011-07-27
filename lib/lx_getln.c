#include "lx_string.h"

#include <unistd.h>
//extern int read ();
#include <string.h>
//extern void *memchr ();


#define DS '\n'     /* default separator (one character) */

#define RSB(n) return(n)

/**
 * Gets a segment (delimited by *cp) from gd and inserts it into s.
 *
 * Returns 0 on success (if *cp was matched, match is set to 1), or 1 on error.
 */

char lx_getseg (s, gd, cp, match, max)
	struct lx_string *s;
	lx_gd *gd;
	char *cp;
	unsigned char *match;
	register unsigned long max;
{
	char c;
	char *p;
	int l;

	*match = 0;

	if (cp == 0) c = DS;
	else         c = *cp;

	s->len = 0; /* state of s->s doesn't matter */

	for (;;) {
		if (!gd->n) { if (lx_gdfill(gd)) return 1; }
		if (gd->n == 0) return 0;

		/* ensure we don't set s to more than max */
		if   ((max != 0 && (s->len+gd->n) > max)) l = max - s->len;
		else l = gd->n;

		if (!(p = memchr(gd->buf, c, l))) {
			if (lx_gdiappend(s, gd, l)) return 1;
			if (gd->n > l) {
				LX_gdff(gd, l);
				*match |= MATCH_TOOLONG;
				return 0;
			}

			LX_gdrw(gd);
			continue;
		}

		l = (p-gd->buf)+1;
		lx_gdiappend(s, gd, l);
		if (l != gd->n) { LX_gdff(gd, l); }
		else { LX_gdrw(gd); }
		*match |= MATCH_OK;
		return 0;
	}
}

/**
 * Gets a line (delimited by '\n') from gd and inserts it into s.
 * 
 * Accepts at most maxlen bytes of input for a line.
 * If maxlen == 0, input line length is unlimited.
 * 
 * WARNING: if length is unlimited, you may run out of memory reading
 *          from continuous input that does not contain a delimiter.
 *
 * Returns as lx_getseg().
 */

char lx_getln (s, gd, match, maxlen)
	struct lx_string *s;
	lx_gd *gd;
	unsigned char *match;
	unsigned long maxlen;
{
	return (lx_getseg (s, gd, "\n", match, maxlen));
}

