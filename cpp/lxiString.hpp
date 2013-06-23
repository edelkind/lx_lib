#ifndef _LXISTRING_HPP
#define _LXISTRING_HPP

// #define NDEBUG
#include <cassert>

extern "C" {
#include <string.h>
}

namespace lx {

/************************************************************************//**
 *** lx::String (LX Generic Data Buffer class)
 ****************************************************************************/

class String : public lx_string {
    /**
     * @defgroup Sumbrella lx::String components
     * @{
     */

    public:

        /****************************************************************//**
          @defgroup Snew Constructors and destructors
          @{
         ********************************************************************/

        /** [new] : [init this, basic form].
         *
         * @c s is set to 0.
         * @c len is set to 0.
         *
         * Calls to @c this.size() will return 0 if we haven't yet been
         * initialized.
        */
        inline String() throw()
        { s = 0; len = 0; }

        /** [new] : lx_strset(this, src).
         * @see lx_strset()
        */
        inline String(const char *src) throw(AllocError)
        { s = 0; copy(src); }

        /** [new] : lx_striset(this, src, n).
         * @see lx_striset()
        */
        inline String(const char *src, unsigned int n) throw(AllocError)
        { s = 0; copy(src, n); }

        /**
         */
        inline String(const String *src) throw(AllocError)
        { s = 0; copy(src); }

        /** [destroy] : lx_free(this).
         * @see lx_free()
        */
        inline ~String() throw()
        { if (s) lx_free(this); }



        /** @} */
        /****************************************************************//**
          @defgroup Sconvenient Convenience for underlying data structures
          @{
         ********************************************************************/

        /** returns underlying lx_s */
        inline lx_s& base()
        { return *this; }

        /** for use in const situations */
        inline const lx_s& base() const
        { return *this; }

        /** length of underlying lx_s */
        inline unsigned int size() const
        { return len; }

        inline unsigned int sizeAlloc() const
        { if (!s) return 0; return alloc; }

        /** pointer to the buffer of the underlying lx_s
         *
         * \note For use as a C string, use \ref cstr().  Do not use this
         * function unless you know what you are doing, since it may not be
         * null-terminated!
         */
        inline char *ptr()
        { return s; }
        inline const char *ptr() const
        { return s; }


        /** Check whether the String has actually been initialized (used) yet.
         *
         * \retval TRUE \c s != 0
         * \retval FALSE \c !s
         */
        inline bool initialized() const
        { return s != 0; }


        /** @} */
        /****************************************************************//**
          @defgroup Sassign String assignment functions
          @{
         ********************************************************************/

        /** alloc : lx_setalloc(this, n)
         * @see lx_setalloc()
         */
        inline void setalloc(unsigned n) throw(AllocError)
        { if (lx_setalloc(this, n)) throw AllocError(); }

        /** strnset : lx_strnset(this, src, maxlen).
         * @see lx_strnset()
        */
        inline void strnset(const char *src, unsigned int maxlen) throw(AllocError)
        {
            if (lx_strnset(this, (char *)(void *)src, maxlen))
                throw AllocError();
        }


        /** copy : lx_strcopy(this, src).
         * @see lx_strcopy()
        */
        //inline void copy(const String& src) throw(AllocError)
        //{
        //    if (lx_strcopy(this, const_cast<lx_s*>((const lx_s*)&src) ))
        //        throw AllocError();
        //}

        /** copy : lx_strcopy(this, src).
         * @see lx_strcopy()
        */
        inline void copy(const lx_s& src) throw(AllocError)
        {
            if (lx_strcopy(this, const_cast<lx_s*>(&src) ))
                throw AllocError();
        }

        inline void copy(const lx_s *src) throw(AllocError)
        {
            if (lx_strcopy(this, src) )
                throw AllocError();
        }


        /** copy : lx_strncopy(this, src, maxlen).
         * @see lx_strncopy()
        */
        inline void copy(const lx_s& src, unsigned int maxlen) throw(AllocError)
        {
            if (lx_strncopy(this, const_cast<lx_s*>(&src), maxlen))
                throw AllocError();
        }

        inline void copy(const lx_s *src, unsigned int maxlen) throw(AllocError)
        {
            if (lx_strncopy(this, src, maxlen))
                throw AllocError();
        }


        /** copy : lx_strset(this, src).
         * @see lx_strset()
        */
        inline void copy(const char *src) throw(AllocError)
        {
            if (lx_strset(this, const_cast<char*>(src) )) /// \todo fix const in lxlib
                throw AllocError();
        }


        /** copy : lx_striset(this, src, n).
         * @see lx_striset()
        */
        inline void copy(const char *src, unsigned int n) throw(AllocError)
        {
            if (lx_striset(this, const_cast<char*>(src), n))
                throw AllocError();
        }

        inline String& printf(const char *fmt, ...) throw(AllocError)
        {
            va_list ap;
            int rv;

            va_start(ap, fmt);
            rv = lx_strvprintf(this, fmt, ap);
            va_end(ap);

            if (rv) throw AllocError();
            return *this;
        }

        inline String& vprintf(const char *fmt, va_list ap) throw(AllocError)
        {
            if (lx_strvprintf(this, fmt, ap))
                throw AllocError();
            return *this;
        }

        /** empty string contents.
         */
        inline void empty() throw()
        { len = 0; }

        /** @} */
        /****************************************************************//**
          @defgroup Sappend String append/insert functions
          @{
         ********************************************************************/

        /** append : lx_strcat(this, src).
         * @see lx_strcat()
        */
        //inline String& append(const String& src) throw(AllocError)
        //{ append(src); return *this; }

        /** append : lx_strcat(this, src).
         * @see lx_strcat()
        */
        inline String& append(const lx_s& src) throw(AllocError)
        {
            if (lx_strcat(this, const_cast<lx_s*>(&src) ))
                throw AllocError();
            return *this;
        }

        inline String& append(const lx_s *src) throw(AllocError)
        {
            if (lx_strcat(this, src) )
                throw AllocError();
            return *this;
        }

        /** append : lx_striadd(this, src, maxlen||src.size()).
         * @see lx_striadd()
        */
        inline String& append(const lx_s& src, unsigned int maxlen)
            throw(AllocError)
        {
            if (maxlen > src.len)
                maxlen = src.len;

            if (lx_striadd(this, src.s, maxlen))
                throw AllocError();
            return *this;
        }


        /** append : lx_striadd(this, src, len).
         * @see lx_striadd()
        */
        inline String& append(const char *src, unsigned int len) throw(AllocError)
        {
            if (lx_striadd(this, const_cast<char*>(src), len))
                throw AllocError();
            return *this;
        }

        /** append : lx_stradd(this, src).
         * @see lx_stradd()
        */
        inline String& append(const char *src) throw(AllocError)
        {
            if (lx_stradd(this, const_cast<char*>(src) ))
                throw AllocError();
            return *this;
        }

        /** append : lx_cadd(this, src).
         * @see lx_cadd()
        */
        inline String& append(char c) throw(AllocError)
        {
            if (lx_cadd(this, c ))
                throw AllocError();

            return *this;
        }

        /** Add unsigned num with base base.
         * @see: lx_straddulong()
         */
        inline String& addulong(unsigned long num,
                             unsigned int base=10) throw(AllocError)
        {
            if (lx_straddulong(this, num, base))
                throw AllocError();

            return *this;
        }

        /** Add signed num with base base.
         * @see: lx_straddlong()
         */
        inline String& addlong(long num,
                            unsigned int base=10) throw(AllocError)
        {
            if (lx_straddlong(this, num, base))
                throw AllocError();

            return *this;
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
        inline String& insert( const char *p,
                            unsigned int len,
                            unsigned int off,
                            unsigned int del=0) throw(AllocError)
        {
            if (lx_strinsert(this, const_cast<char*>(p), len, off, del))
                throw AllocError();

            return *this;
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
            if (lx_check0(this))
                throw AllocError();
        }

        /** post0 : lx_post0(this).
         * @see lx_post0()
        */
        inline void post0() throw(AllocError)
        {
            if (lx_post0(this))
                throw AllocError();
        }

        /** cstr : return lx_cstr(this).
         * @see lx_cstr()
        */
        inline const char *cstr() const throw()
        { return lx_cstr(const_cast<lx_s*>((const lx_s*)this)); }

        /** offer : return lx_stroffer(this).
         * @see lx_stroffer()
         *
         * New allocation: can use \c free().
         *
         * @throws AllocError on ENOMEM
        */
        inline void *offer() const throw(AllocError)
        {
            void *rv = lx_stroffer(this);
            if (!rv) throw AllocError();
            return rv;
        }

        /** Disown a currently allocated buffer.  This string will be reset,
         * and the original buffer will no longer be managed or tracked by this
         * object.  Returns a pointer to the disowned memory.
         */
        inline void *disown()
        {
            void *buf = (void*)s;
            s = 0;
            len = alloc = 0;
            return buf;
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
            { if (lx_chop(this, n)) throw UnderflowError(); return *this; }


        /** chomp : lx_chomp(this, cstr).
         * @see lx_chomp()
         *
         * @returns a reference to @a this, for convenience.
         */
        inline String& chomp(char *cstr) throw (AllocError)
            { if (lx_chomp(this, cstr)) throw AllocError(); return *this; }

        /** chompf : lx_chompf(this, cstr).
         * @see lx_chompf()
         *
         * @returns a reference to @a this, for convenience.
         */
        inline String& chompf(char *cstr) throw (AllocError)
            { if (lx_chompf(this, cstr)) throw AllocError(); return *this; }

        /** chomp : lx_chomp_ws(this).
         * @see lx_chomp_ws()
         *
         * @returns a reference to @a this, for convenience.
         */
        inline String& chomp() throw ()
            { lx_chomp_ws(this); return *this; }

        /** lx_chompf_ws(this).
         * @see lx_chompf_ws()
         *
         * @returns a reference to @a this, for convenience.
         */
        inline String& chompf() throw (AllocError)
            { if (lx_chompf_ws(this)) throw AllocError(); return *this; }

        /** Fast-forward past the \a n th instance of a character.  If \a p is
         * not NULL, allocates a new C string for the old segment and stores it
         * in \a *p .
         *
         * @see lx_strff()
         *
         * \returns true if the character was found; false if it did not exist
         * (\a p will not be modified).
         */
        inline bool fastfw(char **p, char c, unsigned int n)
            throw (AllocError, std::invalid_argument)
        {
            char rv;
            if (!s) throw std::invalid_argument("fastfw called on null value");

            rv = lx_strff(this, p, c, n);
            if (!rv) return true;
            if (rv > 0) throw AllocError();
            return false;
        }

        /** Fast-forward past the \a n th instance of a character.
         *
         * @see lx_strff()
         *
         * \returns true if the character was found; false if it did not exist
         * (\a p will not be modified).
         */
        inline bool fastfw(char c, unsigned int n) throw (AllocError)
        { return fastfw((lx_s*)NULL, c, n); }

        /** Fast-forward past the \a n th instance of a character.  If \a p is
         * not NULL, it will be used to store the old segment (any prior
         * contents will be replaced).
         *
         * @see lx_strffx()
         *
         * \returns true if the character was found; false if it did not exist
         * (\a p will not be modified).
         */
        inline bool fastfw(lx_s *p, char c, unsigned int n)
            throw (AllocError, std::invalid_argument)
        {
            if (!s) throw std::invalid_argument("fastfw called on null value");

            switch (lx_strffx(this, p, c, n)) {
                case 0: return true;
                case 1: throw AllocError();
            }
            return false;
        }

        /** Move a String forward n bytes.
         *
         * @see lx_strfw();
         */
        inline String& forward(char **p, unsigned n) throw (AllocError)
        { if (lx_strfw(this, p, n)) throw AllocError(); return *this; }

        /** Move a String forward n bytes.
         *
         * @see lx_strfw();
         */
        inline String& forward(unsigned n) throw (AllocError)
        { return forward((lx_s*)NULL, n); }

        /** Move a String forward n bytes.
         *
         * @see lx_strfwx();
         */
        inline String& forward(lx_s *p, unsigned n) throw (AllocError)
        { if (lx_strfwx(this, p, n)) throw AllocError(); return *this; }



        /** Make string lowercase.
         *
         * \returns \c this for convenience.
         * @see lx_lowers()
         */
        inline String& lower() throw ()
        { lx_lowers(s, len); return *this; }

        /** Make (up to) @a n bytes of string lowercase.
         *
         * \returns \c this for convenience.
         * @see lx_lowers()
         */
        inline String& lower(unsigned int n) throw ()
        {
            if (n > len) n = len;
            lx_lowers(s, n);
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
            if (lx_lowerstr(this, src, n))
                throw AllocError();
            return *this;
        }


        /** Make string uppercase.
         *
         * \returns \c this for convenience.
         * @see lx_uppers()
         */
        inline String& upper() throw ()
        { lx_uppers(s, len); return *this; }

        /** Make (up to) @a n bytes of string uppercase.
         *
         * \returns \c this for convenience.
         * @see lx_uppers()
         */
        inline String& upper(unsigned int n) throw ()
        {
            if (n > len) n = len;
            lx_uppers(s, n);
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
            if (lx_upperstr(this, src, n))
                throw AllocError();
            return *this;
        }

        /** @} */
        /****************************************************************//**
          @defgroup Ssearch Search functions
          @{
         ********************************************************************/

        /** Find the \a n th index of character \a c.
         *
         * @see lx_strindex()
         *
         * \returns -1 if the character could not be found.
         */
        inline long index(char c, unsigned n=1) throw()
        { return lx_strindex(this, c, n); }

        /** Find the \a n th index of any character in set \a set (which has
         * length \a setl).
         *
         * @see lx_strindex()
         *
         * \returns -1 if no such character could be found.
         */
        inline long indexSet(const char *set, unsigned setl, unsigned n) throw()
        { return lx_strsindex(this, set, setl, n); }


        /** @} */
        /****************************************************************//**
          @defgroup Scomp Comparison functions
          @{
         ********************************************************************/

        /** Compare with an lx_s.
         *
         * \retval true strings match
         * \retval false they do not.
         *
         * \note boolean style return value, not C style.
         *
         * @see lx_strcmp()
         */
        inline bool compare(const lx_s *s2) throw()
            { return !lx_strcmp(this, s2); }

        /** Compare with a character pointer.
         *
         * \retval true strings match
         * \retval false they do not.
         *
         * \note boolean style return value, not C style.
         *
         * @see lx_strscmp()
         */
        inline bool compare(const char *s2) throw()
            { return !lx_strscmp(this, s2); }

        /** Compare with another String.
         *
         * \retval true strings match
         * \retval false they do not.
         *
         * \note boolean style return value, not C style.
         *
         * @see lx_strcmp()
         */
        inline bool compare(const lx_s& s2) throw()
        { return !lx_strcmp(this, &s2); }

        /** Compare strings case insensitively.
         *
         * \retval true strings match
         * \retval false they do not.
         *
         * \note boolean style return value, not C style.
         *
         * @see lx_stricmp()
         */
        inline bool icompare(const lx_s &s2) throw()
        { return !lx_stricmp(this, &s2); }

        /** Compare strings case insensitively.
         *
         * \retval true strings match
         * \retval false they do not.
         *
         * \note boolean style return value, not C style.
         *
         * @see lx_stricmp()
         */
        inline bool icompare(const char *s2) throw()
        {
            lx_s stmp = { const_cast<char *>(s2) };
            stmp.len = strlen(s2);
            return !lx_stricmp(this, &stmp);
        }

        /** @} */

    protected:

        /** No copy constructor!  Use \ref copy(). */
        String(const String &rhs) {}

        /** No assignment!  Use \ref copy(). */
        String& operator= (const String& rhs) { return *this; }

    /** @} */
};

class StringDirect : public String
{
    public:
    /** Directly assign basea structure to \a *s_from. */
    StringDirect(const lx_s *s_from)
    { *(lx_s*)this = *s_from; }

    StringDirect(const char *s_from)
    { this->s = const_cast<char*>(s_from); this->len = strlen(s_from); }

    /** Use \ref assign() to initialize. */
    StringDirect()
    { }

    /** Base \c lx_s memory will not be freed. */
    ~StringDirect()
    { s = 0; }

    /* Directly assign the base \c lx_s to \a s_from . */
    inline void assign(lx_s *s_from)
    { *(lx_s*)this = *s_from; }

    /** Not allocated -- take care that this never needs to realloc! */
    inline void assign(char *s_from, int s_len)
    { s = s_from; len = alloc = s_len; }
};


} // namespace lx

#endif // _LXISTRING_HPP
