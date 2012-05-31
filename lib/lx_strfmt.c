#define _GNU_SOURCE

#include "lx_string.h"
#include <stdarg.h>
#include <stdio.h>

#if 0
struct lx_fmt_token {
    char *tok_start;
    unsigned tok_len;
    char tok_type;
    char tok_padding;
    unsigned result_len;
};

char
lx_fmt_tok_next(char *fmt, struct lx_fmt_token *tok, va_list ap)
{
    char *p;

    p = strchr(fmt, '%');
    if (!p) return 1;
    while (*++p) {
        /* XXX: finish this */
    }
}

char
lx_strprintf_append(lx_s *dest, char *fmt, ...) __attribute__((format(printf, 2, 3)))
{
    va_list ap;
    va_start(ap, fmt);
    char *fmtp;
    struct lx_fmt_token tok;

    fmtp = fmt;
    while (!lx_fmt_tok_next(fmt, &tok, ap)) {
        if (lx_striadd(dest, fmtp, tok.tok_start-fmtp))
            return 1;
        if (lx_plusalloc(dest, tok.result_len))
            return 1;
        lx_fmt_tok_write(dest, &tok, ap);
        dest->len += tok.result_len;

        fmtp = tok.tok_start + tok.tok_len;
    }
    if (*fmtp) {
        if (lx_stradd(dest, fmtp))
            return 1;
    }

    return 0;
}

#endif /* 0 */

/**
 * sprint into a lx_s buffer, auto-allocating as necessary.
 *
 * \note Currently uses vasprintf(3) as a back-end, but this should change.
 *
 * \todo finish implementing own formatting back-end (see source). Then \c _GNU_SOURCE can be removed, too.
 *
 * \returns 0 on success
 */
char
lx_strvprintf(lx_s *dest, const char *fmt, va_list ap)
{
    int len;
    char *tmp;

    if (dest->s)
        lx_free(dest);

    len = vasprintf(&tmp, fmt, ap);

    if (len < 0)
        return 1;

    dest->s = tmp;
    dest->alloc = dest->len = len;
    return 0;
}

/**
 * sprint into a lx_s buffer, auto-allocating as necessary.
 *
 * \see lx_strvprintf()
 */
char
lx_strprintf(lx_s *dest, const char *fmt, ...)
{
    va_list ap;
    int rv;

    va_start(ap, fmt);
    rv = lx_strvprintf(dest, fmt, ap);
    va_end(ap);
    return rv;

}

