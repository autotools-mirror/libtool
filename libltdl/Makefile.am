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

SUBDIRS			= loaders .

BUILT_SOURCES		=
MOSTLYCLEANFILES	=
EXTRA_DIST		= configure.ac

AUTOMAKE_OPTIONS	= foreign
ACLOCAL_AMFLAGS		= -I m4

DEFS			= -DHAVE_CONFIG_H="<$(CONFIG_H)>" -DLTDL
AM_CPPFLAGS		= -I$(builddir) -I$(srcdir) -I$(srcdir)/libltdl
AM_LDFLAGS		= -no-undefined
VERSION_INFO		= -version-info 6:0:0

pkgincludedir		= $(includedir)/libltdl

lib_LTLIBRARIES		= libdlloader.la
libdlloader_la_SOURCES  = libltdl/lt_error.h lt_error.c \
			  libltdl/lt__private.h libltdl/lt_system.h \
			  libltdl/lt__alloc.h lt__alloc.c \
			  libltdl/lt__glibc.h \
			  libltdl/lt__dirent.h \
			  libltdl/slist.h slist.c
libdlloader_la_LDFLAGS	= $(VERSION_INFO)
libdlloader_la_LIBADD	= $(LTLIBOBJS)

## Libltdl brings it all together:
if INSTALL_LTDL
include_HEADERS		= libltdl/ltdl.h
pkginclude_HEADERS	= libltdl/lt_system.h libltdl/lt_error.h \
			  libltdl/lt_dlloader.h
lib_LTLIBRARIES		+= libltdl.la
endif

if CONVENIENCE_LTDL
noinst_LTLIBRARIES	= libltdlc.la
endif

libltdl_la_SOURCES	= libltdl/ltdl.h ltdl.c \
			  libltdl/lt_dlloader.h lt_dlloader.c loaders/preopen.c
libltdl_la_CPPFLAGS	= -DLTDLOPEN=libltdl $(AM_CPPFLAGS)
libltdl_la_LDFLAGS	=  $(VERSION_INFO) $(LT_DLPREOPEN)
libltdl_la_LIBADD	= libdlloader.la

libltdlc_la_SOURCES	= $(libltdl_la_SOURCES) $(libdlloader_la_SOURCES)
libltdlc_la_CPPFLAGS	= -DLTDLOPEN=libltdlc $(AM_CPPFLAGS)
libltdlc_la_LDFLAGS	= -weak libdlloader.la $(LT_DLPREOPEN)
libltdlc_la_LIBADD	= $(libdlloader_la_LIBADD)

## These are installed as a subdirectory of pkgdatadir so that
## libtoolize --ltdl can find them later:
ltdldatadir		= $(pkgvdatadir)/libltdl
nobase_ltdldata_DATA	= COPYING.LIB Makefile.am README configure.ac \
			  $(libltdl_la_SOURCES) $(libdlloader_la_SOURCES) \
			  lt__dirent.c libltdl/lt__dirent.h \
			  argz_.h argz.c

## Make sure these will be cleaned even when they're not built by default:
CLEANFILES		= libltdl.la libltdlc.la libdlloader.la


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
