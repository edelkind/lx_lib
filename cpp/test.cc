#include <lx.hh>

using namespace lx;

int main() {
    Gd in(0, 4096);
    Gd *out = new Gd(1, 4096);
    Gd err(2);

    out->autoflush(true);
    err.autoflush(true);
    return 0;
}
