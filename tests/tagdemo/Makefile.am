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

noinst_LTLIBRARIES = libfoo.la
lib_LTLIBRARIES = libbaz.la

libfoo_la_SOURCES = foo.cpp
libfoo_la_LDFLAGS = -no-undefined
libfoo_la_LIBADD = $(LIBM)

# Test some of the ILD support when using tagged configurations.
libbaz_la_SOURCES = baz.cpp
libbaz_la_LDFLAGS = -no-undefined
libbaz_la_LIBADD = libfoo.la

noinst_HEADERS = foo.h baz.h

bin_PROGRAMS = tagdemo

tagdemo_SOURCES = main.cpp
tagdemo_LDADD = libbaz.la

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
