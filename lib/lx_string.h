#ifndef _LX_STRING_H
#define _LX_STRING_H

#include "lxi_strbuf.h"
#include "lxi_strdef.h"
#include "lxi_gendesc.h"
#include "lxi_gendef.h"

extern unsigned int lx_strlen();
extern unsigned int lx_fstrout();
extern unsigned int lx_setxbuf();
extern          int lx_strout();

extern char lx_alloc();
extern char lx_realloc();
extern char lx_setalloc();
extern char lx_plusalloc();
extern char lx_strcopy();
extern char lx_strncopy();
extern char lx_strcat();
extern char lx_stradd();
extern char lx_striadd();
extern char lx_strset();
extern char lx_striset();
extern char lx_strnset();
extern char lx_straddulong();
extern char lx_cadd();
extern char lx_check0();
extern char lx_chop();
extern char lx_chomp();
extern void lx_chomp_ws();
extern char lx_chompf();
extern char lx_chompf_ws();
extern char lx_strcmp();
extern char lx_strscmp();
extern char lx_stricmp();
extern char lx_strlcmp();
extern char lx_strncmp();
extern char lx_strnicmp();
extern char lx_strnlcmp();
extern char lx_strnpcmp();
extern char lx_strnipcmp();
extern char lx_strnlpcmp();
extern char lx_strff();
extern char lx_strfw();
extern long lx_strindex();
extern char lx_straddp(lx_s*a,char*b,...);
extern char lx_strsetp(lx_s*a,char*b,...);

extern char lx_getln();
extern char lx_getseg();

extern void lx_free();
extern void lx_zfree();
extern void lx_strnull();
extern void lx_strznull();
extern void lx_mirror();
extern void lx_zero();
extern void lx_zeroa();
extern void lx_strrev();

extern char lx_lowerb();
extern char lx_upperb();
extern void lx_lowers();
extern void lx_uppers();
extern void lx_lowersp();
extern void lx_uppersp();
extern char lx_lowerstr();
extern char lx_upperstr();

extern void *lx_stroffer();

/* arrays */

extern char lx_sa_add();
extern char lx_sa_adds();
extern char lx_sa_alloc();
extern char lx_sa_realloc();
extern char lx_sa_setalloc();

extern unsigned int lx_sa_setxbuf();

/* generic descriptors */

extern char lx_gdnew();
extern void lx_gd2s();
extern char lx_read();
extern char lx_gdfill();
extern char lx_gdicopy();
extern char lx_gdiappend();
extern char lx_gdputs();
extern char lx_gdputc();
extern char lx_gdstrput();
extern char lx_gdflush();
extern char lx_gdfree();

#endif
