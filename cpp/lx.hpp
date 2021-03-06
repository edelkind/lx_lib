#ifndef _LX_HPP
#define _LX_HPP


#if 0 /*** PORTING STATUS **************************************************/

//- ignore
//! done
//? irrelevant?

//? extern unsigned int lx_strlen(char *);
//? extern unsigned int lx_fstrout(void *, lx_s *);
//? extern unsigned int lx_setxbuf(unsigned int);
//? extern          int lx_strout(int, lx_s *);

//- extern char lx_alloc(lx_s *, unsigned int);  // XXX: offer preallocation?
//- extern char lx_realloc(lx_s *, unsigned int);
//- extern char lx_setalloc(lx_s *, unsigned int);
//- extern char lx_plusalloc(lx_s *, unsigned int);
//! extern char lx_strcopy(lx_s *, lx_s *);
//! extern char lx_strncopy(lx_s *, lx_s *, unsigned int);
//! extern char lx_strcat(lx_s *, lx_s *);
//! extern char lx_stradd(lx_s *, char *);
//! extern char lx_striadd(lx_s *, char *, unsigned int);
//! extern char lx_strset(lx_s *, char *);
//! extern char lx_striset(lx_s *, char *, unsigned int);
//! extern char lx_strnset(lx_s *, char *, unsigned int);
//! extern char lx_strinsert(lx_s *,char *,unsigned int,unsigned int,unsigned int);
//! extern char lx_straddulong(lx_s *, unsigned long, unsigned int);
//! extern char lx_straddlong(lx_s *, long, unsigned int);
//! extern char lx_cadd(lx_s *, char);
//! extern char lx_check0(lx_s *);
//! extern char lx_chop(lx_s *, unsigned int);
//! extern char lx_chomp(lx_s *, char *);
//! extern void lx_chomp_ws(lx_s *);
//! extern char lx_chompf(lx_s *s, char *);
//! extern char lx_chompf_ws(lx_s *);
//! extern char lx_strcmp(lx_s *, lx_s *);
//! extern char lx_strscmp(lx_s *, char *);
//! extern char lx_stricmp(lx_s *, lx_s *);
//! extern char lx_strlcmp(lx_s *, lx_s *);
extern char lx_strncmp(lx_s *, lx_s *, unsigned int);
extern char lx_strnicmp(lx_s *, lx_s *, unsigned int);
extern char lx_strnlcmp(lx_s *, lx_s *, unsigned int);
extern char lx_strnpcmp(char *, char *, unsigned int);
extern char lx_strnipcmp(char *, char *, unsigned int);
extern char lx_strnlpcmp(char *, char *, unsigned int);
//! extern char lx_strff(lx_s *, char **, char, unsigned int);
//! extern char lx_strfw(lx_s *, char **, unsigned int);
//! extern long lx_strindex(lx_s *, char, unsigned int);
//! extern long lx_strsindex(lx_s *, char *, unsigned int, unsigned int);
extern char lx_straddp(lx_s *, char *, ...);
extern char lx_strsetp(lx_s *, char *, ...);

//! extern char lx_getln(lx_s *, lx_gd *, unsigned char *, unsigned long);
//! extern char lx_getseg(lx_s *, lx_gd *, char *, unsigned char *, unsigned long);

//- extern void lx_free(lx_s *);
//! extern void lx_zfree(lx_s *); // TODO: wipe flag?
extern void lx_strnull(lx_s *);
extern void lx_strznull(lx_s *);
extern void lx_mirror(lx_s *, const lx_s *);
extern void lx_zero(lx_s *);
extern void lx_zeroa(lx_s *);
extern void lx_strrev(lx_s *);

//- extern char lx_lowerb(char);
//- extern char lx_upperb(char);
//! extern void lx_lowers(char *, unsigned int);
//! extern void lx_uppers(char *, unsigned int);
//- extern void lx_lowersp(char *, char *, unsigned int);
//- extern void lx_uppersp(char *, char *, unsigned int);
//! extern char lx_lowerstr(lx_s *, char *, unsigned int);
//! extern char lx_upperstr(lx_s *, char *, unsigned int);

extern int  lx_map();

//! extern void *lx_stroffer(lx_s *);
//! extern const char *lx_cstr(lx_s *);

/* objects */

//- extern void *lx_new(void);
//- extern void  lx_destroy(void *);

/* arrays */

//! extern char lx_sa_add(lx_sa *, lx_s *);
//! extern char lx_sa_adds(lx_sa *, char *);
extern char lx_sa_alloc(lx_sa *, unsigned int);
extern char lx_sa_realloc(lx_sa *, unsigned int);
extern char lx_sa_setalloc(lx_sa *, unsigned int);

extern unsigned int lx_sa_setxbuf(unsigned int);

/* generic descriptors */

//- extern char lx_gdnew(lx_gd *, int, unsigned int);
extern void lx_gd2s(lx_s *, lx_gd *, unsigned int *);
extern char lx_read(lx_s *, lx_gd *, unsigned int);
extern int  lx_gdread(lx_s *, lx_gd *, int, unsigned int);
//- extern char lx_gdfill(lx_gd *);
extern char lx_gdicopy(lx_s *, lx_gd *, unsigned int);
extern char lx_gdiappend(lx_s *, lx_gd *, unsigned int);
//! extern char lx_gdputs(lx_gd *, const char *);  // Gd::put(char *)
extern char lx_gdputsn(lx_gd *, const char *, unsigned int);
//! extern char lx_gdputc(lx_gd *, const char);
//! extern char lx_gdstrput(lx_gd *, const lx_s *); // Gd::put(String)
//! extern char lx_gdflush(lx_gd *);
//- extern char lx_gdfree(lx_gd *);
//! extern char lx_gdaddulong(lx_gd *, unsigned long, unsigned int);
//! extern char lx_gdaddlong(lx_gd *, long, unsigned int);

#endif /*** END PORTING STATUS **********************************************/



/****************************************************************************
 ***   BEGIN   **************************************************************
 ****************************************************************************/


extern "C" {
#include "lx_string.h"
}


#include "lxiException.hpp"
#include "lxiString.hpp"
#include "lxiStringArray.hpp"
#include "lxiGd.hpp"

//class Gd;
//class String;


namespace lx {
} // namespace lx



/****************************************************************************
 ***   END   ****************************************************************
 ****************************************************************************/

#include "lx_map.hpp"

#endif // _LX_HPP
