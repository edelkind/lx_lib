#ifndef _LX_MAP_HPP
#define _LX_MAP_HPP

extern "C" {
#include <stdio.h>
}

namespace lx {

extern "C" {
//#include "lx_string.h"
#include "lx_map.h"
#include <string.h>
}

//#include "lx.hpp"

#include <stdexcept>


struct Sbuf {
    const char *p;
    int l;
};

class ContainerError : public std::exception {};

class ContEnd {};

class ContBase {
    protected:
    bool valid;

    ContBase() : valid(true) {
    }

};

class Container : protected ContBase {
    int _vtype;
    union {
        lx_s lxs;
        unsigned long ul;
        long l;
    } val;

    private:
    inline void setstring(const char *s, unsigned long len)
    {
        val.lxs.s     = const_cast<char*>(s);
        val.lxs.len   = len;
        val.lxs.alloc = len;
    }

    public:
    template<int N>
    Container(const char (&s)[N]) : _vtype(LX_TYPE_STRING)
    {
        setstring(s, N-1);
        printf("array length: %d\n", N-1);
    };

    inline Container(char *s)
    {
        _vtype = LX_TYPE_STRING;
        setstring(s, strlen(s));
        printf("implicit length: %u\n", val.lxs.len);
    }

    inline Container(Sbuf &s)
    {
        _vtype = LX_TYPE_STRING;
        setstring(s.p, s.l);
    }

    inline Container(const char *s, unsigned long len)
    {
        _vtype = LX_TYPE_STRING;
        setstring(s, len);
        printf("explicit length: %lu\n", len);
    }

    inline Container(const lx_s *s)
    {
        _vtype = LX_TYPE_STRING;
        lx_mirror(&val.lxs, s);
    }

    inline Container(int i)
    {
        _vtype = LX_TYPE_INT;
        val.l = i;
    }

    inline Container(unsigned int i)
    {
        _vtype = LX_TYPE_UINT;
        val.ul = i;
    }

    inline Container(long i)
    {
        _vtype = LX_TYPE_LONG;
        val.l = i;
    }

    inline Container(unsigned long i)
    {
        _vtype = LX_TYPE_ULONG;
        val.ul = i;
    }


    inline Container(ContEnd e) {
        valid = false;
    }

    operator bool() {
        return valid;
    }

    void write(Gd& gd)
    {
        switch (_vtype) {
            case LX_TYPE_STRING:
                gd.put(val.lxs);
                break;
            case LX_TYPE_LONG:
            case LX_TYPE_INT:
                gd.putlong(val.l);
                break;
            case LX_TYPE_ULONG:
            case LX_TYPE_UINT:
                gd.putulong(val.l);
                break;
            default:
                throw ContainerError();
        }
    }

    void toString(String& lxs)
    {
        lxs.base().len = 0;
        appendString(lxs);
    }

    void appendString(String& s)
    {
        switch (_vtype) {
            case LX_TYPE_STRING:
                s.append(val.lxs);
                break;
            case LX_TYPE_LONG:
            case LX_TYPE_INT:
                s.addlong(val.l);
                break;
            case LX_TYPE_ULONG:
            case LX_TYPE_UINT:
                s.addulong(val.l);
                break;
            default:
                throw ContainerError();
        }
    }

};

inline void writeClist(Gd &gd, Container *Clist)
{
    while (*Clist)
        (*Clist++).write(gd);
};

inline void writeClist(String &s, Container *Clist)
{
    s.empty();
    while (*Clist)
        (*Clist++).appendString(s);
};

#define LX_CLIST_WRITE(dest, args...)  do {\
    Container cList[] = {args, ContEnd()}; \
    writeClist(dest, cList); \
} while (0)


} // lx::

#endif // _LX_MAP_HPP
