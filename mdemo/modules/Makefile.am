# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
# NOTE: Don't forget that in the libtool distribution, files in this
# directory are distributed by the demo_distfiles variable in the top
# level Makefile.
AUTOMAKE_OPTIONS = no-dependencies foreign

CFLAGS = @CFLAGS@ -module

INCLUDES = -I$(srcdir)/../../libltdl

lib_LTLIBRARIES = libfoo1.la libfoo2.la

libfoo1_la_SOURCES = foo1.c
libfoo1_la_LDFLAGS = -export-symbols $(srcdir)/libfoo1.sym -lm -module

libfoo2_la_SOURCES = foo2.c
libfoo2_la_LDFLAGS = -export-symbols $(srcdir)/libfoo2.sym -lm -module

include_HEADERS = foo.h
