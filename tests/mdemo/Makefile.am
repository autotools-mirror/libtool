## Makefile.am -- Process this file with automake to produce Makefile.in
##
## Copyright (C) 2003 Free Software Foundation
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; see the file COPYING.  If not, write to
## the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
## Boston, MA 02111-1307, USA.

top_distdir = ../..

AUTOMAKE_OPTIONS = no-dependencies foreign
ACLOCAL_AMFLAGS  = -I $(top_distdir)/m4

INCLUDES = $(INCLTDL)

lib_LTLIBRARIES = libsub.la foo1.la libfoo2.la libmlib.la

foo1_la_SOURCES = foo1.c
foo1_la_LIBADD = $(LIBM) libsub.la
foo1_la_LDFLAGS = -no-undefined -module -avoid-version

libfoo2_la_SOURCES = foo2.c
libfoo2_la_LIBADD = $(LIBM) libsub.la
libfoo2_la_LDFLAGS = -no-undefined -module -export-symbols-regex "libfoo2.*"

libsub_la_SOURCES = sub.c
libsub_la_LDFLAGS = -no-undefined

libmlib_la_SOURCES = mlib.c
libmlib_la_LIBADD = @LIBLTDL@ "-dlopen" foo1.la "-dlopen" libfoo2.la
libmlib_la_LDFLAGS = -no-undefined
libmlib_la_DEPENDENCIES = @LIBLTDL@ libsub.la foo1.la libfoo2.la

noinst_HEADERS = foo.h

bin_PROGRAMS = mdemo mdemo_static

## use @LIBLTDL@ because some broken makes do not accept macros in targets
## we can only do this because our LIBLTDL does not contain ${top_builddir}
@LIBLTDL@: $(top_distdir)/libtool $(top_distdir)/libltdl/libtool \
    $(top_distdir)/libltdl/config.h $(srcdir)/$(top_distdir)/libltdl/ltdl.c \
    $(srcdir)/$(top_distdir)/libltdl/ltdl.h
	(cd $(top_distdir)/libltdl; $(MAKE) `echo $(LIBLTDL) | sed 's,.*\.\./libltdl/,,g'`)
# Without the following line, the check may fail if libltdl/libtool is
# removed after libltdl is configured
$(top_distdir)/libltdl/libtool $(top_distdir)/libltdl/config.h:

# Create a version of mdemo that does dlopen.
mdemo_SOURCES = main.c
mdemo_LDFLAGS = -export-dynamic
## The quotes around -dlopen below fool automake into accepting it
mdemo_LDADD = @LIBLTDL@ libsub.la "-dlopen" self \
		"-dlopen" foo1.la "-dlopen" libfoo2.la
mdemo_DEPENDENCIES = @LIBLTDL@ libsub.la foo1.la libfoo2.la

# Create a statically linked version of mdemo.
mdemo_static_SOURCES = $(mdemo_SOURCES)
mdemo_static_LDFLAGS = $(STATIC) $(mdemo_LDFLAGS)
mdemo_static_LDADD = $(mdemo_LDADD)
mdemo_static_DEPENDENCIES = $(mdemo_DEPENDENCIES)

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
