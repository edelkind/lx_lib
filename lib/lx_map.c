#include <stdarg.h>
#include "lx_string.h"
#include "lx_map.h"

/***************************************************************************
  lx_map

  Map arguments with a particular function.

  [f] must be a function that takes its arguments as:
    int f((void *)dest, (void *)src, (int)len);

  This function is to be called from within a loop, for iterating over
  function arguments.  If the function returns 0, lx_map returns 0; if this
  is the last iteration, lx_map returns 1; if the function returns something
  other than 0, lx_map returns -1.  The function result can be found in [r].

  returns:
    0 on success
    1 on complete
    -1 on error

  Example:
    int somefn(lx_s *dest, ...) {
        va_list ap;
        va_start(ap, dest);
        int r, q;

        do {
            q = lx_map(lx_striadd, dest, &ap, &r);
        } while (!q);
        if (q < 0) exit(-1);
        return 0;
    }

    int main(void) {
        lx_s s = {0};
        somefn(&s, LXM_q("around the world in "),
            LXM_du(80), LXM_q(" days\n"), LXM_END);

        write (1, s.s, s.len);
        return 0;
    }

 ***************************************************************************/

int lx_map(f, dst, ap, rv)
    int (*f)(void *, void *, int);
    void *dst;
    va_list *ap;
    int *rv;
{
    struct lx_map_opt arg = va_arg(*ap, struct lx_map_opt);

    switch (arg.type) {
        case LX_TYPE_END:
            return 1;
        case LX_TYPE_STRING:
            *rv = f(dst, arg.v, arg.n);
            if (*rv) return -1;
            break;
        case LX_TYPE_INT:
        case LX_TYPE_LONG:
            {
                char istr[21], *ip, *ipe = istr+21;
                long abs_i = (long)arg.v;

                if (abs_i < 0) abs_i = -abs_i;

                ip = LX_N_TO_S(abs_i, ipe, arg.n);

                if ((long)arg.v < 0)
                    *(--ip) = '-';

                *rv = f(dst, ip, ipe-ip);
                if (*rv) return -1;
                break;
            }
        case LX_TYPE_UINT:
        case LX_TYPE_ULONG:
            {
                char istr[20], *ip, *ipe = istr+20;

                ip = LX_N_TO_S((unsigned long)arg.v, ipe, arg.n);

                *rv = f(dst, ip, ipe-ip);
                if (*rv) return -1;
                break;
            }
    }
    return 0;
}

