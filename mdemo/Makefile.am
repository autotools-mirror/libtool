# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
# NOTE: Don't forget that in the libtool distribution, files in this
# directory are distributed by the demo_distfiles variable in the top
# level Makefile.
AUTOMAKE_OPTIONS = no-dependencies foreign

SUBDIRS = modules

INCLUDES = -I$(srcdir)/../libltdl -I$(srcdir)/modules

EXTRA_DIST = acinclude.m4

bin_PROGRAMS = hell hell.debug

# Create a version of hell that does dlopen.
hell_SOURCES = main.c
hell_LDADD = ../libltdl/libltdl.la \
	-lm # We won't need this when libltdl takes care of dependencies
hell_LDFLAGS = -export-dynamic -dlopen modules/libfoo1.la -dlopen modules/libfoo2.la
hell_DEPENDENCIES = modules/libfoo1.la modules/libfoo2.la

# Create an easier-to-debug version of hell.
hell_debug_SOURCES = main.c
hell_debug_LDADD = ../libltdl/libltdl.la
hell_debug_LDFLAGS = -static -export-dynamic \
	-dlopen modules/libfoo1.la -dlopen modules/libfoo2.la
