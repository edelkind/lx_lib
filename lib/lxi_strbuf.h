#ifndef _LXI_STRBUF_H
#define _LXI_STRBUF_H

typedef struct lx_string {
	char *s;            /**< Pointer to buffer */
	unsigned int len;   /**< Length used */
	unsigned int alloc; /**< Size allocated */
} lx_s;

typedef struct lx_stringplus {
	char *s;            /**< Pointer to current position in buffer */
	unsigned int len;   /**< Length used */
	unsigned int alloc; /**< Size allocated */
	unsigned int p;     /**< Current offset ahead of real allocation */
} lx_sp;

typedef struct lx_stringarray {
	lx_s *sarray;       /**< Beginning of lx_s* array */
	unsigned int elem;  /**< Elements in array */
	unsigned int alloc; /**< Total allocated space for array elements */
} lx_sa;

#endif
