# A brief demonstration of Libtool modules. -*-Makefile-*-
#
AUTOMAKE_OPTIONS = no-dependencies foreign

INCLUDES = -I$(srcdir)/../libltdl

EXTRA_DIST = acinclude.m4

lib_LTLIBRARIES = libfoo1.la libfoo2.la

libfoo1_la_SOURCES = foo1.c
libfoo1_la_LDFLAGS = -lm -module -avoid-version

libfoo2_la_SOURCES = foo2.c
libfoo2_la_LDFLAGS = -lm -module

noinst_HEADERS = foo.h

bin_PROGRAMS = mdemo mdemo.debug

# Create a version of hell that does dlopen.
mdemo_SOURCES = main.c
mdemo_LDADD = ../libltdl/libltdl.la \
	-lm # We won't need this when libltdl takes care of dependencies
mdemo_LDFLAGS = -export-dynamic -dlopen libfoo1.la -dlopen libfoo2.la
mdemo_DEPENDENCIES = ../libltdl/libltdl.la libfoo1.la libfoo2.la

# Create an easier-to-debug version of mdemo.
mdemo_debug_SOURCES = main.c
mdemo_debug_LDADD = ../libltdl/libltdl.la
mdemo_debug_LDFLAGS = -static -export-dynamic \
	-dlopen libfoo1.la -dlopen libfoo2.la
mdemo_debug_DEPENDENCIES = ../libltdl/libltdl.la libfoo1.la libfoo2.la
