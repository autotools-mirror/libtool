# A brief demonstration of Libtool modules. -*-Makefile-*-
#
AUTOMAKE_OPTIONS = no-dependencies foreign

INCLUDES = -I$(srcdir)/../libltdl

EXTRA_DIST = acinclude.m4

noinst_LTLIBRARIES = libfoo1.la

libfoo1_la_SOURCES = foo1.c

noinst_HEADERS = foo.h

bin_PROGRAMS = cdemo

cdemo_SOURCES = main.c
cdemo_LDADD = libfoo1.la $(MATHLIB)
