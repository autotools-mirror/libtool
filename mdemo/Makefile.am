# A brief demonstration of Libtool modules. -*-Makefile-*-
#
AUTOMAKE_OPTIONS = no-dependencies foreign

INCLUDES = -I$(srcdir)/../libltdl

EXTRA_DIST = acinclude.m4

lib_LTLIBRARIES = foo1.la libfoo2.la

foo1_la_SOURCES = foo1.c
foo1_la_LDFLAGS = -module -avoid-version

libfoo2_la_SOURCES = foo2.c
libfoo2_la_LDFLAGS = -module

noinst_HEADERS = foo.h

bin_PROGRAMS = mdemo mdemo.static

../libltdl/libltdl.la: ../libtool ../libltdl/libtool \
    $(srcdir)/../libltdl/ltdl.c $(srcdir)/../libltdl/ltdl.h
	(cd ../libltdl; $(MAKE) libltdl.la)
# Without the following line, the check may fail if libltdl/libtool is
# removed after libltdl is configured
../libltdl/libtool:

# Create a version of mdemo that does dlopen.
mdemo_SOURCES = main.c
mdemo_LDFLAGS = -export-dynamic ## FIXME: remove this when libtool and libltdl
## handle dependencies of modules
## The quotes around -dlopen below fool automake into accepting it
mdemo_LDADD = ../libltdl/libltdl.la "-dlopen" self \
		"-dlopen" foo1.la "-dlopen" libfoo2.la
mdemo_DEPENDENCIES = ../libltdl/libltdl.la foo1.la libfoo2.la

# Create a statically linked version of mdemo.
mdemo_static_SOURCES = $(mdemo_SOURCES)
mdemo_static_LDFLAGS = $(STATIC) $(mdemo_LDFLAGS)
mdemo_static_LDADD = $(mdemo_LDADD)
mdemo_static_DEPENDENCIES = $(mdemo_DEPENDENCIES)
