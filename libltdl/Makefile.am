# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
# NOTE: Don't forget that in the libtool distribution, files in this
# directory are distributed by the demo_distfiles variable in the top
# level Makefile.
AUTOMAKE_OPTIONS = no-dependencies foreign

CFLAGS = -module

EXTRA_DIST = acinclude.m4

lib_LTLIBRARIES = libltdl.la
libltdl_la_SOURCES = ltdl.c
libltdl_la_LDFLAGS = $(LIBADD_DL) 

include_HEADERS = ltdl.h
