## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = 1.3e gnu

BUILD_SUBDIRS = . libltdl doc tests
CONF_SUBDIRS = @CONF_SUBDIRS@
SUBDIRS = $(BUILD_SUBDIRS)
DIST_SUBDIRS = $(BUILD_SUBDIRS) $(CONF_SUBDIRS)

# We need to export these variables
CFLAGS = @CFLAGS@
CPPLAGS = @CPPFLAGS@
LDFLAGS = @LDFLAGS@
LIBS= @LIBS@
FFLAGS = @FFLAGS@
FLIBS = @FLIBS@

aclocal_macros = libtool.m4 ltdl.m4

EXTRA_DIST = $(aclocal_macros) bootstrap libtoolize.in ltmain.in \
	mkstamp ChangeLog.0 ChangeLog.1
CLEANFILES = libtool libtoolize ltmain.shT

# These are required by libtoolize.
pkgdata_SCRIPTS = config.guess config.sub
pkgdata_DATA = ltmain.sh

# This macro file should be visible to Automake's aclocal.
aclocal_DATA = $(aclocal_macros)

# The standalone libtool script, and the libtool distributor.
bin_SCRIPTS = libtool libtoolize

libtool: $(srcdir)/ltmain.sh $(top_builddir)/configure.ac
	$(SHELL) $(top_builddir)/config.status --recheck
	chmod +x $@

libtoolize: $(srcdir)/libtoolize.in $(top_builddir)/config.status
	CONFIG_FILES=$@ CONFIG_HEADERS= $(SHELL) $(top_builddir)/config.status
	chmod +x $@

$(srcdir)/ltmain.sh: $(srcdir)/ltmain.in $(TSDEPS)
	-rm -f ltmain.shT
	date=`$(SHELL) $(srcdir)/mkstamp < $(srcdir)/ChangeLog` && \
	sed -e 's/@''PACKAGE@/@PACKAGE@/' -e 's/@''VERSION@/@VERSION@/' \
	    -e "s%@""TIMESTAMP@%$$date%" $(srcdir)/ltmain.in > ltmain.shT
	mv -f ltmain.shT $@ || \
	(rm -f $@ && cp ltmain.shT $@ && rm -f ltmain.shT)
	cp $@ $(srcdir)/libltdl/

# All our rules should depend on these demo files.
all-recursive: $(srcdir)/libltdl/acinclude.m4 $(ACINCLUDE_M4_LIST)

@srcdir@/libltdl/acinclude.m4: $(srcdir)/libtool.m4 $(srcdir)/ltdl.m4
	-rm -f $@ $@T
	cat $(srcdir)/libtool.m4 $(srcdir)/ltdl.m4 > $@T
	mv $@T $@

@ACINCLUDE_M4_LIST@: $(srcdir)/libtool.m4
	-rm -f $@ $@T
	cat $(srcdir)/libtool.m4 > $@T
	mv $@T $@

.PHONY: configure-subdirs
configure-subdirs distdir: $(DIST_MAKEFILE_LIST)
@DIST_MAKEFILE_LIST@:
	dir=`echo $@ | sed 's,^[^/]*$$,.,;s,/[^/]*$$,,'`; \
	test -d $$dir || mkdir $$dir || exit 1; \
	abs_srcdir=`cd $(top_srcdir) && pwd`; \
	(cd $$dir && $$abs_srcdir/$$dir/configure) || exit 1

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
TSDEPS_DIST = ChangeLog libtool.m4
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
./config.guess \
libltdl/config.guess \
./config.sub \
libltdl/config.sub

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
