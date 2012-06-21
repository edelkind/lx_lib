LX_DIR          = `pwd`
LX_LIBDIR       = $(LX_DIR)/lib
LX_BINDIR       = $(LX_DIR)/bin
LX_DOCDIR       = $(LX_DIR)/doc/working

all:
	cd $(LX_LIBDIR) && $(MAKE)

tests:
	cd $(LX_BINDIR) && $(MAKE)

docs: dox
#	doxygen
#	cd $(LX_DOCDIR) && $(MAKE)

dox: Doxyfile $(wildcard lib/*.[ch])
	doxygen

remake: clean all

clean:
	cd $(LX_LIBDIR) && $(MAKE) clean
	cd $(LX_BINDIR) && $(MAKE) clean
	cd $(LX_DOCDIR) && $(MAKE) clean

