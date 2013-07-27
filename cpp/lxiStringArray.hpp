#ifndef _LXISTRINGARRAY_HPP
# define _LXISTRINGARRAY_HPP

extern "C" {
#include <lx_string.h>
}

#include "lxiString.hpp"

namespace lx {

class StringArray;

static inline lx_s *StringNew() {
    return new lx::String();
}

static inline void StringDelete(lx_s *s) {
    String *sx = static_cast<String*>(s);
    return delete sx;
}

#define FLAG_ZERO_MEMORY    0x1

/************************************************************************//**
 *** lx::StringArray (lx::String Array class)
 ****************************************************************************/

class StringArray : public lx_stringarray {
    /**
     * @defgroup SAumbrella lx::StringArray components
     * @{
     */

    public:
        //lx_sa sa;
        //int flags;

        /****************************************************************//**
          @defgroup SAnew Constructors and destructors
          @{
         ********************************************************************/

        inline StringArray() throw()
        {
            sarray = 0;
            lx_sa_alloc(this, 1);
            _new = StringNew;
            _delete = StringDelete;
        }

        inline ~StringArray() throw()
        {
            lx_sa_free(this);
        }

        inline void empty(void) throw()
        {
            lx_sa_empty(this);
        }

        /** @} */

        /****************************************************************//**
          @defgroup SAflags Flag setting functions
          @{
          \todo flag setting/getting functions
         ********************************************************************/


        /** @} */

        /****************************************************************//**
          @defgroup SAassign Element assignment functions
          @{
         ********************************************************************/

        inline void add(const lx_s *s)
        { if (lx_sa_add(this, s)) throw AllocError(); }

        //inline void add(const String& S)
        //{ add(&S.base()); }

        inline void add(const char *s)
        { if (lx_sa_adds(this, s)) throw AllocError(); }

        inline void add(const lx::StringArray *src)
        { if (lx_sa_addsa(this, src)) throw AllocError(); }

        inline void add(const char *const *pp)
        { if (lx_sa_addpp(this, pp)) throw AllocError(); }

        inline void add(const char *const *pp, int n)
        { if (lx_sa_addppn(this, pp, n)) throw AllocError(); }

        /** add a char* _with_ its terminating zero. */
        inline void add0(const char *s)
        { if (lx_sa_adds(this, s) || lx_post0(sarray[elem-1]))
            throw AllocError(); }
        /** @} */

        /****************************************************************//**
          @defgroup SApop Element removal functions
          @{
         ********************************************************************/

        inline void popBack(lx_s **destp)
        { if (lx_sa_pop_back(this, destp)) throw RangeError(); }

        inline void popFront(lx_s **destp)
        { if (lx_sa_pop_front(this, destp)) throw RangeError(); }

        inline void popIndex(lx_s **destp, int index)
        { if (lx_sa_pop_index(this, destp, index)) throw RangeError(); }

        /** @} */

        /****************************************************************//**
          @defgroup SAref Data reference functions
          @{
         ********************************************************************/

        /** Convert to a pointer array, allocated and contained in \a dest.
         *
         * \param [out] dest  \c String type for data storage
         *
         * \returns a cast pointer to the allocated memory for convenience
         * (don't free this; it will be freed when \a dest is destroyed).
         */
        inline char **toPointerArray(String* dest)
        {
            if (!sarray) {
                dest->empty();
                return NULL;
            }

            if (lx_sa_to_charpp(this, dest))
                throw AllocError();
            return (char**)dest->ptr();
        }

        inline String *get(unsigned index) const
        {
            if (index > len())
                throw RangeError();

            return static_cast<String*>(array()[index]);
        }
        /** @} */

        /****************************************************************//**
          @defgroup SAaccess Accessors for internal structures
          @{
         ********************************************************************/

        inline lx_sa& base() const
        { return *const_cast<lx::StringArray*>(this); }

        inline lx_s **array() const
        { return sarray; }

        inline unsigned len() const
        { return elem; }

        inline unsigned allocated() const
        { return alloc; }

        /** @} */

    /** @} */
};


} // namespace lx


#endif /* _LXISTRINGARRAY_HPP */
