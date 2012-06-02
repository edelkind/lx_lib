#include "lxi_gendesc.h"

static char _buf_in[LX_GD_STDIO_SIZE];
static char _buf_out[LX_GD_STDIO_SIZE];
static char _buf_err[LX_GD_STDIO_SIZE];

/** \defgroup StdGdIO Standard Gd I/O
 * Standard I/O replacements.  These use static buffers that are included in
 * the library, but will only increase the size of your program if you use them
 * (at which point they are linked in).
 *
 * \sa LX_GD_STDIO_SIZE
 * @{
 */

static lx_gd _lx_gd_in  = { _buf_in,  0, LX_GD_STDIO_SIZE, 0, 0 };
static lx_gd _lx_gd_out = { _buf_out, 1, LX_GD_STDIO_SIZE, 0, 0 };
static lx_gd _lx_gd_err = { _buf_err, 2, LX_GD_STDIO_SIZE, 0, 0 };

lx_gd *lx_gd_in  = &_lx_gd_in;  /**< stdin replacement */
lx_gd *lx_gd_out = &_lx_gd_out; /**< stdout replacement */
lx_gd *lx_gd_err = &_lx_gd_err; /**< stderr replacement */

/** @} */
