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

# These are required by libtoolize.
pkgdata_SCRIPTS = config/config.guess config/config.sub
pkgdata_DATA = config/ltmain.sh

# Me maintain our own macros to provent problems with ancient definitions.
# lt~obsolete.m4 doesn't belong here, it's for bootstrapping us only
pkgmacrodir = $(pkgdatadir)/m4
pkgmacro_DATA = m4/libtool.m4 m4/ltdl.m4 m4/ltsugar.m4

# The standalone libtool script, and the libtool distributor.
bin_SCRIPTS = libtool libtoolize

config_status = $(top_builddir)/config.status

libtool: config/ltmain.sh $(top_builddir)/config.status
	CONFIG_FILES= CONFIG_HEADERS= CONFIG_COMMANDS=$@ $(SHELL) $(config_status)
	chmod +x $@

libtoolize: $(srcdir)/libtoolize.in $(top_builddir)/config.status
	CONFIG_FILES=$@ CONFIG_HEADERS= CONFIG_COMMANDS= $(SHELL) $(config_status)
	chmod +x $@

# Make sure config.status is regenerated when the version timestamp changes
MKSTAMP = $(SHELL) $(top_srcdir)/config/mkstamp
$(config_status): stamp-vcl
stamp-vcl: vcl.tmp $(top_srcdir)/ChangeLog
vcl.tmp:
	@dir=.; test -f $$dir/stamp-vcl || dir=$(srcdir); \
	set `$(MKSTAMP) < $(top_srcdir)/ChangeLog`; \
	echo "$$1" > vcl.tmp; \
	cmp -s vcl.tmp $$dir/stamp-vcl \
## If mkstamp does not match $(srcdir)/stamp-vcl, we still put the new one
## in the current dir, incase $(srcdir) is not writable.  The dir selection
## at the top of this rule takes care of prefering the right one on
## subsequent runs.
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

# Create and install libltdl
install-data-hook:
	cd libltdl && $(MAKE) local-install-files

# Uninstall libltdl
uninstall-local:
	-rm -rf $(DESTDIR)$(pkgdatadir)/libltdl


## ---------------------------------------------------------------- ##
##  Everything past here is useful to the maintainer, but probably  ##
##  not to anybody else (inspiration from automake/Makefile.am).    ##
## ---------------------------------------------------------------- ##

CHECK_LASTRELEASE = if test -z "$(LASTRELEASE)"; \
		      then echo "LASTRELEASE is not set"; exit 1; fi

.PHONY: cvs-release
cvs-release: version-check prev-tarball cvs-news fetch cvs-dist cvs-diff xdelta
	@$(CHECK_LASTRELEASE); tarname="$(PACKAGE)-$(VERSION).tar.gz"; \
	diffname="$(PACKAGE)-$(LASTRELEASE)-$(VERSION).diff.gz"; \
	xdeltaname="$(PACKAGE)-$(LASTRELEASE)-$(VERSION).xdelta"; \
	echo " *** Upload $$tarname, $$tarname.sig,";\
	echo " *** $$tarname.directive.asc, $$diffname,"; \
	echo " *** $$diffname.sig, $$diffname.directive.asc,"; \
	echo " *** $$xdeltaname, $$xdeltaname.sig and";\
	echo " *** $$xdeltaname.directive.asc to either";\
	echo " *** /incoming/alpha or /incoming/ftp on ftp-upload.gnu.org.";

.PHONY: version-check
version-check:
	@case $(VERSION) in \
	*[acegikmoqsuwy]) \
	  echo "Version \`$(VERSION)' is not a releasable version, please read:"; \
	  echo "    http://www.gnu.org/software/libtool/contribute.html"; \
	  exit 1; \
	  ;; \
	esac

.PHONY: prev-tarball
prev-tarball:
## Make sure we have the previous release tarball in the tree.
	@$(CHECK_LASTRELEASE); ofile="$(PACKAGE)-$(LASTRELEASE).tar.gz"; \
	if test -f $$ofile; then :; \
	else echo "Cannot make xdelta without $$ofile"; exit 1; fi

# TSDEPS will be defined to TSDEPS_DIST at `make dist' time
TSDEPS =
TSDEPS_DIST = ChangeLog m4/libtool.m4
CVS = cvs # set it to `:' to avoid CVS operations

.PHONY: timestamps update-timestamps
timestamps: update-timestamps
update-timestamps:
	@if (cd $(srcdir) && test -d CVS && \
	    $(CVS) -n update $(TSDEPS_DIST) | grep '^M'); then \
		echo "Cannot make cvs-dist before commit"; exit 1; else :; fi


.PHONY: cvs-news
cvs-news: timestamps
## Make sure the NEWS file is up-to-date:
	@if sed '1,2d;3q' $(srcdir)/NEWS | grep -e "$(VERSION)" >/dev/null; \
	then :; \
	else \
	  echo "NEWS not updated; not releasing" 1>&2; \
	  exit 1; \
	fi

## Program to use to fetch files.
WGET = wget
WGETSGO = $(WGET) http://savannah.gnu.org/cgi-bin/viewcvs/~checkout~

## Files that we fetch and which we compare against.
## FIXME should be a lot more here
FETCHFILES = \
./INSTALL \
config/config.guess \
libltdl/config.guess \
config/config.sub \
libltdl/config.sub \
config/texinfo.tex

## Fetch the latest versions of files we care about.
.PHONY: fetch
fetch:
	rm -rf Fetchdir > /dev/null 2>&1
	mkdir Fetchdir
## If a get fails then that is a problem.
	(cd Fetchdir && \
	$(WGETSGO)/autoconf/autoconf/INSTALL; \
	$(WGETSGO)/config/config/config.guess; \
	$(WGETSGO)/config/config/config.sub; \
	$(WGETSGO)/texinfo/texinfo/doc/texinfo.tex )
## Don't exit after test because we want to give as many errors as
## possible.
	@stat=0; for file in $(FETCHFILES); do \
	  fetchedfile=Fetchdir/`echo $$file | sed 's,.*/,,g'`; \
	  if diff -u $(srcdir)/$$file $$fetchedfile \
	    >>Fetchdir/update.patch 2>/dev/null; then :; \
	  else \
	    stat=1; \
	    echo "Updating $(srcdir)/$$file..."; \
	    cp $$fetchedfile $(srcdir)/$$file; \
	  fi; \
	done; \
	test $$stat = 1 && \
	  echo "See Fetchdir/update.patch for a log of the changes."; \
	exit $$stat


GPG = gpg # set it to `:' to avoid gpg operations

.PHONY: cvs-dist
cvs-dist: cvs-news
## Build the distribution:
	$(MAKE) distcheck
## Finally, if everything was successful, commit the last changes and tag
## the release in the repository:
	cd $(srcdir) \
	  && $(SHELL) ./commit \
	  && $(CVS) -q tag -c `echo "Release-$(VERSION)" | sed 's/\./-/g'`
## We do want the timestamped version numbers from the CVS keywords in
## ChangeLog to be correct, so we must rebuild the release tarball after
## a successfull commit, and then generate the signatures needed for
## FSF ftp-upload:
	ofile="$(PACKAGE)-$(VERSION).tar.gz"; \
	$(MAKE) dist \
	  && $(GPG) --detach-sign $$ofile \
	  && echo "directory: libtool" > $$ofile.directive \
	  && $(GPG) --clearsign $$ofile.directive \
	  && rm -f $$ofile.directive

.PHONY: cvs-diff
cvs-diff:
## Figure out which cvs tags we are diffing, and if the diff works we
## compress it and then generate the signatures needed for FSF ftp-upload:
	thisver=`echo "release-$(VERSION)" | sed 's/\./-/g'`; \
	$(CHECK_LASTRELEASE); \
	prevver=release-`echo $(LASTRELEASE) | sed 's/\./-/g'`; \
	ofile="$(PACKAGE)-$(LASTRELEASE)-$(VERSION).diff.gz"; \
	$(CVS) -f rdiff -c -r $$prevver -r $$thisver $(PACKAGE) \
	    | GZIP=$(GZIP_ENV) gzip -c > $$ofile \
	  && $(GPG) --detach-sign $$ofile \
	  && echo "directory: libtool" > $$ofile.directive \
	  && $(GPG) --clearsign $$ofile.directive \
	  && rm -f $$ofile.directive

XDELTA = xdelta
XDELTA_OPTIONS = --pristine -9

.PHONY: xdelta
xdelta: prev-tarball
## Make sure xdelta exists;
	@if ($(XDELTA) --version 2>&1 | grep version)>/dev/null 2>/dev/null; \
	then :;\
	else \
	  echo "Get xdelta from http://sourceforge.net/projects/xdelta."; \
	  exit 1; \
	fi
## Generate the delta file (xdelta has wierd exit statuses, so we need to
## add some shell code to keep make happy), and then generate the signatures
## for FSF ftp-upload:
	$(CHECK_LASTRELEASE); \
	ofile="$(PACKAGE)-$(LASTRELEASE)-$(VERSION).xdelta"; \
	( test -z `$(XDELTA) delta $(XDELTA_OPTIONS) \
	    $(PACKAGE)-$(LASTRELEASE).tar.gz $(PACKAGE)-$(VERSION).tar.gz \
	    $$ofile 2>&1` \
	  && : ) \
	&& $(GPG) --detach-sign $$ofile \
	&& echo "directory: libtool" > $$ofile.directive \
	&& $(GPG) --clearsign $$ofile.directive \
	&& rm -f $$ofile.directive
