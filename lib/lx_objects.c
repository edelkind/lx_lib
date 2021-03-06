#include "lx_string.h"
#include <stdlib.h>

/***********************************************************************//**
  Allocate a chunk the size of an lx_s.
  Subelement [s] will be zero, depicting unallocated content.

  Returns:
  A pointer to the new chunk on success;
  0 on out-of-memory error
 ***************************************************************************/
lx_s *lx_new(void)
{
    lx_s *data = malloc(sizeof(lx_s));
    if (!data) return 0;
    data->s = 0;
    return data;
}

/***********************************************************************//**
  Destroy a previously allocated lx_s object, including the data within it.
 ***************************************************************************/

void lx_destroy(lx_s *obj)
{
    if (obj->s) lx_free(obj);
    free(obj);
}
