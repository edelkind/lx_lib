#ifndef _LXISTRINGARRAY_HPP
# define _LXISTRINGARRAY_HPP

extern "C" {
#include <string.h>
}

/************************************************************************//**
 *** lx::StringArray (lx::String Array class)
 ****************************************************************************/

class StringArray {
    /**
     * @defgroup SAumbrella lx::StringArray components
     * @{
     */

    public:
        lx_sa sa;

        /****************************************************************//**
          @defgroup SAnew Constructors and destructors
          @{
         ********************************************************************/

        inline StringArray() throw()
        { sa.sarray = 0; }

        inline ~StringArray() throw()
        {
            if (sa.sarray)
                lx_sa_free(&sa);
        }

        /** @} */

        /****************************************************************//**
          @defgroup SAassign Element assignment functions
          @{
         ********************************************************************/

        inline void add(const lx_s *s)
        { if (lx_sa_add(&sa, s)) throw AllocError(); }

        inline void add(const String& S)
        { add(&S.base()); }

        inline void add(const char *s)
        { if (lx_sa_adds(&sa, s)) throw AllocError(); }

        /** add a char* _with_ its terminating zero. */
        inline void add0(const char *s)
        { if (lx_sa_adds(&sa, s) || lx_post0(&sa.sarray[sa.elem-1]))
            throw AllocError(); }
        /** @} */

    /** @} */

#endif /* _LXISTRINGARRAY_HPP */
