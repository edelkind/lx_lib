#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

unsigned int lx_strlen1(s)
	register char *s;
{
	register char *p;

	p = s;
	for (;;) {
		if (*p) {p++;} else {return (p-s);}
		if (*p) {p++;} else {return (p-s);}
		if (*p) {p++;} else {return (p-s);}
	}
}

unsigned int lx_strlen2(s)
	char *s;
{
	register char *p = s;
	register int i = 0;
	for (;;) {
		if (*p) {p++;i++;} else {return (i);}
		if (*p) {p++;i++;} else {return (i);}
		if (*p) {p++;i++;} else {return (i);}
	}
}

unsigned int lx_strlen3(s)
	register char *s;
{
	register char *p = s;

	for (;;) {
		if (!*p) return (p-s); ++p;
		if (!*p) return (p-s); ++p;
		if (!*p) return (p-s); ++p;
	}
}

void p_time (struct tms *start, struct tms *end) {
	long tick = sysconf(_SC_CLK_TCK);

	if (tick <= 0) {
		fprintf (stderr, "sysconf error: %s\n", strerror(errno));
		return;
	}

	fprintf (stderr, "u%7.2f\ns%7.2f\n", (end->tms_utime - start->tms_utime) /
			(double) tick, (end->tms_stime - start->tms_stime) /
			(double) tick);
}

#define SSTRING "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#define STRLEN_1() lx_strlen1(SSTRING)
#define STRLEN_2() lx_strlen2(SSTRING)
#define STRLEN_3() lx_strlen3(SSTRING)
#define STRLEN_4() strlen(SSTRING)

int main(void) {
	long int i;
	struct tms tstart, tend;

	times(&tstart);
	for (i = 0; i < 1000000; i++) {
		STRLEN_1();
	}
	times(&tend);

	fprintf (stderr, "strlen1: %d\n", STRLEN_1());
	p_time(&tstart, &tend);


	times(&tstart);
	for (i = 0; i < 1000000; i++) {
		STRLEN_2();
	}
	times(&tend);

	fprintf (stderr, "strlen2: %d\n", STRLEN_2());
	p_time(&tstart, &tend);

	times(&tstart);
	for (i = 0; i < 1000000; i++) {
		STRLEN_3();
	}
	times(&tend);

	fprintf (stderr, "strlen3: %d\n", STRLEN_3());
	p_time(&tstart, &tend);

	/* strlen() is in asm on linux */
	times(&tstart);
	for (i = 0; i < 1000000; i++) {
		STRLEN_4();
	}
	times(&tend);

	fprintf (stderr, "strlen4: %d\n", STRLEN_4());
	p_time(&tstart, &tend);

	return 0;
}
