# A brief demonstration of inter-library dependencies
#

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES = libl2.la
libl2_la_SOURCES = l2.c l2.h
libl2_la_LIBADD = $(top_builddir)/l1/libl1.la
