## Process Makefile.am with automake to create Makefile.in. -*-Makefile-*-
## Gordon Matzigkeit <gord@gnu.ai.mit.edu>, 1996
AUTOMAKE_OPTIONS = gnits
SUBDIRS = doc tests

# We need to export these variables when we run ltconfig.
CFLAGS = @CFLAGS@
CPPLAGS = @CPPFLAGS@

aclocal_macros = libtool.m4

EXTRA_DIST = $(aclocal_macros) libtoolize.in ltconfig.in ltmain.in \
	libtool.spec libtool.prj
CLEANFILES = libtool libtoolize
MAINTAINERCLEANFILES = ltconfig ltmain.sh

# Files in the demo subdirectory that go in the distribution.
demo_distfiles = demo/Makefile.in demo/Makefile.am demo/README \
	demo/acinclude.m4 demo/aclocal.m4 \
	demo/configure demo/configure.in demo/foo.c demo/foo.h \
	demo/dlmain.c demo/hello.c demo/main.c demo/run.test

# These are required by libtoolize.
pkgdata_SCRIPTS = config.guess config.sub ltconfig
pkgdata_DATA = ltmain.sh

# This macro file should be visible to Automake's aclocal.
aclocaldir = @aclocaldir@
aclocal_DATA = $(aclocal_macros)

# The standalone libtool script, and the libtool distributor.
bin_SCRIPTS = libtool libtoolize

libtool: ltmain.sh ltconfig
	CC="$(CC)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" \
	LD="$(LD)" LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	$(SHELL) $(srcdir)/ltconfig --srcdir=$(srcdir) --output=$@  $<

# Experimental C version of libtool.
clibtool: ltmain.c ltconfig
	CC="$(CC)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" \
	LD="$(LD)" LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	$(SHELL) $(srcdir)/ltconfig --srcdir=$(srcdir) --output=$@ $<

libtoolize: libtoolize.in $(top_builddir)/config.status
	CONFIG_FILES=libtoolize CONFIG_HEADERS= $(top_builddir)/config.status
	chmod +x libtoolize

# Do line number substitution, as well as PACKAGE and VERSION.
# Line numbering transliterated from a section in autoconf (Autoconf 2.12).
$(srcdir)/ltconfig: ltconfig.in $(top_srcdir)/configure.in
	$(AWK) '/@LINENO@/ { printf "%d:", NR } { print }' $(srcdir)/ltconfig.in | \
	  sed -e 's/@''PACKAGE@/@PACKAGE@/' -e 's/@''VERSION@/@VERSION@/' \
	      -e '/@LINENO@/s/^\([0-9][0-9]*\):\(.*\)@LINENO@/\2\1/' > ltconfig.T
	chmod +x ltconfig.T
	mv -f ltconfig.T $@

$(srcdir)/ltmain.sh: ltmain.in $(top_srcdir)/configure.in
	sed -e 's/@''PACKAGE@/@PACKAGE@/' -e 's/@''VERSION@/@VERSION@/' $(srcdir)/ltmain.in > ltmain.shT
	mv -f ltmain.shT $@

# Distribute the demo subdirectory.
dist-hook: $(demo_distfiles)
	mkdir $(distdir)/demo
	-chmod 755 $(distdir)/demo
	here=`pwd`; distdir=`cd $(distdir) && pwd` \
	  && cd $(srcdir)/demo \
	  && $(AUTOMAKE) --include-deps --build-dir=$$here/demo --srcdir-name=$(srcdir)/demo --output-dir=$$distdir/demo
	@for file in $(demo_distfiles); do \
	  d=$(srcdir); \
	  test -f $(distdir)/$$file \
	  || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	  || cp -p $$d/$$file $(distdir)/$$file; \
	done

# All our rules should depend on these demo files.
all: demo/Makefile.in demo/configure

# We use our own libtool.m4.
$(srcdir)/acinclude.m4: libtool.m4
	rm -f $(srcdir)/acinclude.m4
	cd $(srcdir) && $(LN_S) libtool.m4 acinclude.m4
$(srcdir)/demo/acinclude.m4: libtool.m4
	rm -f $(srcdir)/demo/acinclude.m4
	cd $(srcdir)/demo && $(LN_S) ../libtool.m4 acinclude.m4

# Rules for rebuilding some of the demo source files.
$(srcdir)/demo/Makefile.in: demo/Makefile.am demo/configure.in demo/aclocal.m4
	cd $(srcdir)/demo && $(AUTOMAKE)

$(srcdir)/demo/configure: demo/configure.in demo/aclocal.m4
	cd $(srcdir)/demo && $(AUTOCONF)

$(srcdir)/demo/aclocal.m4: demo/configure.in demo/acinclude.m4
	cd $(srcdir)/demo && $(ACLOCAL)

######################################################################
# These commands really help my life as a maintainer who uses PRCS.
# Feel free to copy them to your own project.  I just run a
# maintainer-checkin whenever I feel like it, then I run a maintainer-release
# after changing the project major version number in my project file.
#
# This works because of the special `$Format: ...$' string I have in my
# `configure.in'.
PRCS = prcs
released = $(top_srcdir)/.released

# At least configure.in should be rekeyed, but you can also add other files.
rekey_files = configure.in libtool.spec

.PHONY: maintainer-checkin maintainer-rekey maintainer-release
maintainer-checkin: maintainer-rekey
	cd $(top_srcdir) && $(PRCS) checkin -f $(PACKAGE).prj

maintainer-rekey:
	@newver=`grep '^(Project-Version[ 	]' $(srcdir)/$(PACKAGE).prj | \
	   sed 's/^.*[ 	]\+\([^ 	]\+\)[ 	]\+[0-9]\+).*$$/\1/'`; \
	  if test "X$$newver" = "X$(VERSION)"; then \
	    if test -f "$(released)"; then \
	      echo "New development cycle: change Project-Version in $(top_srcdir)/$(PACKAGE).prj."; \
	      exit 1; \
	    else \
	      echo "No need to rekey any files"; \
	    fi; \
	  else \
	    rm -f "$(released)"; \
	    echo "cd $(top_srcdir) && $(PRCS) rekey -f $(PACKAGE).prj $(rekey_files)"; \
	    cd $(top_srcdir) && $(PRCS) rekey -f $(PACKAGE).prj $(rekey_files); \
	  fi

maintainer-release: maintainer-rekey distcheck
	cd $(top_srcdir) && $(PRCS) checkin -f $(PACKAGE).prj
	echo "$(VERSION)" > "$(release)"
	@echo "============================="; \
	  echo "Congratulations!  $(PACKAGE)-$(VERSION) is now complete."; \
	  echo; \
	  echo "Distribute \`$(PACKAGE)-$(VERSION).tar.gz' to the masses, and don't forget"; \
	  echo "any other details you need to complete this release."; \
	  echo "============================="
