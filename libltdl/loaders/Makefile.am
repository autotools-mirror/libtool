## Process this file with automake to produce Makefile.in
##
## Copyright (C) 2004, 2005 Free Software Foundation, Inc.
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

BUILT_SOURCES		=
MOSTLYCLEANFILES	=
EXTRA_DIST		=

AUTOMAKE_OPTIONS	= foreign

DEFS			= -DHAVE_CONFIG_H="<$(CONFIG_H)>" -DLTDL
AM_CPPFLAGS		= -I$(top_builddir) -I$(top_srcdir)  \
			  -I.. -I$(srcdir)/.. -I$(srcdir)/../libltdl
AM_LDFLAGS		= -module -avoid-version

pkgincludedir		= $(includedir)/libltdl


## The loaders are preopened by libltdl, itself always built from
## pic-objects (either as a shared library, or a convenience library),
## so the loaders themselves must be made from pic-objects too.  We
## use convenience libraries for that purpose:
noinst_LTLIBRARIES	= $(LT_DLLOADERS)
EXTRA_LTLIBRARIES	= dlopen.la dld_link.la dyld.la load_add_on.la \
			  loadlibrary.la shl_load.la

dlopen_la_LIBADD 	= $(LIBADD_DLOPEN)
shl_load_la_LIBADD	= $(LIBADD_SHL_LOAD)
dld_link_la_LIBADD	= -ldld


## These are installed as a subdirectory of pkgdatadir so that
## libtoolize --ltdl can find them later:
ltdldatadir		= $(pkgvdatadir)/libltdl/loaders
ltdldatafiles		= Makefile.am dld_link.c dlopen.c dyld.c \
			  load_add_on.c loadlibrary.c shl_load.c

## To avoid spurious reconfiguration when the user installs these files
## with libtoolize, we have to preserve their timestamps carefully:
install-data-local:
	-rm -rf $(DESTDIR)$(ltdldatadir)
	$(mkinstalldirs) $(DESTDIR)$(ltdldatadir)
	$(AMTAR) cf - $(ltdldatafiles) \
	  | ( cd $(DESTDIR)$(ltdldatadir) && $(AMTAR) xf -; )
