
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

/** Static buffer size for stdio GDs.
 *
 * If you want bigger buffers, call \ref lx_gdnew() on the global gd variables
 * with the size you want (make sure that the existing gds are either unused or
 * flushed so you don't lose data).  DO NOT call lx_gdfree() on it first; you
 * can't free static buffers.
 *
 * \ingroup StdGdIO
 */
#define LX_GD_STDIO_SIZE 2048


extern lx_gd *lx_gd_in;
extern lx_gd *lx_gd_out;
extern lx_gd *lx_gd_err;

#endif
