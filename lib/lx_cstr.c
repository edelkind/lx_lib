#include "lx_string.h"

/** Returns a pointer to a C string, internal to \a buf.  This is different
 * from just using \a buf->s because it's guaranteed to be null-terminated.
 *
 * If memory could not be allocated for a terminating 0, an empty string is
 * returned.  This function never returns \c NULL.
 */
const char *
lx_cstr(lx_s *buf) {
    if (lx_post0(buf))
        return "";

    return buf->s;
}
