## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = 1.3e gnu

BUILD_SUBDIRS = . libltdl doc tests
SUBDIRS = $(BUILD_SUBDIRS)
DIST_SUBDIRS = $(BUILD_SUBDIRS) $(CONF_SUBDIRS)

# We need to export these variables when we run ltconfig.
CFLAGS = @CFLAGS@
CPPLAGS = @CPPFLAGS@
LDFLAGS = @LDFLAGS@
LIBS= @LIBS@

aclocal_macros = libtool.m4

EXTRA_DIST = $(aclocal_macros) libtoolize.in ltconfig.in ltmain.in \
	mkstamp ChangeLog.0
CLEANFILES = libtool libtoolize ltconfig.T ltmain.shT

# These are required by libtoolize.
pkgdata_SCRIPTS = config.guess config.sub ltconfig
pkgdata_DATA = ltmain.sh

# This macro file should be visible to Automake's aclocal.
aclocal_DATA = $(aclocal_macros)

# The standalone libtool script, and the libtool distributor.
bin_SCRIPTS = libtool libtoolize

libtool: $(srcdir)/ltmain.sh $(srcdir)/ltconfig
	CC="$(CC)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" \
	LD="$(LD)" LDFLAGS="$(LDFLAGS)" LIBS="$(LIBS)" \
	LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	DLLTOOL="$(DLLTOOL)" OBJDUMP="$(OBJDUMP)" AS="$(AS)" \
	$(SHELL) $(srcdir)/ltconfig $(LIBTOOL_FLAGS) --srcdir=$(srcdir) \
	  --output=$@ $(srcdir)/ltmain.sh

# Experimental C version of libtool.
clibtool: $(srcdir)/ltmain.c $(srcdir)/ltconfig
	CC="$(CC)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" \
	LD="$(LD)" LDFLAGS="$(LDFLAGS)" LIBS="$(LIBS)" \
	LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	DLLTOOL="$(DLLTOOL)" OBJDUMP="$(OBJDUMP)" AS="$(AS)" \
	$(SHELL) $(srcdir)/ltconfig $(LIBTOOL_FLAGS) --srcdir=$(srcdir) \
	  --output=$@ $(srcdir)/ltmain.c

libtoolize: $(srcdir)/libtoolize.in $(top_builddir)/config.status
	CONFIG_FILES=libtoolize CONFIG_HEADERS= $(top_builddir)/config.status
	chmod +x libtoolize

# TSDEPS will be defined to TSDEPS_DIST at `make dist' time
TSDEPS =
TSDEPS_DIST = ChangeLog libtool.m4
CVS = cvs # set it to `:' to avoid CVS operations

.PHONY: timestamps update-timestamps
timestamps distdir: update-timestamps
update-timestamps:
	@if (cd $(srcdir) && test -d CVS && \
	    $(CVS) -n update $(TSDEPS_DIST) | grep '^M'); then \
		echo "Cannot make dist before commit"; exit 1; else :; fi
	$(MAKE) TSDEPS="$(TSDEPS_DIST)" $(srcdir)/ltconfig $(srcdir)/ltmain.sh

# Do line number substitution, as well as PACKAGE, VERSION and TIMESTAMP.
# Line numbering transliterated from a section in autoconf (Autoconf 2.12).
@srcdir@/ltconfig: $(srcdir)/ltconfig.in $(top_srcdir)/configure.in $(TSDEPS)
	rm -f ltconfig.T
	date=`$(SHELL) $(srcdir)/mkstamp < $(srcdir)/ChangeLog` && \
	$(AWK) '/@LINENO@/ { printf "%d:", NR } { print }' $(srcdir)/ltconfig.in | \
	  sed -e 's/@''PACKAGE@/@PACKAGE@/' -e 's/@''VERSION@/@VERSION@/' \
	      -e "s%@""TIMESTAMP@%$$date%" \
	      -e '/@LINENO@/s/^\([0-9][0-9]*\):\(.*\)@LINENO@/\2\1/' \
		> ltconfig.T
	chmod +x ltconfig.T
	mv -f ltconfig.T $@ || \
	(rm -f $@ && cp ltconfig.T $@ && rm -f ltconfig.T)

@srcdir@/ltmain.sh: $(srcdir)/ltmain.in $(top_srcdir)/configure.in $(TSDEPS)
	rm -f ltmain.shT
	date=`$(SHELL) $(srcdir)/mkstamp < $(srcdir)/ChangeLog` && \
	sed -e 's/@''PACKAGE@/@PACKAGE@/' -e 's/@''VERSION@/@VERSION@/' \
	    -e "s%@""TIMESTAMP@%$$date%" $(srcdir)/ltmain.in > ltmain.shT
	mv -f ltmain.shT $@ || \
	(rm -f $@ && cp ltmain.shT $@ && rm -f ltmain.shT)

# All our rules should depend on these demo files.
all-recursive: $(ACINCLUDE_M4_LIST)

@ACINCLUDE_M4_LIST@: $(srcdir)/libtool.m4
	rm -f $@
	cp $(srcdir)/libtool.m4 $@

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
	    > $(PACKAGE)-$$prevno-$(VERSION).diff
