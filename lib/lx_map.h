/* include after: "lx_string.h" */
#ifndef _LX_MAP_H
#define _LX_MAP_H

struct lx_map_opt {
    int type;
    void *v;
    unsigned int n;
};

#define LX_TYPE_END    0x00
#define LX_TYPE_STRING 0x01
#define LX_TYPE_LONG   0x02
#define LX_TYPE_ULONG  0x03
#define LX_TYPE_UINT   0x04
#define LX_TYPE_INT    0x05

#define LXM_q(s)       ((struct lx_map_opt){ LX_TYPE_STRING, s, sizeof(s)-1 })
#define LXM_qm(s)      ((struct lx_map_opt){ LX_TYPE_STRING, s, sizeof(s)   })
#define LXM_mb(s, len) ((struct lx_map_opt){ LX_TYPE_STRING, s,         len })
#define LXM_l(n)       ((struct lx_map_opt){ LX_TYPE_LONG,   (void *)n, 10  })
#define LXM_d(n)       ((struct lx_map_opt){ LX_TYPE_INT,    (void *)n, 10  })
#define LXM_lu(n)      ((struct lx_map_opt){ LX_TYPE_ULONG,  (void *)n, 10  })
#define LXM_du(n)      ((struct lx_map_opt){ LX_TYPE_UINT,   (void *)n, 10  })
#define LXM_x(n)       ((struct lx_map_opt){ LX_TYPE_ULONG,  (void *)n, 16  })
#define LXM_lxs(s)     ((struct lx_map_opt){ LX_TYPE_STRING, s->s,   s->len })
#define LXM_END        ((struct lx_map_opt){ LX_TYPE_END,    0,         0   })

static inline char *LX_N_TO_S(i, ip, base)
    unsigned long i;
    char *ip;
    unsigned int base;
{
    unsigned int n;

    for (;;) {
        n = i % base;
        *--ip = n + ((n < 10) ? '0' : 'a'-10);
        i /= base;
        if (!i) break;
    }
    return ip;
}

#if 0
static inline int LX_MAP(f, dst, ap, rv)
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
#endif


#endif /* _LX_MAP_H */
