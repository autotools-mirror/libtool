## Process this file with automake to produce Makefile.in
##
## Copyright (C) 1998, 1999, 2000, 2001, 2003, 2004 Free Software Foundation
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

BUILT_SOURCES =
MOSTLYCLEANFILES =
EXTRA_DIST =

AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS  = -I m4
AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)
DEFS = -DHAVE_CONFIG_H="<$(CONFIG_H)>" -DLTDL

pkgincludedir = $(includedir)/libltdl

if INSTALL_LTDL
include_HEADERS = ltdl.h
pkginclude_HEADERS = lt_system.h lt_error.h
lib_LTLIBRARIES = libltdl.la
endif

if CONVENIENCE_LTDL
noinst_LTLIBRARIES  = libltdlc.la
endif

## Make sure these will be cleaned even when they're not built by
## default.
CLEANFILES	    = libltdl.la libltdlc.la

libltdl_la_SOURCES  = loader-preopen.c \
		      lt__alloc.c lt__alloc.h lt__dirent.h lt__glibc.h \
		      lt__private.h lt_dlloader.h \
		      lt_error.c lt_error.h lt_system.h \
		      ltdl.c ltdl.h
libltdl_la_LDFLAGS  = -no-undefined -version-info 5:0:2
libltdl_la_LIBADD   = $(LIBADD_DL) $(LTLIBOBJS)

libltdlc_la_SOURCES = $(libltdl_la_SOURCES)
libltdlc_la_LIBADD  = $(LIBADD_DL) $(LTLIBOBJS)

## These are installed as a subdirectory of pkgdatadir so that
## libtoolize --ltdl can find them later:
ltdldatadir = $(pkgdatadir)/libltdl
ltdldata_DATA = COPYING.LIB Makefile.am README configure.ac \
		argz_.h argz.c $(libltdl_la_SOURCES) \
		loader-dld_link.c loader-dlopen.c loader-dyld.c \
		loader-load_add_on.c loader-loadlibrary.c loader-shl_load.c \
		lt__dirent.c


## --------------------------- ##
## Gnulib Makefile.am snippets ##
## --------------------------- ##

## ((( gnulib module argz
BUILT_SOURCES += $(ARGZ_H)
EXTRA_DIST += argz_.h

# We need the following in order to create an <argz.h> when the system
# doesn't have one that works with the given compiler.
all-local $(lib_OBJECTS): $(ARGZ_H)
argz.h: argz_.h
	cp $(srcdir)/argz_.h $@-t
	mv $@-t $@
MOSTLYCLEANFILES += argz.h argz.h-t
## ))) gnulib module argz
