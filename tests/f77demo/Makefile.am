## Makefile.am -- Process this file with automake to produce Makefile.in
##
## Copyright (C) 2003, 2004 Free Software Foundation
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

AUTOMAKE_OPTIONS = no-dependencies foreign
ACLOCAL_AMFLAGS  = -I ../../m4
AM_CPPFLAGS	 = -I$(top_srcdir)/../..

lib_LTLIBRARIES = libfoo.la libmix.la libfoo2.la libfoo3.la

libfoo_la_SOURCES = foof.f
libfoo_la_LDFLAGS = -no-undefined
libfoo_la_LIBADD = libfoo2.la

libfoo2_la_SOURCES = foof2.f
libfoo2_la_LDFLAGS = -no-undefined

libfoo3_la_SOURCES = foof3.f
libfoo3_la_LDFLAGS = -no-undefined

libmix_la_SOURCES = foof.f foof2.f fooc.c
libmix_la_LDFLAGS = -no-undefined

noinst_HEADERS = foo.h

bin_PROGRAMS = fprogram cprogram

fprogram_SOURCES = fprogram.f
fprogram_LDADD = libfoo.la libfoo3.la

cprogram_SOURCES = cprogram.c
cprogram_LDADD = libmix.la $(FLIBS)

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
