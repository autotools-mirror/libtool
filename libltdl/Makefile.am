# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
# NOTE: Don't forget that in the libtool distribution, files in this
# directory are distributed by the demo_distfiles variable in the top
# level Makefile.
AUTOMAKE_OPTIONS = no-dependencies foreign

noinst_LTLIBRARIES = libltdl.la
libltdl_la_SOURCES = ltdl.c
libltdl_la_LDFLAGS = $(LIBADD_DL) 

include_HEADERS = ltdl.h

# rebuild the libtool script if needed
ltdl.lo: libtool
libtool: $(srcdir)/../ltconfig $(srcdir)/../ltmain.sh
	rm -f libtool
	cd .. && $(MAKE) libtool
	$(MAKE) -f ../Makefile srcdir=$(srcdir)/.. LIBTOOL_DEPS= libtool
