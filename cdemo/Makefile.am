# A brief demonstration of Libtool modules. -*-Makefile-*-
#
AUTOMAKE_OPTIONS = no-dependencies foreign

EXTRA_DIST = acinclude.m4

noinst_LTLIBRARIES = libfoo.la

libfoo_la_SOURCES = foo.c

noinst_HEADERS = foo.h

bin_PROGRAMS = cdemo

cdemo_SOURCES = main.c
cdemo_LDADD = libfoo.la

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
