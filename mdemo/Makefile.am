# A brief demonstration of Libtool modules. -*-Makefile-*-
#
AUTOMAKE_OPTIONS = no-dependencies foreign

INCLUDES = -I$(srcdir)/../libltdl

EXTRA_DIST = acinclude.m4

# A little hack to build libltdl in a subdirectory
libltdl/libltdl.la:
	-mkdir $(top_builddir)/libltdl
	(here=`pwd` && cd $(top_builddir)/libltdl && \
	$$here/../libltdl/configure --srcdir=$$here/../libltdl && \
	$(MAKE) all)
	
distclean-local:
	-rm -rf $(top_builddir)/libltdl

lib_LTLIBRARIES = libfoo1.la libfoo2.la

libfoo1_la_SOURCES = foo1.c
libfoo1_la_LDFLAGS = $(LIBADD_M) -module -avoid-versioning

libfoo2_la_SOURCES = foo2.c
libfoo2_la_LDFLAGS = $(LIBADD_M) -module

noinst_HEADERS = foo.h

bin_PROGRAMS = mdemo mdemo.debug

# Create a version of mdemo that does dlopen.
mdemo_SOURCES = main.c
mdemo_LDADD = libltdl/libltdl.la \
	$(LIBADD_M) # We won't need this when libltdl takes care of dependencies
mdemo_LDFLAGS = -dlopen libfoo1.la -dlopen libfoo2.la
mdemo_DEPENDENCIES = libltdl/libltdl.la libfoo1.la libfoo2.la

# Create an easier-to-debug version of mdemo.
mdemo_debug_SOURCES = main.c
mdemo_debug_LDADD = libltdl/libltdl.la
mdemo_debug_LDFLAGS = -static -dlopen libfoo1.la -dlopen libfoo2.la
mdemo_debug_DEPENDENCIES = libltdl/libltdl.la libfoo1.la libfoo2.la
