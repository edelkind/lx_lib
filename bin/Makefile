include Makefile.sets

LX_OBJ          = $(LX_SRC:.c=.o)
LX_LIB          = liblx.a
LX_DIR          = ../lib

SRC             = catline.c \
                  catlinegd.c \
                  catlinegdrev.c \
                  cat_gdemu.c \
                  gdtest.c \
                  testmemf.c \
                  testmemfr.c \

OBJ             = ptime.o rtime.o
BIN             = $(SRC:.c=)

CFLAGS         += -I$(LX_DIR) $(DFLAGS)
LDFLAGS        += -L$(LX_DIR) -llx

.c.o:
	$(CC) -c $< $(CFLAGS)
	
all: bin

rebin: binclean bin

remake: clean all

bin: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $@.c $(OBJ) $(LDFLAGS)

lean:
	rm -f core $(LX_OBJ) $(OBJ)

libclean:
	rm -f $(LX_LIB)

binclean:
	rm -f $(BIN)

clean: lean binclean

distclean: clean
	@echo ""
	@echo "note: distclean is the same as clean"

install: all installbin

installbin:
	cp $(BIN) $(HOME)/bin/

