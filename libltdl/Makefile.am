## Process this file with automake to produce Makefile.in
##
## Copyright (C) 1998, 1999, 2000, 2001, 2003, 2004, 2005
## Free Software Foundation, Inc.
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
## the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
## Boston, MA 02110-1301, USA.

BUILT_SOURCES		=
MOSTLYCLEANFILES	=
EXTRA_DIST		= configure.ac

AUTOMAKE_OPTIONS	= foreign
ACLOCAL_AMFLAGS		= -I m4

DEFS			= -DHAVE_CONFIG_H="<$(CONFIG_H)>" -DLTDL
AM_CPPFLAGS		= -I. -I$(srcdir) -I$(srcdir)/libltdl
AM_LDFLAGS		= -no-undefined
VERSION_INFO		= -version-info 6:0:0

noinst_LTLIBRARIES	= $(LT_DLLOADERS)

if INSTALL_LTDL
nobase_include_HEADERS	= ltdl.h \
			  libltdl/lt_system.h libltdl/lt_error.h \
			  libltdl/lt_dlloader.h
lib_LTLIBRARIES		= libltdl.la
endif

if CONVENIENCE_LTDL
noinst_LTLIBRARIES     += libltdlc.la
endif

## !!NOTE!! Be sure to update ../Makefile.am:ltdldatafiles if you
##          make any changes here:
libltdl_la_SOURCES	= libltdl/lt__alloc.h \
			  libltdl/lt__dirent.h \
			  libltdl/lt__glibc.h \
			  libltdl/lt__private.h \
                          libltdl/lt__strl.h \
			  libltdl/lt_dlloader.h \
			  libltdl/lt_error.h \
                          libltdl/lt_system.h \
			  libltdl/slist.h \
			  loaders/preopen.c \
			  lt__alloc.c \
			  lt_dlloader.c \
			  lt_error.c \
			  ltdl.c ltdl.h \
			  slist.c
libltdl_la_CPPFLAGS	= -DLTDLOPEN=$(LTDLOPEN) $(AM_CPPFLAGS)
libltdl_la_LDFLAGS	= $(AM_LDFLAGS) $(VERSION_INFO) $(LT_DLPREOPEN)
libltdl_la_LIBADD	= $(LTLIBOBJS)
libltdl_la_DEPENDENCIES	= $(LT_DLLOADERS) $(LTLIBOBJS) $(BUILT_SOURCES)

libltdlc_la_SOURCES	= $(libltdl_la_SOURCES)
libltdlc_la_CPPFLAGS	= -DLTDLOPEN=$(LTDLOPEN)c $(AM_CPPFLAGS)
libltdlc_la_LDFLAGS	= $(AM_LDFLAGS) $(LT_DLPREOPEN)
libltdlc_la_LIBADD	= $(libltdl_la_LIBADD)
libltdlc_la_DEPENDENCIES= $(libltdl_la_DEPENDENCIES)

## The loaders are preopened by libltdl, itself always built from
## pic-objects (either as a shared library, or a convenience library),
## so the loaders themselves must be made from pic-objects too.  We
## use convenience libraries for that purpose:
EXTRA_LTLIBRARIES	= dlopen.la dld_link.la dyld.la load_add_on.la \
			  loadlibrary.la shl_load.la

dlopen_la_SOURCES	= loaders/dlopen.c
dlopen_la_LDFLAGS	= -module -avoid-version
dlopen_la_LIBADD 	= $(LIBADD_DLOPEN)

dld_link_la_SOURCES	= loaders/dld_link.c
dld_link_la_LDFLAGS	= -module -avoid-version
dld_link_la_LIBADD	= -ldld

dyld_la_SOURCES		= loaders/dyld.c
dyld_la_LDFLAGS		= -module -avoid-version

load_add_on_la_SOURCES	= loaders/load_add_on.c
load_add_on_la_LDFLAGS	= -module -avoid-version

loadlibrary_la_SOURCES	= loaders/loadlibrary.c
loadlibrary_la_LDFLAGS	= -module -avoid-version

shl_load_la_SOURCES	= loaders/shl_load.c
shl_load_la_LDFLAGS	= -module -avoid-version
shl_load_la_LIBADD	= $(LIBADD_SHL_LOAD)

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
