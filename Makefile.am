## Process Makefile.am with automake to create Makefile.in. -*-Makefile-*-
## Gordon Matzigkeit <gord@gnu.ai.mit.edu>, 1996
AUTOMAKE_OPTIONS = gnits
SUBDIRS = . doc tests $(BUILD_LTDL)
DIST_SUBDIRS = . doc tests libltdl demo mdemo # depdemo

# We need to export these variables when we run ltconfig.
CFLAGS = @CFLAGS@
CPPLAGS = @CPPFLAGS@

aclocal_macros = libtool.m4

EXTRA_DIST = $(aclocal_macros) libtoolize.in ltconfig.in ltmain.in \
	libtool.spec README-alpha # remove this for a non-alpha release
CLEANFILES = libtool libtoolize
MAINTAINERCLEANFILES = ltconfig ltmain.sh

# These are required by libtoolize.
pkgdata_SCRIPTS = config.guess config.sub ltconfig
pkgdata_DATA = ltmain.sh

# This macro file should be visible to Automake's aclocal.
aclocaldir = @aclocaldir@
aclocal_DATA = $(aclocal_macros)

# The standalone libtool script, and the libtool distributor.
bin_SCRIPTS = libtool libtoolize

LIBTOOL_DEPS = $(srcdir)/ltmain.sh $(srcdir)/ltconfig

libtool: $(LIBTOOL_DEPS)
	CC="$(CC)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" \
	LD="$(LD)" LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	$(SHELL) $(srcdir)/ltconfig --srcdir=$(srcdir) --output=$@ \
	  $(srcdir)/ltmain.sh

# Experimental C version of libtool.
clibtool: $(srcdir)/ltmain.c $(srcdir)/ltconfig
	CC="$(CC)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" \
	LD="$(LD)" LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	$(SHELL) $(srcdir)/ltconfig --srcdir=$(srcdir) --output=$@ \
	  $(srcdir)/ltmain.c

libtoolize: $(srcdir)/libtoolize.in $(top_builddir)/config.status
	CONFIG_FILES=libtoolize CONFIG_HEADERS= $(top_builddir)/config.status
	chmod +x libtoolize

# Do line number substitution, as well as PACKAGE and VERSION.
# Line numbering transliterated from a section in autoconf (Autoconf 2.12).
$(srcdir)/ltconfig: $(srcdir)/ltconfig.in $(top_srcdir)/configure.in
	$(AWK) '/@LINENO@/ { printf "%d:", NR } { print }' $(srcdir)/ltconfig.in | \
	  sed -e 's/@''PACKAGE@/@PACKAGE@/' -e 's/@''VERSION@/@VERSION@/' \
	      -e '/@LINENO@/s/^\([0-9][0-9]*\):\(.*\)@LINENO@/\2\1/' > ltconfig.T
	chmod +x ltconfig.T
	mv -f ltconfig.T $@

$(srcdir)/ltmain.sh: $(srcdir)/ltmain.in $(top_srcdir)/configure.in
	sed -e 's/@''PACKAGE@/@PACKAGE@/' -e 's/@''VERSION@/@VERSION@/' $(srcdir)/ltmain.in > ltmain.shT
	mv -f ltmain.shT $@

# We use our own libtool.m4 for these.
ACINCLUDE_M4_LIST = \
	$(srcdir)/acinclude.m4 \
	$(srcdir)/demo/acinclude.m4 \
	$(srcdir)/libltdl/acinclude.m4 \
	$(srcdir)/mdemo/acinclude.m4

# All our rules should depend on these demo files.
all check: $(ACINCLUDE_M4_LIST) $(LIBTOOL_DEPS)

$(ACINCLUDE_M4_LIST): $(srcdir)/libtool.m4
	rm -f $@
	cd `echo $@ | sed 's,/[^/]*$$,,'` && \
	  $(LN_S) `echo $@ | sed -e 's|^$(srcdir)/||' -e 's,[^/]*$$,,' -e 's,[^/][^/]*,..,g'`libtool.m4 acinclude.m4

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
	cd $(srcdir) && cvs -q tag `echo "release-$(VERSION)" | sed 's/\./-/g'`
	$(MAKE) dist

cvs-diff:
	thisver=`echo "release-$(VERSION)" | sed 's/\./-/g'`; \
	if test -z "$$OLDVERSION"; then \
	  prevno=`echo "$(VERSION)" - 0.01 | bc | sed 's/^\./0./'`; \
	else prevno="$$OLDVERSION"; fi; \
	prevver=release-`echo $$prevno | sed 's/\./-/g'`; \
	cvs -f rdiff -c -r $$prevver -r $$thisver $(PACKAGE) \
	    > $(PACKAGE)-$$prevno-$(VERSION).diff
