#include <iostream>
#include <string>
using namespace std;


extern "C" {
    void p_time (void* t1, void* t2);
    void times(void* t);

    struct tms {
        long tms_utime;  /* user time */
        long tms_stime;  /* system time */
        long tms_cutime; /* user time of children */
        long tms_cstime; /* system time of children */
    };

    struct tms tstart, tend;

}


int main()
{
    string buf;

    cout.sync_with_stdio(false);

    times(&tstart);

    try {
        while (getline(cin, buf))
            cout << buf << '\n';
    } catch (int e) {
        cerr << "Exception " << e << endl;
        return 1;
    }

    cout.flush();

    times(&tend);
    p_time(&tstart, &tend);

    return 0;
}
