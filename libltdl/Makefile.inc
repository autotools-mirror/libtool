## Makefile.am -- Process this file with automake to produce Makefile.in
##
## Copyright (C) 2003, 2004, 2005 Free Software Foundation, Inc.
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## As a special exception to the GNU Lesser General Public License,
## if you distribute this file as part of a program or library that
## is built using GNU libtool, you may include it under the same
## distribution terms that you use for the rest of that program.
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

## DO NOT REMOVE THIS LINE -- make depends on it

# -I$(srcdir) is needed for user that built libltdl with a sub-Automake
# (not as a sub-package!) using 'nostdinc':
AM_CPPFLAGS	       += -DLT_CONFIG_H='<$(LT_CONFIG_H)>' \
			  -DLTDL -I. -I$(srcdir) -Ilibltdl \
			  -I$(srcdir)/libltdl -I$(srcdir)/libltdl/libltdl
AM_LDFLAGS	       += -no-undefined
LTDL_VERSION_INFO	= -version-info 7:0:0

noinst_LTLIBRARIES	+= $(LT_DLLOADERS)

if INSTALL_LTDL
ltdlincludedir		= $(includedir)/libltdl
ltdlinclude_HEADERS	= libltdl/libltdl/lt_system.h \
			  libltdl/libltdl/lt_error.h \
			  libltdl/libltdl/lt_dlloader.h
include_HEADERS		= libltdl/ltdl.h
lib_LTLIBRARIES	       += libltdl/libltdl.la
endif

if CONVENIENCE_LTDL
noinst_LTLIBRARIES     += libltdl/libltdlc.la
endif

libltdl_libltdl_la_SOURCES = libltdl/libltdl/lt__alloc.h \
			  libltdl/libltdl/lt__dirent.h \
			  libltdl/libltdl/lt__glibc.h \
			  libltdl/libltdl/lt__private.h \
			  libltdl/libltdl/lt__strl.h \
			  libltdl/libltdl/lt_dlloader.h \
			  libltdl/libltdl/lt_error.h \
	                  libltdl/libltdl/lt_system.h \
			  libltdl/libltdl/slist.h \
			  libltdl/loaders/preopen.c \
			  libltdl/lt__alloc.c \
			  libltdl/lt_dlloader.c \
			  libltdl/lt_error.c \
			  libltdl/ltdl.c \
			  libltdl/ltdl.h \
			  libltdl/slist.c

libltdl_libltdl_la_CPPFLAGS	= -DLTDLOPEN=$(LTDLOPEN) $(AM_CPPFLAGS)
libltdl_libltdl_la_LDFLAGS	= $(AM_LDFLAGS) $(LTDL_VERSION_INFO) $(LT_DLPREOPEN)
libltdl_libltdl_la_LIBADD	= $(LTLIBOBJS)
libltdl_libltdl_la_DEPENDENCIES	= $(LT_DLLOADERS) $(LTLIBOBJS)

libltdl_libltdlc_la_SOURCES	= $(libltdl_libltdl_la_SOURCES)
libltdl_libltdlc_la_CPPFLAGS	= -DLTDLOPEN=$(LTDLOPEN)c $(AM_CPPFLAGS)
libltdl_libltdlc_la_LDFLAGS	= $(AM_LDFLAGS) $(LT_DLPREOPEN)
libltdl_libltdlc_la_LIBADD	= $(libltdl_libltdl_la_LIBADD)
libltdl_libltdlc_la_DEPENDENCIES= $(libltdl_libltdl_la_DEPENDENCIES)

## The loaders are preopened by libltdl, itself always built from
## pic-objects (either as a shared library, or a convenience library),
## so the loaders themselves must be made from pic-objects too.  We
## use convenience libraries for that purpose:
EXTRA_LTLIBRARIES	       += libltdl/dlopen.la \
				  libltdl/dld_link.la \
				  libltdl/dyld.la \
				  libltdl/load_add_on.la \
				  libltdl/loadlibrary.la \
				  libltdl/shl_load.la

libltdl_dlopen_la_SOURCES	= libltdl/loaders/dlopen.c
libltdl_dlopen_la_LDFLAGS	= -module -avoid-version
libltdl_dlopen_la_LIBADD 	= $(LIBADD_DLOPEN)

libltdl_dld_link_la_SOURCES	= libltdl/loaders/dld_link.c
libltdl_dld_link_la_LDFLAGS	= -module -avoid-version
libltdl_dld_link_la_LIBADD	= -ldld

libltdl_dyld_la_SOURCES		= libltdl/loaders/dyld.c
libltdl_dyld_la_LDFLAGS		= -module -avoid-version

libltdl_load_add_on_la_SOURCES	= libltdl/loaders/load_add_on.c
libltdl_load_add_on_la_LDFLAGS	= -module -avoid-version

libltdl_loadlibrary_la_SOURCES	= libltdl/loaders/loadlibrary.c
libltdl_loadlibrary_la_LDFLAGS	= -module -avoid-version

libltdl_shl_load_la_SOURCES	= libltdl/loaders/shl_load.c
libltdl_shl_load_la_LDFLAGS	= -module -avoid-version
libltdl_shl_load_la_LIBADD	= $(LIBADD_SHL_LOAD)

## Make sure these will be cleaned even when they're not built by default:
CLEANFILES		       += libltdl/libltdl.la \
				  libltdl/libltdlc.la \
				  libltdl/libdlloader.la

## Automake-1.9.6 doesn't clean subdir AC_LIBOBJ compiled objects
## automatically:
CLEANFILES	       += $(LIBOBJS) $(LTLIBOBJS)

EXTRA_DIST	       += libltdl/COPYING.LIB \
			  libltdl/Makefile.am \
			  libltdl/Makefile.in \
			  libltdl/Makefile.inc \
			  libltdl/README \
			  libltdl/config-h.in \
			  libltdl/configure \
			  libltdl/configure.ac \
			  libltdl/aclocal.m4 \
			  libltdl/m4/lt~obsolete.m4

## --------------------------- ##
## Gnulib Makefile.am snippets ##
## --------------------------- ##

BUILT_SOURCES	+= libltdl/$(ARGZ_H)
EXTRA_DIST	+= libltdl/argz_.h

# We need the following in order to create an <argz.h> when the system
# doesn't have one that works with the given compiler.
all-local $(lib_OBJECTS): libltdl/$(ARGZ_H)
libltdl/argz.h: libltdl/argz_.h
	cp $(srcdir)/libltdl/argz_.h $@-t
	mv $@-t $@
MOSTLYCLEANFILES += libltdl/argz.h \
		    libltdl/argz.h-t
