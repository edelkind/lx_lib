#ifndef _LXI_STRBUF_H
#define _LXI_STRBUF_H

typedef struct lx_string {
	char *s;
	unsigned int len;
	unsigned int alloc;
} lx_s;

typedef struct lx_stringplus {
	char *s;
	unsigned int len;
	unsigned int alloc;
	unsigned int p;  /* amount ahead of real allocation */
} lx_sp;

typedef struct lx_stringarray {
	lx_s *sarray;
	unsigned int elem;
	unsigned int alloc;
} lx_sa;

#endif
