#ifndef _LX_STRING_H
#define _LX_STRING_H

#include "lxi_strbuf.h"
#include "lxi_strdef.h"
#include "lxi_gendesc.h"
#include "lxi_gendef.h"

#include <stdarg.h>

/** @file lx_string.h */

/** @defgroup lxs_Umbrella lx_s Operations
 * @{
 */

    /** @defgroup Misc Miscellaneous Helper Functions
     * @{
     */
extern unsigned int lx_strlen(const char *);
extern unsigned int lx_fstrout(void *, lx_s *);
extern unsigned int lx_setxbuf(unsigned int);
extern          int lx_strout(int, lx_s *);
    /** @}
     *
     * @defgroup Alloc lx_s Allocation and Insertion
     * @{
     */
extern char lx_alloc(lx_s *, unsigned int);
extern char lx_realloc(lx_s *, unsigned int);
extern char lx_setalloc(lx_s *, unsigned int);
extern char lx_plusalloc(lx_s *, unsigned int);
extern char lx_strcopy(lx_s *, const lx_s *);
extern char lx_strncopy(lx_s *, const lx_s *, unsigned int);
extern char lx_strcat(lx_s *, const lx_s *);
extern char lx_stradd(lx_s *, const char *);
extern char lx_striadd(lx_s *, const char *, unsigned int);
extern char lx_strset(lx_s *, const char *);
extern char lx_striset(lx_s *, const char *, unsigned int);
extern char lx_strnset(lx_s *, const char *, unsigned int);
extern void lx_strsetdirect(lx_s *, const char *);
extern char lx_strinsert(lx_s *,const char *,unsigned int,unsigned int,unsigned int);
extern char lx_straddulong(lx_s *, unsigned long, unsigned int);
extern char lx_straddlong(lx_s *, long, unsigned int);
extern char lx_cadd(lx_s *, char);
extern char lx_strprintf(lx_s *dest, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
extern char lx_strvprintf(lx_s *dest, const char *fmt, va_list ap);
    /** @}
     *
     * @defgroup CInterface Interfacing with C Strings
     * @{
     */
extern char lx_check0(lx_s *);
extern char lx_post0(lx_s *);
extern const char *lx_cstr(lx_s *);
extern const char *lx_cstr_tryconst(lx_s *);
extern void *lx_stroffer(const lx_s *);

    /** @}
     *
     * @defgroup Prune Pruning
     * @{
     */
extern char lx_chop(lx_s *, unsigned int);
extern char lx_chomp(lx_s *, char *);
extern void lx_chomp_ws(lx_s *);
extern char lx_chompf(lx_s *s, char *);
extern char lx_chompf_ws(lx_s *);
    /** @}
     *
     * @defgroup Compare Comparison
     * @{
     */
extern char lx_strcmp(const lx_s *, const lx_s *);
extern char lx_strscmp(const lx_s *, const char *);
extern char lx_stricmp(const lx_s *, const lx_s *);
extern char lx_strlcmp(const lx_s *, const lx_s *);
extern char lx_strncmp(const lx_s *, const lx_s *, unsigned int);
extern char lx_strnicmp(const lx_s *, const lx_s *, unsigned int);
extern char lx_strnlcmp(const lx_s *, const lx_s *, unsigned int);
extern char lx_strnpcmp(const char *, const char *, unsigned int);
extern char lx_strnipcmp(const char *, const char *, unsigned int);
extern char lx_strnlpcmp(const char *, const char *, unsigned int);
    /** @}
     *
     * @defgroup Find Searching and Indexing
     * @{
     */
extern char lx_strff(lx_s *, char **, char, unsigned int);
extern char lx_strfw(lx_s *, char **, unsigned int);
extern char lx_strffx(lx_s *, lx_s *, char, unsigned int);
extern char lx_strfwx(lx_s *, lx_s *, unsigned int);
extern long lx_strindex(lx_s *, char, unsigned int);
extern long lx_strsindex(lx_s *, const char *, unsigned int, unsigned int);
extern char lx_straddp(lx_s *, char *, ...);
extern char lx_strsetp(lx_s *, char *, ...);
    /** @}
     *
     * @defgroup GDInterface Interfacing with lx_gd Objects
     * @{
     */
extern char lx_getln(lx_s *, lx_gd *, unsigned char *, unsigned long);
extern char lx_getseg(lx_s *, lx_gd *, char *, unsigned char *, unsigned long);
    /** @}
     *
     * @defgroup Destroy Destructors
     * @{
     */
extern void lx_free(lx_s *);
extern void lx_zfree(lx_s *);
extern void lx_strnull(lx_s *);
extern void lx_strznull(lx_s *);
extern void lx_mirror(lx_s *, const lx_s *);
extern void lx_zero(lx_s *);
extern void lx_zeroa(lx_s *);
extern void lx_strrev(lx_s *);
    /** @}
     *
     * @defgroup Case Case Manipulation
     * @{
     */
extern char lx_lowerb(char);
extern char lx_upperb(char);
extern void lx_lowers(char *, unsigned int);
extern void lx_uppers(char *, unsigned int);
extern void lx_lowersp(char *, const char *, unsigned int);
extern void lx_uppersp(char *, const char *, unsigned int);
extern char lx_lowerstr(lx_s *, const char *, unsigned int);
extern char lx_upperstr(lx_s *, const char *, unsigned int);
    /** @}
     *
     * @defgroup Map Mapping Operations
     * @{
     */
extern int  lx_map();

    /** @}
     *
     * @defgroup Object Using lx_s as Objects
     * @{
     */

extern lx_s *lx_new(void);
extern void  lx_destroy(lx_s *);

    /** @} */
/**************************************************//**
 * @}
 * @defgroup lxsa_Umbrella Arrays (lx_sa)
 * @{
 ******************************************************/

     /**
     * @defgroup ArrayOps Array Operations
     * @{
     */

extern char lx_sa_add(lx_sa *, const lx_s *);
extern char lx_sa_addsa (lx_sa *dest, const lx_sa *src);
extern char lx_sa_adds(lx_sa *, const char *);
extern char lx_sa_adds0(lx_sa *, const char *);
extern char lx_sa_addpp (lx_sa *sa, const char *const *src);
extern char lx_sa_addppn(lx_sa *sa, const char *const *src, int n);
extern char lx_sa_alloc(lx_sa *, unsigned int);
extern char lx_sa_realloc(lx_sa *, unsigned int);
extern char lx_sa_setalloc(lx_sa *, unsigned int);
extern char lx_sa_plusalloc(lx_sa *sa, unsigned int elem);
extern void lx_sa_free(lx_sa *sa);
extern void lx_sa_zfree(lx_sa *sa);
extern void lx_sa_empty(lx_sa *sa);
extern void lx_sa_zempty(lx_sa *sa);
extern char lx_sa_post0(lx_sa *sa);
extern char lx_sa_each_post0(lx_sa *sa);
extern const char **lx_sa_each_post0_charpp(lx_sa *sa);
extern char lx_sa_add0(lx_sa *sa);
extern char lx_sa_to_charpp(lx_sa *sa, lx_s *dest);
extern char lx_sa_pop_back (lx_sa *sa, lx_s **destp);
extern char lx_sa_pop_index (lx_sa *sa, lx_s **destp, int index);
extern char lx_sa_pop_front(lx_sa *sa, lx_s **destp);

extern unsigned int lx_sa_setxbuf(unsigned int);

    /** @} */
/**************************************************//**
 * @}
 * @defgroup lxgd_Umbrella Generic Descriptors (lx_gd)
 * @{
 ******************************************************/

    /*
     * @defgroup GDOps Generic Descriptor Operations
     * @{
     */

extern char lx_gdnew(lx_gd *, int, unsigned int);
extern void lx_gd2s(lx_s *, lx_gd *, unsigned int *);
extern char lx_read(lx_s *, lx_gd *, unsigned int);
extern int  lx_gdread(lx_s *, lx_gd *, int, unsigned int);
extern char lx_gdfill(lx_gd *);
extern char lx_gdicopy(lx_s *, lx_gd *, unsigned int);
extern char lx_gdiappend(lx_s *, lx_gd *, unsigned int);
extern char lx_gdputs(lx_gd *, const char *);
extern char lx_gdputsn(lx_gd *, const char *, unsigned int);
extern char lx_gdputc(lx_gd *, const char);
extern char lx_gdstrput(lx_gd *, const lx_s *);
extern char lx_gdflush(lx_gd *);
extern char lx_gdfree(lx_gd *);
extern char lx_gdaddulong(lx_gd *, unsigned long, unsigned int);
extern char lx_gdaddlong(lx_gd *, long, unsigned int);

    /** @} */
/** @} */


#endif
