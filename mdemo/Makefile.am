# A brief demonstration of Libtool modules. -*-Makefile-*-
#
AUTOMAKE_OPTIONS = no-dependencies foreign

INCLUDES = -I$(srcdir)/../libltdl

EXTRA_DIST = acinclude.m4

lib_LTLIBRARIES = foo1.la libfoo2.la

foo1_la_SOURCES = foo1.c
foo1_la_LDFLAGS = $(LIBADD_M) -module -avoid-version

libfoo2_la_SOURCES = foo2.c
libfoo2_la_LDFLAGS = $(LIBADD_M) -module

noinst_HEADERS = foo.h

bin_PROGRAMS = mdemo mdemo.debug

../libltdl/libltdlc.la: ../libtool ../libltdl/libtool \
    $(srcdir)/../libltdl/ltdl.c $(srcdir)/../libltdl/ltdl.h
	(cd ../libltdl; $(MAKE) libltdlc.la)

# Create a version of mdemo that does dlopen.
mdemo_SOURCES = main.c
mdemo_LDFLAGS = -export-dynamic ## FIXME: remove this when libtool and libltdl
## handle dependencies of modules
## The quotes around -dlopen below fool automake into accepting it
mdemo_LDADD = ../libltdl/libltdlc.la "-dlopen" foo1.la "-dlopen" libfoo2.la
mdemo_DEPENDENCIES = ../libltdl/libltdlc.la foo1.la libfoo2.la

# Create an easier-to-debug version of mdemo.
mdemo_debug_SOURCES = $(mdemo_SOURCES)
mdemo_debug_LDFLAGS = @STATIC@ $(mdemo_LDFLAGS)
mdemo_debug_LDADD = $(mdemo_LDADD)
mdemo_debug_DEPENDENCIES = $(mdemo_DEPENDENCIES)
