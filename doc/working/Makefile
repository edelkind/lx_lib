.SUFFIXES: .htmp .html .inc

FILES =   index.htmp \
          status.htmp \
          func_lx_alloc.htmp \
          func_lx_cadd.htmp \
          func_lx_check0.htmp \
          func_lx_chop.htmp \
          func_lx_chomp.htmp \
          func_lx_chomp_ws.htmp \
          func_lx_chompf.htmp \
          func_lx_free.htmp \
          func_lx_zfree.htmp \

INCLUDE = head.inc \
          foot.inc \
          refs.inc \
          refext.inc \
          defines.inc \

VPATH =   ..

OBJ =     $(FILES:.htmp=.html)

INSTALLDIR = /usr/public/file/0/docs/lx/

.htmp.html: $(INCLUDE)
	chpp -o ../$@ $<

all: $(OBJ)

public: all
	cd .. && cp $(OBJ) $(INSTALLDIR)

clean:
	cd .. && rm -f $(OBJ)

remake: clean all
