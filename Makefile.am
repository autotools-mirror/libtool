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

AUTOMAKE_OPTIONS = 1.7 gnu
ACLOCAL_AMFLAGS  = -I m4

BUILD_SUBDIRS = . libltdl doc tests
SUBDIRS = $(BUILD_SUBDIRS)
DIST_SUBDIRS = $(BUILD_SUBDIRS) $(CONF_SUBDIRS)

aclocal_macros = m4/libtool.m4 m4/ltdl.m4

EXTRA_DIST = $(aclocal_macros) bootstrap libtoolize.in ltmain.in \
	config/mkstamp ChangeLog.0 ChangeLog.1
CLEANFILES = libtool libtoolize ltmain.shT

# These are required by libtoolize.
pkgdata_SCRIPTS = config/config.guess config/config.sub
pkgdata_DATA = config/ltmain.sh

# This macro file should be visible to Automake's aclocal.
aclocal_DATA = $(aclocal_macros)

# The standalone libtool script, and the libtool distributor.
bin_SCRIPTS = libtool libtoolize

config_status = $(top_builddir)/config.status

libtool: config/ltmain.sh $(top_builddir)/configure
	CONFIG_FILES= CONFIG_HEADERS= $(SHELL) $(config_status)
	chmod +x $@

libtoolize: $(srcdir)/libtoolize.in $(top_builddir)/config.status
	CONFIG_FILES=$@ CONFIG_HEADERS= CONFIG_COMMANDS= $(SHELL) $(config_status)
	chmod +x $@

# TSDEPS will be defined to TSDEPS_DIST at `make dist' time
TSDEPS =
TSDEPS_DIST = ChangeLog m4/libtool.m4
CVS = cvs # set it to `:' to avoid CVS operations

.PHONY: timestamps update-timestamps
timestamps distdir: update-timestamps
update-timestamps:
	@if (cd $(srcdir) && test -d CVS && \
	    $(CVS) -n update $(TSDEPS_DIST) | grep '^M'); then \
		echo "Cannot make dist before commit"; exit 1; else :; fi

.PHONY: configure-subdirs
configure-subdirs distdir: $(DIST_MAKEFILE_LIST)
@DIST_MAKEFILE_LIST@:
	dir=`echo $@ | sed 's,^[^/]*$$,.,;s,/[^/]*$$,,'`; \
	test -d $$dir || mkdir $$dir || exit 1; \
	abs_srcdir=`cd $(top_srcdir) && pwd`; \
	(cd $$dir && $$abs_srcdir/$$dir/configure) || exit 1

# Don't install over the top of an old pkgdatadir
install-data-local:
	-rm -rf $(DESTDIR)$(pkgdatadir)

# Create and install libltdl
install-data-hook:
	cd libltdl && $(MAKE) local-install-files

# Uninstall libltdl
uninstall-local:
	-rm -rf $(DESTDIR)$(pkgdatadir)/libltdl

################################################################
##
## Everything past here is useful to the maintainer, but probably not
## to anybody else (snarfed from automake/Makefile.am).
##

# Tag before making distribution.  Also, don't make a distribution if
# checks fail.  Also, make sure the NEWS file is up-to-date.
cvs-dist: distcheck
	@if sed '1,2d;3q' $(srcdir)/NEWS | grep -e "$(VERSION)" > /dev/null; then :; else \
	  echo "NEWS not updated; not releasing" 1>&2; \
	  exit 1;				\
	fi
	cd $(srcdir) && \
	 $(CVS) -q tag `echo "release-$(VERSION)" | sed 's/\./-/g'`
	$(MAKE) dist

cvs-diff:
	thisver=`echo "release-$(VERSION)" | sed 's/\./-/g'`; \
	if test -z "$$OLDVERSION"; then \
	  prevno=`echo "$(VERSION)" - 0.01 | bc | sed 's/^\./0./'`; \
	else prevno="$$OLDVERSION"; fi; \
	prevver=release-`echo $$prevno | sed 's/\./-/g'`; \
	$(CVS) -f rdiff -c -r $$prevver -r $$thisver $(PACKAGE) \
	    | GZIP=$(GZIP_ENV) gzip -c \
	    > $(PACKAGE)-$$prevno-$(VERSION).diff.gz
