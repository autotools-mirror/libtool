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

AM_CPPFLAGS = -I$(top_srcdir)/../../libltdl

bin_PROGRAMS = mdemo2 mdemo2_static

# Create a version of mdemo2 that links a library that does dlopen.
mdemo2_SOURCES = main.c
mdemo2_LDFLAGS = -export-dynamic "-dlopen" force
mdemo2_LDADD = ../mdemo/libmlib.la

# Create a statically linked version of mdemo.
mdemo2_static_SOURCES = $(mdemo2_SOURCES)
mdemo2_static_LDFLAGS = $(STATIC) $(mdemo2_LDFLAGS)
mdemo2_static_LDADD = $(mdemo2_LDADD)
mdemo2_static_DEPENDENCIES = $(mdemo2_DEPENDENCIES)

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
