#include <unistd.h>

void printer(const char *s, int len) {
    write(1, s, len);
}

struct Sb {
    template<int N>
    Sb(const char (&s)[N])
    {
        printer(s, N-1);
    };
};


int main() {

    Sb x[] = { "DirectExt 10.1!\n" };         // okay
    Sb y[] = (Sb []) { "DirectExt 10.1!\n" }; // error

    return 0;
}
