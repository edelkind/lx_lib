/** \todo make this file more useful */

#define lx_empty(strbuf) (!((strbuf).s)) /** test if lx_s is uninitialized */
#define lx_full(strbuf) ((strbuf).s)     /** test if lx_s has been initialized */

#define lx_addnl(strbuf) lx_cadd(strbuf, '\n') /** add a newline */

#define auto_lx_s(s) lx_s (s) __attribute__((cleanup(lx_free)))
#define auto_lx_sa(sa) lx_sa (sa) __attribute__((cleanup(lx_sa_free)))
