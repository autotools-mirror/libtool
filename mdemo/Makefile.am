# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
# NOTE: Don't forget that in the libtool distribution, files in this
# directory are distributed by the demo_distfiles variable in the top
# level Makefile.
AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = acinclude.m4

lib_LTLIBRARIES = libfoo1.la libfoo2.la
libfoo1_la_SOURCES = foo1.c foolib1.h
libfoo1_la_LDFLAGS = -export-symbols $(srcdir)/libfoo1.sym -lm

libfoo2_la_SOURCES = foo2.c foolib2.h
libfoo2_la_LDFLAGS = -export-symbols $(srcdir)/libfoo2.sym -lm

include_HEADERS = foo.h

bin_PROGRAMS = hell hell.debug

# Create a version of hell that does dlopen.
hell_SOURCES = main.c ltdl.c
hell_LDFLAGS = $(LIBADD_DL) -lm
hell_DEPENDENCIES = libfoo1.la libfoo2.la

# Create an easier-to-debug version of hell.
hell_debug_SOURCES = main.c ltdls.c
hell_debug_LDADD = libfoo1.la libfoo2.la
hell_debug_LDFLAGS = -export-dynamic -dlpreopen libfoo1.la -dlpreopen libfoo2.la -static
