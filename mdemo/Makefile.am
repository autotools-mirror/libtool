# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
# NOTE: Don't forget that in the libtool distribution, files in this
# directory are distributed by the demo_distfiles variable in the top
# level Makefile.
AUTOMAKE_OPTIONS = no-dependencies foreign

INCLUDES = -I$(srcdir)/../libltdl

EXTRA_DIST = acinclude.m4

lib_LTLIBRARIES = libfoo1.la libfoo2.la

libfoo1_la_SOURCES = foo1.c
libfoo1_la_LDFLAGS = -lm -module

libfoo2_la_SOURCES = foo2.c
libfoo2_la_LDFLAGS = -lm -module -static

noinst_HEADERS = foo.h

bin_PROGRAMS = hell hell.debug

# Create a version of hell that does dlopen.
hell_SOURCES = main.c
hell_LDADD = ../libltdl/libltdl.la \
	-lm # We won't need this when libltdl takes care of dependencies
hell_LDFLAGS = -export-dynamic -dlopen libfoo1.la -dlopen libfoo2.la
hell_DEPENDENCIES = ../libltdl/libltdl.la libfoo1.la libfoo2.la

# Create an easier-to-debug version of hell.
hell_debug_SOURCES = main.c
hell_debug_LDADD = ../libltdl/libltdl.la
hell_debug_LDFLAGS = -static -export-dynamic \
	-dlopen libfoo1.la -dlopen libfoo2.la
hell_DEPENDENCIES = ../libltdl/libltdl.la libfoo1.la libfoo2.la
