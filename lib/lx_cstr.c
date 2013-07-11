#include "lx_string.h"

/** Returns a pointer to a C string, internal to \a buf.  This is different
 * from just using \a buf->s because it's guaranteed to be null-terminated.
 *
 * If memory could not be allocated for a terminating 0, an empty string is
 * returned.  This function never returns \c NULL.
 */
const char *
lx_cstr(lx_s *buf) {
    if (!buf->s || lx_post0(buf))
        return "";

    return buf->s;
}

/** Best effort to fulfill a lx_cstr() style request without modifying \a buf.
 * If \a buf was directly assigned to a cstring, using \ref lx_strsetdirect, no
 * modifications should be performed.
 */
const char *
lx_cstr_tryconst(lx_s *buf) {
    if (!buf->s)
        return "";

    if ( (  buf->alloc > buf->len && !buf->s[buf->len]  ) ||
         (  buf->len              && !buf->s[buf->len-1]) ) {
        return buf->s;
    }

    return lx_cstr(buf);
}
