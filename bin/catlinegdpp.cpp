#include <stdexcept>
#include <lx.hh>

using namespace lx;

#define BLOCKSIZE 8192


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



int main() {
    Gd gdin(0, BLOCKSIZE);
    Gd gdout(1, BLOCKSIZE);
    Gd gderr(2);

    String buf;
    bool match; // unnecessary in this context

    gdout.autoflush(true); // flush on destroy
    gderr.autoflush(true); // endl still flushes, but anyway....

    times(&tstart);

    try {

	do {
            match = gdin.getln(buf, BLOCKSIZE);
            gdout.put(buf);
	} while (!gdin.eof);

    } catch (std::exception& e) {
        gderr.put((char *)"lx::getln: ");
        gderr.put((char *)(void *)e.what());
        gderr.put((char *)(void *)"\n");
        //gderr.put("lx::getln: ", e.what(), endl);
        // or, could offer: gderr.putchain << "lx::getln: " << e.what() << endl;

        return 1;
    }


    gdout.flush(); // just to take care of this before times()

    times(&tend);
    p_time (&tstart, &tend);

    return 0;
}
