# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
# NOTE: Don't forget that in the libtool distribution, files in this
# directory are distributed by the demo_distfiles variable in the top
# level Makefile.
AUTOMAKE_OPTIONS = no-dependencies foreign

LTDL_VERSION = -version-info 0:1:1

if INSTALL_LTDL
LTDL_FLAGS = $(LTDL_VERSION) -rpath $(libdir) 
include_HEADERS = ltdl.h
else
LTDL_FLAGS =
noinst_HEADERS = ltdl.h
endif

EXTRA_LTLIBRARIES = libltdl.la

lib_LTLIBRARIES = @LIBLIBS@
noinst_LTLIBRARIES = @NOINSTLIBS@

libltdl_la_SOURCES = ltdl.c
libltdl_la_LDFLAGS = $(LTDL_FLAGS) $(LIBADD_DL)

# rebuild the libtool script if needed
ltdl.lo: libtool
libtool: $(srcdir)/../ltconfig $(srcdir)/../ltmain.sh
	rm -f libtool
	cd .. && $(MAKE) libtool
	$(MAKE) -f ../Makefile srcdir=$(srcdir)/.. LIBTOOL_DEPS= libtool
