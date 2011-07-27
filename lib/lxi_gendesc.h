
#ifndef _LXI_DESC_H
#define _LXI_DESC_H


/**
 * generic descriptors
 */
typedef struct lx_gd {
	char *buf;
	int fd; /**< _could_ possibly be negative if used for return value */
	int a; /**< amount left in allocated buf */
	int n; /**< amount left in currently read buf */
	int p; /**< position from beginning of allocated buf */
} lx_gd;

#endif
