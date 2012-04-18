#ifndef _LXISTRING_HPP
#define _LXISTRING_HPP

// #define NDEBUG
#include <cassert>

/************************************************************************//**
 *** lx::String (LX Generic Data Buffer class)
 ****************************************************************************/

class String {
    /**
     * @defgroup Sumbrella lx::String components
     * @{
     */

    public:
        lx_string s;

        /****************************************************************//**
          @defgroup Snew Constructors and destructors
          @{
         ********************************************************************/

        /** [new] : [init this, basic form].
         *
         * @c s.s is set to 0.
         * @c s.len is set to 0.
         *
         * Calls to @c this.len() will return 0 if we haven't yet been
         * initialized.
        */
        inline String() throw()
        { s.s = 0; s.len = 0; }

        /** [new] : lx_strset(this, src).
         * @see lx_strset()
        */
        inline String(const char *src) throw(AllocError)
        { s.s = 0; copy(src); }

        /** [new] : lx_striset(this, src, n).
         * @see lx_striset()
        */
        inline String(const char *src, unsigned int n) throw(AllocError)
        { s.s = 0; copy(src, n); }

        /** [destroy] : lx_free(this).
         * @see lx_free()
        */
        inline ~String() throw()
        { if (s.s) lx_free(&s); }

#if 0
        inline String(const String& rhs)
        {
            assert(!"use copy() instead of direct assignment -- did you forget to mark a reference?");
            if (this != &rhs) {
                s.s = 0;
                this->copy(rhs);
            }
        }

        String& operator= (const String& rhs)
        {
            assert(!"use copy() instead of direct assignment -- did you forget to mark a reference?");
            if (this != &rhs) {
                this->copy(rhs);
            }

            return *this;
        }
#endif



        /** @} */
        /****************************************************************//**
          @defgroup Sconvenient Convenience for underlying data structures
          @{
         ********************************************************************/

        /** returns underlying lx_s */
        inline lx_s& base()
        { return s; }

        /** length of underlying lx_s */
        inline unsigned int len()
        { return s.len; }

        /** pointer to the buffer of the underlying lx_s */
        inline char *ptr()
        { return s.s; }


        /** Check whether the String has actually been initialized (used) yet.
         *
         * \retval TRUE \c s.s != 0
         * \retval FALSE \c !s.s
         */
        inline bool initialized()
        { return s.s != 0; }


        /** @} */
        /****************************************************************//**
          @defgroup Sassign String assignment functions
          @{
         ********************************************************************/

        /** strnset : lx_strnset(this, src, maxlen).
         * @see lx_strnset()
        */
        inline void strnset(const char *src, unsigned int maxlen) throw(AllocError)
        {
            if (lx_strnset(&s, (char *)(void *)src, maxlen))
                throw AllocError();
        }


        /** copy : lx_strcopy(this, src).
         * @see lx_strcopy()
        */
        inline void copy(const String& src) throw(AllocError)
        {
            if (lx_strcopy(&s, const_cast<lx_s*>(&src.s) ))
                throw AllocError();
        }


        /** copy : lx_strncopy(this, src, maxlen).
         * @see lx_strncopy()
        */
        inline void copy(const String& src, unsigned int maxlen) throw(AllocError)
        {
            if (lx_strncopy(&s, const_cast<lx_s*>(&src.s), maxlen))
                throw AllocError();
        }


        /** copy : lx_strset(this, src).
         * @see lx_strset()
        */
        inline void copy(const char *src) throw(AllocError)
        {
            if (lx_strset(&s, const_cast<char*>(src) )) /// \todo fix const in lxlib
                throw AllocError();
        }


        /** copy : lx_striset(this, src, n).
         * @see lx_striset()
        */
        inline void copy(const char *src, unsigned int n) throw(AllocError)
        {
            if (lx_striset(&s, const_cast<char*>(src), n))
                throw AllocError();
        }

        /** empty string contents.
         */
        inline void empty() throw()
        { s.len = 0; }

        /** @} */
        /****************************************************************//**
          @defgroup Sappend String append/insert functions
          @{
         ********************************************************************/

        /** append : lx_strcat(this, src).
         * @see lx_strcat()
        */
        inline void append(const String& src) throw(AllocError)
        { append(src.s); }

        /** append : lx_strcat(this, src).
         * @see lx_strcat()
        */
        inline void append(const lx_s& src) throw(AllocError)
        {
            if (lx_strcat(&s, const_cast<lx_s*>(&src) ))
                throw AllocError();
        }

        /** append : lx_striadd(this, src, maxlen||src.len()).
         * @see lx_striadd()
        */
        inline void append(const String& src, unsigned int maxlen) throw(AllocError)
        {
            if (maxlen > src.s.len)
                maxlen = src.s.len;

            if (lx_striadd(&s, src.s.s, maxlen))
                throw AllocError();
        }


        /** append : lx_striadd(this, src, len).
         * @see lx_striadd()
        */
        inline void append(const char *src, unsigned int len) throw(AllocError)
        {
            if (lx_striadd(&s, const_cast<char*>(src), len))
                throw AllocError();
        }

        /** append : lx_stradd(this, src).
         * @see lx_stradd()
        */
        inline void append(const char *src) throw(AllocError)
        {
            if (lx_stradd(&s, const_cast<char*>(src) ))
                throw AllocError();
        }

        /** append : lx_cadd(this, src).
         * @see lx_cadd()
        */
        inline void append(char c) throw(AllocError)
        {
            if (lx_cadd(&s, c ))
                throw AllocError();
        }

        /** Add unsigned num with base base.
         * @see: lx_straddulong()
         */
        inline void addulong(unsigned long num,
                             unsigned int base=10) throw(AllocError)
        {
            if (lx_straddulong(&s, num, base))
                throw AllocError();
        }

        /** Add signed num with base base.
         * @see: lx_straddlong()
         */
        inline void addlong(long num,
                            unsigned int base=10) throw(AllocError)
        {
            if (lx_straddlong(&s, num, base))
                throw AllocError();
        }

        /** Append to string.
         * \param p pointer to data for insertion
         * \param len length of data to insert
         * \param off offset from beginning of self to begin insertion
         * \param del amount to delete from self[off] before inserting
         *
         * self must already contain at least off+del bytes.
         *
         * @see: lx_strinsert()
         */
        inline void insert( const char *p,
                            unsigned int len,
                            unsigned int off,
                            unsigned int del=0) throw(AllocError)
        {
            if (lx_strinsert(&s, const_cast<char*>(p), len, off, del))
                throw AllocError();
        }


        /** @} */
        /****************************************************************//**
          @defgroup Sext Interfacing with non-lx functions
          @{
         ********************************************************************/

        /** check0 : lx_check0(this).
         * @see lx_check0()
        */
        inline void check0() throw(AllocError)
        {
            if (lx_check0(&s))
                throw AllocError();
        }

        /** post0 : lx_post0(this).
         * @see lx_post0()
        */
        inline void post0() throw(AllocError)
        {
            if (lx_post0(&s))
                throw AllocError();
        }

        /** cstr : return lx_cstr(this).
         * @see lx_cstr()
        */
        inline const char *post0() throw()
        { return lx_cstr(&s); }

        /** offer : return lx_stroffer(this).
         * @see lx_stroffer()
        */
        inline void *offer() throw(AllocError)
        {
            void *rv = lx_stroffer(&s);
            if (!rv) throw AllocError();
            return rv;
        }



        /** @} */
        /****************************************************************//**
          @defgroup Smanip Data manipulation functions
          @{
         ********************************************************************/


        /** chop : lx_chop(this, n).
         * @see lx_chop()
         *
         * @returns a reference to @a this, for convenience.
         */
        inline String& chop(unsigned int n) throw (UnderflowError)
            { if (lx_chop(&s, n)) throw UnderflowError(); return *this; }


        /** chomp : lx_chomp(this, cstr).
         * @see lx_chomp()
         *
         * @returns a reference to @a this, for convenience.
         */
        inline String& chomp(char *cstr) throw (AllocError)
            { if (lx_chomp(&s, cstr)) throw AllocError(); return *this; }

        /** chompf : lx_chompf(this, cstr).
         * @see lx_chompf()
         */
        inline void chompf(char *cstr) throw (AllocError)
            { if (lx_chompf(&s, cstr)) throw AllocError(); }

        /** chomp : lx_chomp_ws(this).
         * @see lx_chomp_ws()
         */
        inline void chomp() throw ()
            { lx_chomp_ws(&s); }

        /** lx_chompf_ws(this).
         * @see lx_chompf_ws()
         */
        inline void chompf() throw (AllocError)
            { if (lx_chompf_ws(&s)) throw AllocError(); }


        /** Make string lowercase.
         *
         * \returns \c this for convenience.
         * @see lx_lowers()
         */
        inline String& lower() throw ()
        { lx_lowers(s.s, s.len); return *this; }

        /** Make (up to) @a n bytes of string lowercase.
         *
         * \returns \c this for convenience.
         * @see lx_lowers()
         */
        inline String& lower(unsigned int n) throw ()
        {
            if (n > s.len) n = s.len;
            lx_lowers(s.s, n);
            return *this;
        }

        /** Store @a n bytes of lower-case @a s into @c this.
         *
         * \returns \c this for convenience.
         * @see lx_lowerstr()
         */
        inline String& lowerAssign(const char *src, unsigned int n)
            throw (AllocError)
        {
            if (lx_lowerstr(&s, src, n))
                throw AllocError();
            return *this;
        }


        /** Make string uppercase.
         *
         * \returns \c this for convenience.
         * @see lx_uppers()
         */
        inline String& upper() throw ()
        { lx_uppers(s.s, s.len); return *this; }

        /** Make (up to) @a n bytes of string uppercase.
         *
         * \returns \c this for convenience.
         * @see lx_uppers()
         */
        inline String& upper(unsigned int n) throw ()
        {
            if (n > s.len) n = s.len;
            lx_uppers(s.s, n);
            return *this;
        }

        /** Store @a n bytes of upper-case @a s into @c this.
         *
         * \returns \c this for convenience.
         * @see lx_upperstr()
         */
        inline String& upperAssign(const char *src, unsigned int n)
            throw (AllocError)
        {
            if (lx_upperstr(&s, src, n))
                throw AllocError();
            return *this;
        }

        /** @} */
        /****************************************************************//**
          @defgroup Scomp Comparison functions
          @{
         ********************************************************************/

        /**
         * returns true if strings match; false if not.
         * Note C++ style, not C style.
         * @see lx_strcmp()
         */
        inline bool compare(lx_s *s2) throw()
            { return !lx_strcmp(&s, s2); }

        /**
         * returns true if strings match; false if not.
         * Note C++ style, not C style.
         * @see lx_strscmp()
         */
        inline bool compare(char *s2) throw()
            { return !lx_strscmp(&s, s2); }

        /** @} */

    protected:

        /** No copy constructor!  Use \ref copy(). */
        String(const String &rhs) {}

        /** No assignment!  Use \ref copy(). */
        String& operator= (const String& rhs) { return *this; }

    /** @} */
};



#endif // _LXISTRING_HPP
