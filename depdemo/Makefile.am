# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
# NOTE: Don't forget that in the libtool distribution, files in this
# directory are distributed by the demo_distfiles variable in the top
# level Makefile.
AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = acinclude.m4

lib_LTLIBRARIES = libl1.la libl2.la libl3.la libl4.la
libl1_la_SOURCES = l1.c l1.h sysdep.h
libl2_la_SOURCES = l2.c l2.h sysdep.h
libl2_la_LIBADD = libl1.la
libl3_la_SOURCES = l3.c l3.h sysdep.h
libl3_la_LIBADD = libl1.la libl2.la
libl4_la_SOURCES = l4.c l4.h sysdep.h
libl4_la_LIBADD = libl3.la -lm

bin_PROGRAMS = depdemo depdemo.static

depdemo_SOURCES = main.c
depdemo_LDADD = libl1.la libl2.la libl4.la \
		libl3.la # remove this!
depdemo_DEPENDENCIES = libl1.la libl2.la libl4.la

depdemo_static_SOURCES = main.c
depdemo_static_LDADD = libl1.la libl2.la libl4.la \
		libl3.la # remove this!
depdemo_static_DEPENDENCIES = libl1.la libl2.la libl4.la
depdemo_static_LDFLAGS = -static
