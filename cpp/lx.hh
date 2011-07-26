#include <stdexcept>


#if 0 /*** PORTING STATUS **************************************************/

//- ignore
//! done
//? irrelevant?

//? extern unsigned int lx_strlen(char *);
//? extern unsigned int lx_fstrout(void *, lx_s *);
//? extern unsigned int lx_setxbuf(unsigned int);
//? extern          int lx_strout(int, lx_s *);

//- extern char lx_alloc(lx_s *, unsigned int);  // XXX: offer preallocation?
//- extern char lx_realloc(lx_s *, unsigned int);
//- extern char lx_setalloc(lx_s *, unsigned int);
//- extern char lx_plusalloc(lx_s *, unsigned int);
//! extern char lx_strcopy(lx_s *, lx_s *);
//! extern char lx_strncopy(lx_s *, lx_s *, unsigned int);
//! extern char lx_strcat(lx_s *, lx_s *);
//! extern char lx_stradd(lx_s *, char *);
//! extern char lx_striadd(lx_s *, char *, unsigned int);
//! extern char lx_strset(lx_s *, char *);
//! extern char lx_striset(lx_s *, char *, unsigned int);
//! extern char lx_strnset(lx_s *, char *, unsigned int);
extern char lx_strinsert(lx_s *,char *,unsigned int,unsigned int,unsigned int);
extern char lx_straddulong(lx_s *, unsigned long, unsigned int);
extern char lx_straddlong(lx_s *, long, unsigned int);
//! extern char lx_cadd(lx_s *, char);
//! extern char lx_check0(lx_s *);
//! extern char lx_chop(lx_s *, unsigned int);
//! extern char lx_chomp(lx_s *, char *);
//! extern void lx_chomp_ws(lx_s *);
//! extern char lx_chompf(lx_s *s, char *);
//! extern char lx_chompf_ws(lx_s *);
//! extern char lx_strcmp(lx_s *, lx_s *);
//! extern char lx_strscmp(lx_s *, char *);
extern char lx_stricmp(lx_s *, lx_s *);
extern char lx_strlcmp(lx_s *, lx_s *);
extern char lx_strncmp(lx_s *, lx_s *, unsigned int);
extern char lx_strnicmp(lx_s *, lx_s *, unsigned int);
extern char lx_strnlcmp(lx_s *, lx_s *, unsigned int);
extern char lx_strnpcmp(char *, char *, unsigned int);
extern char lx_strnipcmp(char *, char *, unsigned int);
extern char lx_strnlpcmp(char *, char *, unsigned int);
extern char lx_strff(lx_s *, char **, char, unsigned int);
extern char lx_strfw(lx_s *, char **, unsigned int);
extern long lx_strindex(lx_s *, char, unsigned int);
extern long lx_strsindex(lx_s *, char *, unsigned int, unsigned int);
extern char lx_straddp(lx_s *, char *, ...);
extern char lx_strsetp(lx_s *, char *, ...);

//! extern char lx_getln(lx_s *, lx_gd *, unsigned char *, unsigned long);
//! extern char lx_getseg(lx_s *, lx_gd *, char *, unsigned char *, unsigned long);

//- extern void lx_free(lx_s *);
extern void lx_zfree(lx_s *); // TODO: wipe flag?
extern void lx_strnull(lx_s *);
extern void lx_strznull(lx_s *);
extern void lx_mirror(lx_s *, const lx_s *);
extern void lx_zero(lx_s *);
extern void lx_zeroa(lx_s *);
extern void lx_strrev(lx_s *);

extern char lx_lowerb(char);
extern char lx_upperb(char);
extern void lx_lowers(char *, unsigned int);
extern void lx_uppers(char *, unsigned int);
extern void lx_lowersp(char *, char *, unsigned int);
extern void lx_uppersp(char *, char *, unsigned int);
extern char lx_lowerstr(lx_s *, char *, unsigned int);
extern char lx_upperstr(lx_s *, char *, unsigned int);

extern int  lx_map();

extern void *lx_stroffer(lx_s *);

/* objects */

//- extern void *lx_new(void);
//- extern void  lx_destroy(void *);

/* arrays */

extern char lx_sa_add(lx_sa *, lx_s *);
extern char lx_sa_adds(lx_sa *, char *);
extern char lx_sa_alloc(lx_sa *, unsigned int);
extern char lx_sa_realloc(lx_sa *, unsigned int);
extern char lx_sa_setalloc(lx_sa *, unsigned int);

extern unsigned int lx_sa_setxbuf(unsigned int);

/* generic descriptors */

//- extern char lx_gdnew(lx_gd *, int, unsigned int);
extern void lx_gd2s(lx_s *, lx_gd *, unsigned int *);
extern char lx_read(lx_s *, lx_gd *, unsigned int);
extern int  lx_gdread(lx_s *, lx_gd *, int, unsigned int);
extern char lx_gdfill(lx_gd *);
extern char lx_gdicopy(lx_s *, lx_gd *, unsigned int);
extern char lx_gdiappend(lx_s *, lx_gd *, unsigned int);
//! extern char lx_gdputs(lx_gd *, const char *);  // Gd::put(char *)
extern char lx_gdputsn(lx_gd *, const char *, unsigned int);
extern char lx_gdputc(lx_gd *, const char);
//! extern char lx_gdstrput(lx_gd *, const lx_s *); // Gd::put(String)
//! extern char lx_gdflush(lx_gd *);
//- extern char lx_gdfree(lx_gd *);
extern char lx_gdaddulong(lx_gd *, unsigned long, unsigned int);
extern char lx_gdaddlong(lx_gd *, long, unsigned int);

#endif /*** END PORTING STATUS **********************************************/


namespace lx {

/****************************************************************************
 ***   BEGIN   **************************************************************
 ****************************************************************************/


extern "C" {
#include "lx_string.h"
}

class AllocError: public std::exception
{ const char *what() { return "Bad Allocation"; } };

// TODO: add errno checking/reporting
class ReadError: public std::exception
{ const char *what() { return "Read Error"; } };

class WriteError: public std::exception
{ const char *what() { return "Write Error"; } };

class UnderflowError: public std::exception
{ const char *what() { return "Underflow Error"; } };


class Gd;
class String;


/*** lx::String (LX Generic Data Buffer class) ******************************
 ****************************************************************************/

class String {

    public:
        lx_string s;

        /********************************************************************
          Constructors and destructors
         ********************************************************************/

        /*** [new] : [init this, basic form]
        */
        inline String() throw()
        { s.s = 0; }

        /*** [new] : lx_strset(this, src)
        */
        inline String(const char *src) throw(AllocError)
        { s.s = 0; copy(src); }

        /*** [new] : lx_striset(this, src, n)
        */
        inline String(const char *src, unsigned int n) throw(AllocError)
        { s.s = 0; copy(src, n); }

        /*** [destroy] : lx_free(this)
        */
        inline ~String() throw()
        { if (s.s) lx_free(&s); }



        /********************************************************************
          convenience for underlying data structures
         ********************************************************************/

        inline lx_s& base()
        { return s; }

        inline unsigned int len()
        { return s.len; }

        inline char *ptr()
        { return s.s; }



        /********************************************************************
          String assignment functions
         ********************************************************************/

        /*** strnset : lx_strnset(this, src, maxlen)
        */
        inline void strnset(const char *src, unsigned int maxlen) throw(AllocError)
        {
            if (lx_strnset(&s, (char *)(void *)src, maxlen))
                throw AllocError();
        }


        /*** copy : lx_strcopy(this, src)
        */
        inline void copy(const String& src) throw(AllocError)
        {
            if (lx_strcopy(&s, const_cast<lx_s*>(&src.s) ))
                throw AllocError();
        }


        /*** copy : lx_strncopy(this, src, maxlen)
        */
        inline void copy(const String& src, unsigned int maxlen) throw(AllocError)
        {
            if (lx_strncopy(&s, const_cast<lx_s*>(&src.s), maxlen))
                throw AllocError();
        }


        /*** copy : lx_strset(this, src)
        */
        inline void copy(const char *src) throw(AllocError)
        {
            if (lx_strset(&s, const_cast<char*>(src) )) // TODO: fix const in lxlib
                throw AllocError();
        }


        /*** copy : lx_striset(this, src, n)
        */
        inline void copy(const char *src, unsigned int n) throw(AllocError)
        {
            if (lx_striset(&s, const_cast<char*>(src), n))
                throw AllocError();
        }


        /********************************************************************
          String append functions
         ********************************************************************/

        /*** append : lx_strcat(this, src)
        */
        inline void append(const String& src) throw(AllocError)
        {
            if (lx_strcat(&s, const_cast<lx_s*>(&src.s) ))
                throw AllocError();
        }

        /*** append : lx_striadd(this, src, maxlen||src.len())
        */
        inline void append(const String& src, unsigned int maxlen) throw(AllocError)
        {
            if (maxlen > src.s.len)
                maxlen = src.s.len;

            if (lx_striadd(&s, src.s.s, maxlen))
                throw AllocError();
        }


        /*** append : lx_striadd(this, src, len)
        */
        inline void append(const char *src, unsigned int len) throw(AllocError)
        {
            if (lx_striadd(&s, const_cast<char*>(src), len))
                throw AllocError();
        }

        /*** append : lx_stradd(this, src)
        */
        inline void append(const char *src) throw(AllocError)
        {
            if (lx_stradd(&s, const_cast<char*>(src) ))
                throw AllocError();
        }

        /*** append : lx_cadd(this, src)
        */
        inline void append(char c) throw(AllocError)
        {
            if (lx_cadd(&s, c ))
                throw AllocError();
        }


        /********************************************************************
          Interfacing with non-lx functions
         ********************************************************************/

        /*** check0 : lx_check0(this)
        */
        inline void check0() throw(AllocError)
        {
            if (lx_check0(&s))
                throw AllocError();
        }



        /********************************************************************
          Data manipulation functions
         ********************************************************************/


        /*** chop : lx_chop(this, n)
         */
        inline void chop(unsigned int n) throw (UnderflowError)
            { if (lx_chop(&s, n)) throw UnderflowError(); }


        /*** chomp : lx_chomp(this, cstr)
         */
        inline void chomp(char *cstr) throw (AllocError)
            { if (lx_chomp(&s, cstr)) throw AllocError(); }

        /*** chompf : lx_chompf(this, cstr)
         */
        inline void chompf(char *cstr) throw (AllocError)
            { if (lx_chompf(&s, cstr)) throw AllocError(); }

        /*** chomp : lx_chomp_ws(this)
         */
        inline void chomp() throw ()
            { lx_chomp_ws(&s); }

        /*** lx_chompf_ws(this) */
        inline void chompf() throw (AllocError)
            { if (lx_chompf_ws(&s)) throw AllocError(); }


        /** returns true if strings match; false if not */
        inline bool compare(lx_s *s2) throw()
            { return !lx_strcmp(&s, s2); }

        /** returns true if strings match; false if not */
        inline bool compare(char *s2) throw()
            { return !lx_strscmp(&s, s2); }



    protected:
};






/*** lx::Gd (LX Generic Descriptor) class ***********************************
 ****************************************************************************/
class Gd {

    public:
        lx_gd gd;
        bool eof;

        Gd(int fd, unsigned int blocksize = 0) throw(AllocError);
        ~Gd() throw();

        /********************************************************************
          Constructors and destructors
         ********************************************************************/

        /*********** construct
         *
         * init this.gd with file descriptor [fd], and optionally an explicit [blocksize]
         * autoflush defaults to false
         *
         * exceptions:
         *   - AllocError
         *
         ***********/
        inline Gd(int fd, unsigned int blocksize) throw(AllocError)
        {
            _autoflush = false;
            eof = false;

            if (lx_gdnew(&gd, fd, blocksize))
                throw AllocError();
        }

        /*********** destroy
         *
         * free this.gd
         ***********/
        inline ~Gd() throw()
        {
            if (_autoflush) flush();
            lx_gdfree(&gd);
        }


        /********************************************************************
          State changing functions
         ********************************************************************/

        /** Set autoflush property to val
         *
         * Return old autoflush value.
         */
        inline bool autoflush(bool val) throw()
        {
            bool oaf = _autoflush;
            _autoflush = val;
            return oaf;
        }

        /** Return autoflush value */
        inline bool autoflush() throw()
        { return _autoflush; }

        /** lx_gdflush(this) */
        inline void flush() throw()
        { lx_gdflush(&gd); }


        /********************************************************************
          GD seeking and searching functions
         ********************************************************************/

        /**
         * Get a segment, and place it into s.  Maximum segment length to
         * retrieve is maxlen.  Returns true if EOS was reached, false
         * otherwise.
         */
        inline bool getseg(String& s, char c, unsigned long maxlen) throw(AllocError, ReadError)
        {
            unsigned char match;
            if (!lx_getseg(&s.s, &gd, &c, &match, maxlen)) {
                if (!match) eof = true;
                return (match == MATCH_OK);
            }

            throw AllocError(); // TODO: check errno, maybe throw ReadError
        }

        /**
         * Same as getseg(), but c is '\n'.
         */
        inline bool getln(String& s, unsigned long maxlen)          throw(AllocError, ReadError)
        {
            unsigned char match;
            if (!lx_getln(&s.s, &gd, &match, maxlen)) {
                if (!match) eof = true;
                return (match == MATCH_OK);
            }

            throw AllocError(); // TODO: check errno, maybe throw ReadError
        }


        /********************************************************************
          GD output functions

          // TODO: templatized variable-argument put() version using lx_map()
         ********************************************************************/

        /**
         * lx_gdstrput(this, S.base())
         */
        inline void put(String& S) throw(WriteError)
        {
            if ( lx_gdstrput( &gd, &S.base() ) )
                throw WriteError();
        }

        /**
         * lx_gdputs(this, c_str)
         */
        inline void put(char *c_str) throw(WriteError)
        {
            if ( lx_gdputs(&gd, c_str) )
                throw WriteError();
        }

    protected:
        bool _autoflush;
};



/****************************************************************************
 ***   END   ****************************************************************
 ****************************************************************************/

} // namespace lx
