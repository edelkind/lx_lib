DEFAULT: all
include ./Makefile.sets
include ./Makefile.ready
include ./Makefile.bin

SRC             = lx_alloc.c \
                  lx_cadd.c \
                  lx_check0.c \
                  lx_chop.c \
                  lx_cstr.c \
                  lx_free.c \
                  lx_gd2s.c \
                  lx_gdaddnum.c \
                  lx_gdappend.c \
                  lx_gdcopy.c \
                  lx_gdfill.c \
                  lx_gdflush.c \
                  lx_gdfree.c \
                  lx_gdnew.c \
                  lx_gdputc.c \
                  lx_gdputs.c \
                  lx_gdstrput.c \
                  lx_getln.c \
                  lx_map.c \
                  lx_mirror.c \
                  lx_objects.c \
                  lx_read.c \
                  lx_sa_add.c \
                  lx_sa_adds.c \
                  lx_sa_add0.c \
                  lx_sa_alloc.c \
                  lx_sa_free.c \
                  lx_sa_to_charpp.c \
                  lx_stradd.c \
                  lx_straddnum.c \
                  lx_straddp.c \
                  lx_strcat.c \
                  lx_strcmp.c \
                  lx_strcopy.c \
                  lx_strff.c \
                  lx_strfw.c \
                  lx_strlen.c \
                  lx_strnull.c \
                  lx_stroffer.c \
                  lx_strout.c \
                  lx_strrev.c \
                  lx_strset.c \
                  lx_strsetp.c \
				  lx_strinsert.c \
                  lx_zero.c \
                  lx_caseb.c \
                  lx_cases.c \
                  lx_strindex.c \
#                  lx_strnout.c

OBJ             = $(SRC:.c=.o)
LIB             = liblx.a

CFLAGS         += $(D_CFLAGS)

.c.o:
	./compile.sh $<
	
all: lib

ready-local: READYBANNER compile.sh makelib.sh

lib: ready-local $(LIB) lib$(LIB)

$(LIB): BINBANNER $(OBJ)
	./makelib.sh $@ $(OBJ)
#	$(AR) $@ $(OBJ)
#	$(RANLIB) $@

lib$(LIB): $(LIB)
	rm -f $@
	ln -s $(LIB) $@

relib: lean libclean lib

rebin: binclean bin

remake: clean all

lean:
	rm -f core $(OBJ)

libclean:
	rm -f BINBANNER $(LIB) lib$(LIB)

clean: lean libclean readyclean

distclean: clean
	@echo ""
	@echo "note: distclean is the same as clean"

install:
	@echo "minilib: install me not."

