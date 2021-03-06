#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char s_time[21];

char *r_time (struct tms *start, struct tms *end) {
	long tick = sysconf(_SC_CLK_TCK);

	if (tick <= 0) {
		fprintf (stderr, "sysconf error: %s\n", strerror(errno));
		return (char *)0;
	}

	/*
	fprintf (stderr, "u%7.2f\ns%7.2f\n", (end->tms_utime - start->tms_utime) /
			(double) tick, (end->tms_stime - start->tms_stime) /
			(double) tick);
	*/
	sprintf (s_time, "%7.2fu %7.2fs", (end->tms_utime - start->tms_utime)
			/ (double) tick, (end->tms_stime - start->tms_stime)
			/ (double) tick);

	return (s_time);
}

