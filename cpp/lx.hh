#include <stdexcept>

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


class Gd;
class String;


/*** lx::String (LX Generic Data Buffer class) ******************************
 ****************************************************************************/

class String {

    public:
        lx_string s;

        String()                                throw();
        String(const char *src)                 throw(AllocError);
        String(const char *src, unsigned int n) throw(AllocError);
        ~String() throw();

        void striset(const char *src, unsigned int n) throw(AllocError);
        void strnset(const char *src, unsigned int n) throw(AllocError);

    protected:
};

inline String::String() throw()
{ s.s = 0; }

inline String::String(const char *src) throw(AllocError)
{
    if (lx_strset(&s, (char *)(void *)src)) // TODO: fix const in lxlib
        throw AllocError();
}

inline String::String(const char *src, unsigned int n) throw(AllocError)
{
    striset(src, n);
}

inline String::~String() throw()
{
    if (s.s) lx_free(&s);
}


inline void String::striset(const char *src, unsigned int n) throw(AllocError)
{
    if (lx_striset(&s, (char *)(void *)src, n))
        throw AllocError();
}

inline void String::strnset(const char *src, unsigned int n) throw(AllocError)
{
    if (lx_strnset(&s, (char *)(void *)src, n))
        throw AllocError();
}




/*** lx::Gd (LX Generic Descriptor) class ***********************************
 ****************************************************************************/
class Gd {

    public:
        lx_gd gd;
        bool eof;

        Gd(int fd, unsigned int blocksize = 0) throw(AllocError);
        ~Gd() throw();

        bool autoflush(bool val) throw();
        bool autoflush()         throw();
        void flush()             throw();

        bool getln(String& s, unsigned long maxlen)          throw(AllocError, ReadError);
        bool getseg(String& s, char c, unsigned long maxlen) throw(AllocError, ReadError);

        // TODO: templatized variable-argument put() version using lx_map()
        void put(String& s)     throw(WriteError);
        void put(char *s)       throw(WriteError);

    protected:
        bool _autoflush;
};


/*********** construct
 * init this.gd with file descriptor [fd], and optionally an explicit [blocksize]
 * autoflush defaults to false
 *
 * exceptions:
 *   - AllocError
 *
 ***********/
inline Gd::Gd(int fd, unsigned int blocksize) throw(AllocError)
{
    _autoflush = false;
    eof = false;

    if (lx_gdnew(&gd, fd, blocksize))
        throw AllocError();
}

/*********** destroy
 * free this.gd
 ***********/
inline Gd::~Gd() throw()
{
    if (_autoflush) flush();
    lx_gdfree(&gd);
}


inline bool Gd::autoflush(bool val) throw()
{
    bool oaf = _autoflush;
    _autoflush = val;
    return oaf;
}

inline void Gd::flush() throw()
{ lx_gdflush(&gd); }

inline bool Gd::getln(String& s, unsigned long maxlen)          throw(AllocError, ReadError)
{
    unsigned char match;
    if (!lx_getln(&s.s, &gd, &match, maxlen)) {
        if (!match) eof = true;
        return (match == MATCH_OK);
    }

    throw AllocError(); // TODO: check errno, maybe throw ReadError
}

inline bool Gd::getseg(String& s, char c, unsigned long maxlen) throw(AllocError, ReadError)
{
    unsigned char match;
    if (!lx_getseg(&s.s, &gd, &c, &match, maxlen)) {
        if (!match) eof = true;
        return (match == MATCH_OK);
    }

    throw AllocError(); // TODO: check errno, maybe throw ReadError
}


inline void Gd::put(String& s) throw(WriteError)
{
    if (lx_gdstrput(&gd, &s.s))
        throw WriteError();
}

inline void Gd::put(char *s) throw(WriteError)
{
    if (lx_gdputs(&gd, s))
        throw WriteError();
}


/****************************************************************************
 ***   END   ****************************************************************
 ****************************************************************************/

} // namespace lx