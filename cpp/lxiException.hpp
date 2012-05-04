#ifndef _LXIEXCEPTION_HPP
# define _LXIEXCEPTION_HPP

extern "C" {
#include <string.h>
#include <stdlib.h>
}

#include <stdexcept>

namespace lx {

class lxException: public std::exception {};

class AllocError: public lxException
{ const char *what() const throw() { return "Bad Allocation"; } };

/// \todo add errno checking/reporting
class ReadError: public lxException
{ const char *what() const throw() { return "Read Error"; } };

class WriteError: public lxException
{ const char *what() const throw() { return "Write Error"; } };

class UnderflowError: public lxException
{ const char *what() const throw() { return "Underflow Error"; } };

class RangeError: public lxException
{ const char *what() const throw() { return "Range Error"; } };


class SystemError : public lxException {
    char *_cause;
    public:
    SystemError(const char *cause) {
        _cause = strdup(cause);
    }
    ~SystemError() throw() {
        free(_cause);
    }

    const char *what() const throw()
    { return _cause; }
};


} // namespace lx


#endif /* _LXIEXCEPTION_HPP */
