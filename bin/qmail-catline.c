#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <unistd.h>
#include "substdio.h"
#include "readwrite.h"
#include "subfd.h"
#include "sgetopt.h"
#include "control.h"
#include "constmap.h"
#include "stralloc.h"
#include "fmt.h"
#include "str.h"
#include "scan.h"
#include "open.h"
#include "error.h"
#include "getln.h"
#include "auto_break.h"
#include "auto_qmail.h"
#include "auto_usera.h"

extern void p_time();

stralloc line = {0};

int main(void)
{
  int opt;
  int match;

  struct tms tstart, tend;

  times (&tstart);

  for (;;) {
    if (getln(subfdin,&line,&match,'\n') == -1) {
	    substdio_puts(subfderr, "error\n");
	    _exit (1);
    }
    stralloc_0 (&line);
    substdio_puts (subfdout, line.s);

    if (!match) break;
  }

  times (&tend);
  p_time (&tstart, &tend);

  _exit(0);
}
