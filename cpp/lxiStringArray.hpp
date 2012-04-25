#ifndef _LXISTRINGARRAY_HPP
# define _LXISTRINGARRAY_HPP

extern "C" {
}

#define FLAG_ZERO_MEMORY    0x1

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
        int flags;

        /****************************************************************//**
          @defgroup SAnew Constructors and destructors
          @{
         ********************************************************************/

        inline StringArray() throw()
        { sa.sarray = 0; }

        inline ~StringArray() throw()
        {
            if (!(flags & FLAG_ZERO_MEMORY))
                lx_sa_free(&sa);
            else
                lx_sa_zfree(&sa);
        }

        inline void empty(void) throw()
        {
            if (!(flags & FLAG_ZERO_MEMORY))
                lx_sa_empty(&sa);
            else
                lx_sa_zempty(&sa);
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
            if (lx_sa_to_charpp(&sa, &dest->base()))
                throw AllocError();
            return (char**)dest->ptr();
        }
        /** @} */

    /** @} */
};

#endif /* _LXISTRINGARRAY_HPP */
