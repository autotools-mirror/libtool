# A brief demonstration of Libtool modules. -*-Makefile-*-
#
AUTOMAKE_OPTIONS = no-dependencies foreign

INCLUDES = -I$(srcdir)/../libltdl

EXTRA_DIST = acinclude.m4

lib_LTLIBRARIES = foo1.la libfoo2.la

foo1_la_SOURCES = foo1.c
foo1_la_LDFLAGS = $(LIBADD_M) -module -avoid-versioning

libfoo2_la_SOURCES = foo2.c
libfoo2_la_LDFLAGS = $(LIBADD_M) -module

noinst_HEADERS = foo.h

bin_PROGRAMS = mdemo mdemo.debug

../libltdl/libtest.la: ../libltdl/libtool \
    $(srcdir)/../libltdl/ltdl.c $(srcdir)/../libltdl/ltdl.h
	(cd ../libltdl; $(MAKE) libtest.la)

# Create a version of mdemo that does dlopen.
mdemo_SOURCES = main.c
mdemo_LDADD = ../libltdl/libtest.la
mdemo_LDFLAGS = -export-dynamic -dlopen foo1.la -dlopen libfoo2.la
mdemo_DEPENDENCIES = ../libltdl/libtest.la foo1.la libfoo2.la

# Create an easier-to-debug version of mdemo.
mdemo_debug_SOURCES = main.c
mdemo_debug_LDADD = ../libltdl/libtest.la
mdemo_debug_LDFLAGS = -static -export-dynamic \
	-dlopen foo1.la -dlopen libfoo2.la
mdemo_debug_DEPENDENCIES = ../libltdl/libtest.la foo1.la libfoo2.la
