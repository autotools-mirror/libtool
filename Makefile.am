## Process Makefile.am with automake to create Makefile.in. -*-Makefile-*-
## Gordon Matzigkeit <gord@gnu.ai.mit.edu>, 1996
AUTOMAKE_OPTIONS = gnits
SUBDIRS = doc tests

# We need to export these variables when we run ltconfig.
CFLAGS = @CFLAGS@
CPPLAGS = @CPPFLAGS@

aclocal_macros = libtool.m4

EXTRA_DIST = $(aclocal_macros) libtoolize.in ltconfig.in ltmain.sh.in \
	libtool.spec libtool.prj
CLEANFILES = libtool libtoolize
MAINTAINERCLEANFILES = ltconfig ltmain.sh

# Files in the demo subdirectory that go in the distribution.
demo_distfiles = demo/Makefile.in demo/Makefile.am demo/README \
	demo/acinclude.m4 demo/aclocal.m4 \
	demo/configure demo/configure.in demo/foo.c demo/foo.h \
	demo/hello.c demo/main.c demo/run.test

# These are required by libtoolize.
pkgdata_SCRIPTS = config.guess config.sub ltconfig
pkgdata_DATA = ltmain.sh

# This macro file should be visible to Automake's aclocal.
aclocaldir = @aclocaldir@
aclocal_DATA = $(aclocal_macros)

# The standalone libtool script, and the libtool distributor.
bin_SCRIPTS = libtool libtoolize

libtool: ltconfig
	@echo 'WARNING: Warnings from ltconfig can be ignored. :-)'
	CC="$(CC)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" \
	LD="$(LD)" LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	$(srcdir)/ltconfig --srcdir=$(srcdir) $(pkgdatadir)/ltmain.sh

libtoolize: libtoolize.in $(top_builddir)/config.status
	CONFIG_FILES=libtoolize CONFIG_HEADERS= $(top_builddir)/config.status
	chmod +x libtoolize

# These depend on configure.in (rather then config.status) so that version
# numbers are correctly updated.
# This way, they aren't regenerated after people configure the package.
$(srcdir)/ltconfig: ltconfig.in configure.in
	CONFIG_FILES=ltconfig CONFIG_HEADERS= $(top_builddir)/config.status
	chmod +x ltconfig
	test "$(srcdir)" = . || mv ltconfig $(srcdir)/ltconfig

$(srcdir)/ltmain.sh: ltmain.sh.in configure.in
	CONFIG_FILES=ltmain.sh CONFIG_HEADERS= $(top_builddir)/config.status
	test "$(srcdir)" = . || mv ltmain.sh $(srcdir)/ltmain.sh

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
$(srcdir)/aclocal.m4: acinclude.m4
$(srcdir)/acinclude.m4:
	rm -f $(srcdir)/acinclude.m4
	ln -s libtool.m4 $(srcdir)/acinclude.m4

# Rules for rebuilding some of the demo source files.
$(srcdir)/demo/Makefile.in: demo/Makefile.am demo/configure.in demo/aclocal.m4
	cd $(srcdir)/demo && $(AUTOMAKE)

$(srcdir)/demo/configure: demo/configure.in demo/aclocal.m4
	cd $(srcdir)/demo && $(AUTOCONF)

$(srcdir)/demo/aclocal.m4: demo/configure.in demo/acinclude.m4
	cd $(srcdir)/demo && $(ACLOCAL)

$(srcdir)/demo/acinclude.m4:
	rm -f $(srcdir)/demo/acinclude.m4
	ln -s ../libtool.m4 $(srcdir)/demo/acinclude.m4
