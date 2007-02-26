## Makefile.am -- Process this file with automake to produce Makefile.in
##
## Copyright (C) 2003, 2004, 2005 Free Software Foundation
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

AUTOMAKE_OPTIONS = no-dependencies foreign
ACLOCAL_AMFLAGS  = -I ../../libltdl/m4
AM_CPPFLAGS	 = -I$(top_srcdir)/../..

lib_LTLIBRARIES = libfoo.la libmix.la libfoo2.la libfoo3.la

libfoo_la_SOURCES = foof.f90
libfoo_la_LDFLAGS = -no-undefined
libfoo_la_LIBADD = libfoo2.la

libfoo2_la_SOURCES = foof2.f90
libfoo2_la_LDFLAGS = -no-undefined

libfoo3_la_SOURCES = foof3.f90
libfoo3_la_LDFLAGS = -no-undefined

libmix_la_SOURCES = foof.f90 foof2.f90 fooc.c
libmix_la_LDFLAGS = -no-undefined

noinst_HEADERS = foo.h

bin_PROGRAMS = fprogram cprogram

fprogram_SOURCES = fprogram.f90
fprogram_LDADD = libfoo.la libfoo3.la

cprogram_SOURCES = cprogram.c
cprogram_LDADD = libmix.la $(FCLIBS)

libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

# work around Automake bug not providing FCFLAGS_f90:
.f90.o:
	$(FCCOMPILE) -c -o $@ $(FCFLAGS_f90) $<

.f90.obj:
	$(FCCOMPILE) -c -o $@ $(FCFLAGS_f90) `$(CYGPATH_W) '$<'`

.f90.lo:
	$(LTFCCOMPILE) -c -o $@ $(FCFLAGS_f90) $<
