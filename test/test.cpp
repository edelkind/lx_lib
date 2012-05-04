#include <lx.hpp>
#include <unistd.h>
//#include <lx_map.hpp>

using namespace lx;

void printer(const char *s, int len) {
    write(1, s, len);
}

class Tstuff {
    public:
    template<int N>
    Tstuff(const char (&s)[N])
    {
        Tstuff(s, N-1);
    };

    Tstuff(const char *s, int len) {
        printer(s, len);
    }
};


int main() {
    Gd in(0, 4096);
    Gd *out = new Gd(1, 4096);
    Gd err(2);

    out->autoflush(true);
    err.autoflush(true);
    LX_CLIST_WRITE(err, "here ", 1, " come to save the day...\n");

    Tstuff x[] = { "arghle!\n" };
    return 0;
}
