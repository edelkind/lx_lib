#ifndef _LXIGD_HPP
#define _LXIGD_HPP

extern "C" {
#include <fcntl.h>
#include <errno.h>
#include <string.h>
}

namespace lx {

/************************************************************************//**
 *** lx::Gd (LX Generic Descriptor) class
 ****************************************************************************/
class Gd {
    /**
     * @defgroup GDumbrella lx::GD components
     * @{
     */

    public:
        lx_gd gd;
        bool eof;

        /****************************************************************//**
          @defgroup GDnew Constructors and destructors
          @{
         ********************************************************************/

        /** construct.
         *
         * init this.gd with file descriptor [fd], and optionally an explicit [blocksize].
         * @a autoflush defaults to false.
         * @a separator defaults to @c '\\n' .
         *
         * exceptions:
         *   - AllocError
         *
         * @see lx_gdnew()
         *
         ***********/
        inline Gd(int fd=-1, unsigned int blocksize=0, bool autoflush=false) throw(AllocError)
        {
            _autoflush = autoflush;
            eof = false;
            _separator = '\n';

            if (lx_gdnew(&gd, fd, blocksize))
                throw AllocError();
        }

        /** destroy.
         *
         * free this.gd.  If autoflush is true, then also flush it.
         *
         * @see flush()
         * @see lx_gdfree()
         ***********/
        inline ~Gd() throw()
        {
            if (_autoflush) flush();
            lx_gdfree(&gd);
        }


        /** @} */
        /****************************************************************//**
          @defgroup GDconvenient Convenience for underlying data structures
          @{
         ********************************************************************/

        /** @returns underlying gd */
        inline lx_gd& base()
        { return gd; }

        /** @returns underlying fd */
        inline int fd()
        { return gd.fd; }

        /** @} */
        /****************************************************************//**
          @defgroup GDstate State changing functions
          @{
         ********************************************************************/

        /** Set the descriptor that the underlying gd uses.
         * \returns the old fd value.
         */
        inline int setFd(int newfd) throw()
        {
            int oldfd = gd.fd;
            gd.fd = newfd;
            return oldfd;
        }

        /** Set autoflush property to val.
         *
         * Return old autoflush value.
         */
        inline bool autoflush(bool val) throw()
        {
            bool oaf = _autoflush;
            _autoflush = val;
            return oaf;
        }

        /** Return autoflush value. */
        inline bool autoflush() throw()
        { return _autoflush; }

        /** Set separator property to val.
         *
         * Return old separator value.
         */
        inline bool separator(char val) throw()
        {
            char os = _separator;
            _separator = val;
            return os;
        }

        /** Return separator value. */
        inline bool separator() throw()
        { return _separator; }

        /**
         * lx_gdflush(this).
         * @see lx_gdflush()
         */
        inline void flush() throw(WriteError)
        { if (lx_gdflush(&gd)) throw WriteError(); }

        /** Set blocking status of the descriptor.
         */
        inline void blocking(bool value)
        {
            int oflags, nflags, rv;

            oflags = fcntl(gd.fd, F_GETFL);
            if (!value) nflags = oflags | O_NONBLOCK;
            else        nflags = oflags & (~O_NONBLOCK);
            if (oflags == nflags)
                return;

            rv = fcntl(gd.fd, F_SETFL, nflags);
            if (rv < 0) {
                throw SystemError(strerror(errno));
            }
        }


        /** @} */
        /****************************************************************//**
          @defgroup GDsearch GD seeking and searching functions
          @{
         ********************************************************************/

        /**
         * Get a segment, and place it into s.  Maximum segment length to
         * retrieve is maxlen.
         *
         * Returns true if EOS was reached, false otherwise.
         *
         * @see lx_getseg()
         */
        inline bool getseg(String *s, char c, unsigned long maxlen) throw(AllocError, ReadError)
        {
            unsigned char match;
            if (!lx_getseg(&s->s, &gd, &c, &match, maxlen)) {
                if (!match) eof = true;
                return (match == MATCH_OK);
            }

            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return false;

            throw AllocError(); /// \todo check errno, maybe throw ReadError
        }

        /**
         * Same as getseg(), but c is the default \ref separator.
         *
         * @see lx_getln()
         */
        inline bool getln(String *s, unsigned long maxlen)          throw(AllocError, ReadError)
        {
            unsigned char match;
            if (!lx_getseg(&s->s, &gd, &_separator, &match, maxlen)) {
                if (!match) eof = true;
                return (match == MATCH_OK);
            }

            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return false;

            throw AllocError(); /// \todo check errno, maybe throw ReadError
        }

        /** @} */
        /****************************************************************//**
          @defgroup GDout GD output functions
          @{

          \todo templatized variable-argument put() version using lx_map()
         ********************************************************************/

        /**
         * lx_gdstrput(this, S.base()).
         *
         * @see lx_gdstrput()
         */
        inline void put(const String& S) throw(WriteError)
        { put(S.s); }

        /**
         * lx_gdstrput(this, S.base()).
         *
         * @see lx_gdstrput()
         */
        inline void put(const lx_s& s) throw(WriteError)
        {
            if ( lx_gdstrput( &gd, &s ) )
                throw WriteError();
        }

        /**
         * lx_gdputs(this, c_str).
         *
         * @see lx_gdputs()
         */
        inline void put(const char *c_str) throw(WriteError)
        {
            if ( lx_gdputs(&gd, c_str) )
                throw WriteError();
        }

        /**
         * lx_gdputc(this, c).
         *
         * @see lx_gdputc()
         */
        inline void put(char c) throw(WriteError)
        {
            if ( lx_gdputc(&gd, c) )
                throw WriteError();
        }

        /**
         * lx_gdstrput(this, S.base()), but appends the default \ref separator.
         *
         * @see lx_gdstrput()
         */
        inline void putln(const String& S) throw(WriteError)
        { put(S.s); put(_separator); }

        /**
         * lx_gdstrput(this, S.base()), but appends the default \ref separator.
         *
         * @see lx_gdstrput()
         */
        inline void putln(const lx_s& s) throw(WriteError)
        {
            if ( lx_gdstrput( &gd, &s ) )
                throw WriteError();
            put(_separator);
        }

        /**
         * lx_gdputs(this, c_str), but appends the default \ref separator.
         *
         * @see lx_gdputs()
         */
        inline void putln(const char *c_str) throw(WriteError)
        {
            if ( lx_gdputs(&gd, c_str) )
                throw WriteError();
            put(_separator);
        }

        /** Add unsigned num with base base.
         * @see: lx_gdaddulong()
         */
        inline void putulong(unsigned long num,
                             unsigned int base=10) throw(AllocError)
        {
            if (lx_gdaddulong(&gd, num, base))
                throw WriteError();
        }

        /** Add signed num with base base.
         * @see: lx_gdaddlong()
         */
        inline void putlong(long num,
                            unsigned int base=10) throw(AllocError)
        {
            if (lx_gdaddlong(&gd, num, base))
                throw WriteError();
        }

        /** @} */

    protected:
        bool _autoflush;
        char _separator;

    /** @} */
};


} // namespace lx


#endif // _LXIGD_HPP
