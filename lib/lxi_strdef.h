#define lx_empty(strbuf) (!((strbuf).s))
#define lx_full(strbuf) ((strbuf).s)

#define lx_addnl(strbuf) lx_cadd(strbuf, '\n')
