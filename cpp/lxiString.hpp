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

        /** for use in const situations */
        inline const lx_s& base() const
        { return s; }

        /** length of underlying lx_s */
        inline unsigned int len() const
        { return s.len; }

        inline unsigned int alloc() const
        { return s.alloc; }

        /** pointer to the buffer of the underlying lx_s
         *
         * \note For use as a C string, use \ref cstr().  Do not use this
         * function unless you know what you are doing, since it may not be
         * null-terminated!
         */
        inline char *ptr()
        { return s.s; }
        inline const char *ptr() const
        { return s.s; }


        /** Check whether the String has actually been initialized (used) yet.
         *
         * \retval TRUE \c s.s != 0
         * \retval FALSE \c !s.s
         */
        inline bool initialized() const
        { return s.s != 0; }


        /** @} */
        /****************************************************************//**
          @defgroup Sassign String assignment functions
          @{
         ********************************************************************/

        /** alloc : lx_setalloc(this, n)
         * @see lx_setalloc()
         */
        inline void setalloc(unsigned n) throw(AllocError)
        { if (lx_setalloc(&s, n)) throw AllocError(); }

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

        /** copy : lx_strcopy(this, src).
         * @see lx_strcopy()
        */
        inline void copy(const lx_s& src) throw(AllocError)
        {
            if (lx_strcopy(&s, const_cast<lx_s*>(&src) ))
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
        inline String& append(const String& src) throw(AllocError)
        { append(src.s); return *this; }

        /** append : lx_strcat(this, src).
         * @see lx_strcat()
        */
        inline String& append(const lx_s& src) throw(AllocError)
        {
            if (lx_strcat(&s, const_cast<lx_s*>(&src) ))
                throw AllocError();
            return *this;
        }

        /** append : lx_striadd(this, src, maxlen||src.len()).
         * @see lx_striadd()
        */
        inline String& append(const String& src, unsigned int maxlen)
            throw(AllocError)
        {
            if (maxlen > src.s.len)
                maxlen = src.s.len;

            if (lx_striadd(&s, src.s.s, maxlen))
                throw AllocError();
            return *this;
        }


        /** append : lx_striadd(this, src, len).
         * @see lx_striadd()
        */
        inline String& append(const char *src, unsigned int len) throw(AllocError)
        {
            if (lx_striadd(&s, const_cast<char*>(src), len))
                throw AllocError();
            return *this;
        }

        /** append : lx_stradd(this, src).
         * @see lx_stradd()
        */
        inline String& append(const char *src) throw(AllocError)
        {
            if (lx_stradd(&s, const_cast<char*>(src) ))
                throw AllocError();
            return *this;
        }

        /** append : lx_cadd(this, src).
         * @see lx_cadd()
        */
        inline String& append(char c) throw(AllocError)
        {
            if (lx_cadd(&s, c ))
                throw AllocError();

            return *this;
        }

        /** Add unsigned num with base base.
         * @see: lx_straddulong()
         */
        inline String& addulong(unsigned long num,
                             unsigned int base=10) throw(AllocError)
        {
            if (lx_straddulong(&s, num, base))
                throw AllocError();

            return *this;
        }

        /** Add signed num with base base.
         * @see: lx_straddlong()
         */
        inline String& addlong(long num,
                            unsigned int base=10) throw(AllocError)
        {
            if (lx_straddlong(&s, num, base))
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
            if (lx_strinsert(&s, const_cast<char*>(p), len, off, del))
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
        inline const char *cstr() const throw()
        { return lx_cstr(const_cast<lx_s*>(&s)); }

        /** offer : return lx_stroffer(this).
         * @see lx_stroffer()
         *
         * New allocation: can use \c free().
         *
         * @throws AllocError on ENOMEM
        */
        inline void *offer() const throw(AllocError)
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
         *
         * @returns a reference to @a this, for convenience.
         */
        inline String& chompf(char *cstr) throw (AllocError)
            { if (lx_chompf(&s, cstr)) throw AllocError(); return *this; }

        /** chomp : lx_chomp_ws(this).
         * @see lx_chomp_ws()
         *
         * @returns a reference to @a this, for convenience.
         */
        inline String& chomp() throw ()
            { lx_chomp_ws(&s); return *this; }

        /** lx_chompf_ws(this).
         * @see lx_chompf_ws()
         *
         * @returns a reference to @a this, for convenience.
         */
        inline String& chompf() throw (AllocError)
            { if (lx_chompf_ws(&s)) throw AllocError(); return *this; }

        /** Fast-forward past the \a n th instance of a character.  If \a p is
         * not NULL, allocates a new C string for the old segment and stores it
         * in \a *p .
         *
         * @see lx_strff()
         *
         * \returns a reference to \c this for convenience.
         */
        inline bool fastfw(char **p, char c, unsigned int n)
            throw (AllocError)
        {
            char rv;
            rv = lx_strff(&s, p, c, n);
            if (!rv) return true;
            if (rv > 0) throw AllocError();
            return false;
        }

        /** Fast-forward past the \a n th instance of a character.
         *
         * @see lx_strff()
         *
         * \returns a reference to \c this for convenience.
         */
        inline bool fastfw(char c, unsigned int n) throw (AllocError)
        { return fastfw((String*)NULL, c, n); }

        /** Fast-forward past the \a n th instance of a character.  If \a p is
         * not NULL, it will be used to store the old segment (any prior
         * contents will be replaced).
         *
         * @see lx_strffx()
         *
         * \returns a reference to \c this for convenience.
         */
        inline bool fastfw(String *p, char c, unsigned int n)
            throw (AllocError)
        {
            switch (lx_strffx(&s, &p->base(), c, n)) {
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
        { if (lx_strfw(&s, p, n)) throw AllocError(); return *this; }

        /** Move a String forward n bytes.
         *
         * @see lx_strfw();
         */
        inline String& forward(unsigned n) throw (AllocError)
        { return forward((String*)NULL, n); }

        /** Move a String forward n bytes.
         *
         * @see lx_strfwx();
         */
        inline String& forward(String *p, unsigned n) throw (AllocError)
        { if (lx_strfwx(&s, &p->base(), n)) throw AllocError(); return *this; }



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
          @defgroup Ssearch Search functions
          @{
         ********************************************************************/

        /** Find the \a n th index of character \a c.
         *
         * @see lx_strindex()
         *
         * \returns -1 if the character could not be found.
         */
        inline long index(char c, unsigned n) throw()
        { return lx_strindex(&s, c, n); }

        /** Find the \a n th index of any character in set \a set (which has
         * length \a setl).
         *
         * @see lx_strindex()
         *
         * \returns -1 if no such character could be found.
         */
        inline long indexSet(const char *set, unsigned setl, unsigned n) throw()
        { return lx_strsindex(&s, set, setl, n); }


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
            { return !lx_strcmp(&s, s2); }

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
            { return !lx_strscmp(&s, s2); }

        /** Compare with another String.
         *
         * \retval true strings match
         * \retval false they do not.
         *
         * \note boolean style return value, not C style.
         *
         * @see lx_strcmp()
         */
        inline bool compare(const String& s2) throw()
        { return !lx_strcmp(&s, &s2.base()); }

        /** Compare strings case insensitively.
         *
         * \retval true strings match
         * \retval false they do not.
         *
         * \note boolean style return value, not C style.
         *
         * @see lx_stricmp()
         */
        inline bool icompare(const String &s2) throw()
        { return !lx_stricmp(&s, &s2.s); }

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
            return !lx_stricmp(&s, &stmp);
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
    /** Directly assign basea structure to \a *s_from. */
    StringDirect(lx_s *s_from)
    { s = *s_from; }

    /** Use \ref assign() to initialize. */
    StringDirect()
    { }

    /** Base \c lx_s memory will not be freed. */
    ~StringDirect()
    { }

    /* Directly assign the base \c lx_s to \a s_from . */
    inline void assign(lx_s *s_from)
    { s = *s_from; }

    /** Not allocated -- take care that this never needs to realloc! */
    inline void assign(char *s_from, int len)
    { s.s = s_from; s.len = s.alloc = len; }
};


} // namespace lx

#endif // _LXISTRING_HPP
