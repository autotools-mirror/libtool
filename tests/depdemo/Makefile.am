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

AUTOMAKE_OPTIONS = no-dependencies foreign
ACLOCAL_AMFLAGS  = -I ../../m4

SUBDIRS = l1 l2 l3 l4

EXTRA_DIST = sysdep.h

bin_PROGRAMS = depdemo depdemo_static

depdemo_SOURCES = main.c
depdemo_LDADD = $(top_builddir)/l1/libl1.la $(top_builddir)/l2/libl2.la \
		$(top_builddir)/l4/libl4.la
depdemo_DEPENDENCIES = $(top_builddir)/l1/libl1.la \
		$(top_builddir)/l2/libl2.la $(top_builddir)/l4/libl4.la

depdemo_static_SOURCES = $(depdemo_SOURCES)
depdemo_static_LDADD = $(depdemo_LDADD)
depdemo_static_DEPENDENCIES = $(depdemo_DEPENDENCIES)
depdemo_static_LDFLAGS = $(STATIC)

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
