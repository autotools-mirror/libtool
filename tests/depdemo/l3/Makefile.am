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

top_distdir = ../..
extradir    = $(libdir)/extra

AUTOMAKE_OPTIONS = no-dependencies foreign

AM_CPPFLAGS = -I$(top_srcdir)

lib_LTLIBRARIES = libl3.la
libl3_la_SOURCES = l3.c l3.h
libl3_la_LDFLAGS = -no-undefined
libl3_la_LIBADD = $(top_builddir)/l1/libl1.la $(top_builddir)/l2/libl2.la
