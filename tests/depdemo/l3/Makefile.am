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
## along with this program; if not, a copy can be downloaded from
## http://www.gnu.org/copyleft/gpl.html, or by writing to the Free
## Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
## MA 02110-1301, USA.

top_distdir = ../..
extradir    = $(libdir)/extra

AUTOMAKE_OPTIONS = no-dependencies foreign

AM_CPPFLAGS = -I$(top_srcdir)

lib_LTLIBRARIES = libl3.la
libl3_la_SOURCES = l3.c l3.h
libl3_la_LDFLAGS = -no-undefined
libl3_la_LIBADD = $(top_builddir)/l1/libl1.la $(top_builddir)/l2/libl2.la
