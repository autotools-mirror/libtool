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

ACLOCAL_AMFLAGS  = -I m4

BUILD_SUBDIRS = . libltdl doc tests
SUBDIRS = $(BUILD_SUBDIRS)
DIST_SUBDIRS = $(BUILD_SUBDIRS)

EXTRA_DIST = bootstrap libtoolize.in ltmain.in config/mkstamp stamp-vcl \
	ChangeLog.1996 ChangeLog.1997 ChangeLog.1998 ChangeLog.1999 \
	ChangeLog.2000 ChangeLog.2001 ChangeLog.2002 ChangeLog.2003
CLEANFILES = libtool libtoolize ltmain.shT

# These are required by libtoolize and must be executable when installed.
# Since _SCRIPTS gets the program transform applied we make them
# executable by hand
dist_pkgdata_DATA = config/config.guess config/config.sub config/ltmain.sh

# Everything that gets picked up by aclocal is automatically distributed,
# this is the list of macro files we install on the user's system.
pkgmacrodir = $(pkgdatadir)/m4
pkgmacro_DATA = m4/argz.m4 m4/libtool.m4 m4/ltdl.m4 \
	m4/ltoptions.m4 m4/ltsugar.m4 m4/ltversion.m4

# We build ltversion.m4 here, instead of from config.status,
# because config.status is rerun each time one og configure's
# dependencies change and ltversion.m4 happens to be a configure
# dependency.  configure and ltversion.m4 vould be rebuilt in
# a loop otherwise.
# Use `$(top_srcdir)/m4' for the benefit of non-GNU makes: this is
# how ltversion.m4 appears in our dependencies.
EXTRA_DIST += m4/ltversion.in
$(top_srcdir)/m4/ltversion.m4: $(top_srcdir)/m4/ltversion.in stamp-vcl
	set `$(MKSTAMP) < $(top_srcdir)/ChangeLog`; \
	serial=`echo $$1 | sed 's,^1[.],,g'`; \
	sed -e "s,[@]MACRO_VERSION[@],$(VERSION),g" \
	    -e "s,[@]MACRO_REVISION[@],$$1,g" \
	    -e "s,[@]MACRO_SERIAL[@],$$serial,g" \
	    -e "s,[@]configure_input[@],Generated from ltversion.in; do not edit by hand.,g" \
	$(top_srcdir)/m4/ltversion.in > $@t
	chmod a-w $@t
	mv -f $@t $@

# The standalone libtool script, and the libtool distributor.
bin_SCRIPTS = libtool libtoolize

## If mkstamp does not match $(srcdir)/stamp-vcl, we still put the new one
## in the current dir, incase $(srcdir) is not writable.  The dir selection
## at the top of this rule takes care of prefering the right one on
## subsequent runs.
MKSTAMP = $(SHELL) $(top_srcdir)/config/mkstamp
stamp-vcl: vcl.tmp $(top_srcdir)/ChangeLog
vcl.tmp:
	@dir=.; test -f $$dir/stamp-vcl || dir=$(srcdir); \
	set `$(MKSTAMP) < $(top_srcdir)/ChangeLog`; \
	echo "$$1" > vcl.tmp; \
	cmp -s vcl.tmp $$dir/stamp-vcl \
	  || (echo "Updating stamp-vcl"; cp vcl.tmp ./stamp-vcl)
	-@rm -f vcl.tmp

.PHONY: configure-subdirs
configure-subdirs distdir: $(DIST_MAKEFILE_LIST)
@DIST_MAKEFILE_LIST@:
	dir=`echo $@ | sed 's,^[^/]*$$,.,;s,/[^/]*$$,,'`; \
	test -d $$dir || mkdir $$dir || exit 1; \
	abs_srcdir=`cd $(top_srcdir) && pwd`; \
	(cd $$dir && $$abs_srcdir/$$dir/configure) || exit 1

install-data-local:
## Don't install over the top of an old pkgdatadir
	-rm -rf $(DESTDIR)$(pkgdatadir)
## Remove old macro definitions
	-rm -rf $(DESTDIR)$(aclocaldir)/ltdl.m4
	-rm -rf $(DESTDIR)$(aclocaldir)/libtool.m4

install-data-hook:
	chmod +x $(DESTDIR)$(pkgdatadir)/config.guess
	chmod +x $(DESTDIR)$(pkgdatadir)/config.sub
