extern (C) {
    void p_time (void* t1, void* t2);
    void times(void* t);

    struct tms {
        long tms_utime;  /* user time */
        long tms_stime;  /* system time */
        long tms_cutime; /* user time of children */
        long tms_cstime; /* system time of children */
    };

	tms tstart, tend;

}


import std.stdio;
import std.stream;

int main()
{
    char[] buf;

	times(&tstart);

    try {
        while (stdin.readln(buf))
            write(buf);
    } catch (StdioException e) {
        stderr.writefln("Exception: %s", e.toString());
    }

    times(&tend);
    p_time(&tstart, &tend);

    return 0;
}
