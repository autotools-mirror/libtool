# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
AUTOMAKE_OPTIONS = no-dependencies foreign

LTDL_VERSION = -version-info 0:1:0

ltdls.lo: ltdl.c libtool
	$(LTCOMPILE) -DUSE_DLPREOPEN -o $@ -c $<

lib_LTLIBRARIES = @LIBLIBS@
noinst_LTLIBRARIES = @NOINSTLIBS@
EXTRA_LTLIBRARIES = libltdl.la libltdls.la

if INSTALL_LTDL
LTDL_FLAGS = $(LTDL_VERSION) -rpath $(libdir)
include_HEADERS = ltdl.h
else
LTDL_FLAGS =
noinst_HEADERS = ltdl.h
endif

libltdl_la_SOURCES = ltdl.c ltdl.h
libltdl_la_LDFLAGS = $(LTDL_FLAGS) $(LIBADD_DL)
libltdls_la_LIBADD = ltdls.lo
libltdls_la_SOURCES = ltdl.h
libltdls_la_LDFLAGS = $(LTDL_FLAGS) $(LIBADD_DL) 

# rebuild the libtool script if needed
ltdl.lo: libtool
libtool: $(srcdir)/../ltconfig $(srcdir)/../ltmain.sh
	rm -f libtool
	cd .. && $(MAKE) libtool
	$(MAKE) -f ../Makefile srcdir=$(srcdir)/.. LIBTOOL_DEPS= libtool
