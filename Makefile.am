## Process Makefile.am with automake to create Makefile.in. -*-Makefile-*-
## Gordon Matzigkeit <gord@gnu.ai.mit.edu>, 1996
AUTOMAKE_OPTIONS = gnits
SUBDIRS = doc tests

# We need to export these variables when we run ltconfig.
CFLAGS = @CFLAGS@
CPPLAGS = @CPPFLAGS@

aclocal_macros = libtool.m4

EXTRA_DIST = $(aclocal_macros) libtoolize.in ltconfig.in ltmain.in \
	libtool.spec
CLEANFILES = libtool libtoolize
MAINTAINERCLEANFILES = ltconfig ltmain.sh

# Files in the demo subdirectory that go in the distribution.
demo_distfiles = demo/Makefile.in demo/Makefile.am demo/README \
	demo/acinclude.m4 demo/aclocal.m4 \
	demo/configure demo/configure.in demo/foo.c demo/foo.h \
	demo/dlmain.c demo/hello.c demo/main.c demo/run.test

# Files in the mdemo subdirectory that go in the distribution.
mdemo_distfiles = mdemo/Makefile.in mdemo/Makefile.am mdemo/README \
	mdemo/acinclude.m4 mdemo/aclocal.m4 \
	mdemo/configure mdemo/configure.in \
	mdemo/main.c mdemo/modules/Makefile.in mdemo/modules/Makefile.am \
	mdemo/modules/foo.h mdemo/modules/foo1.c mdemo/modules/foo2.c \
	mdemo/modules/libfoo1.sym mdemo/modules/libfoo2.sym

# Files in the libltdl subdirectory that go in the distribution.
libltdl_distfiles = libltdl/Makefile.in libltdl/Makefile.am libltdl/README \
	libltdl/acinclude.m4 libltdl/aclocal.m4 \
	libltdl/configure libltdl/configure.in \
	libltdl/ltdl.h libltdl/ltdl.c

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

# Distribute the demo, mdemo and libltdl subdirectory.
dist-hook: $(demo_distfiles) $(mdemo_distfiles) $(libltdl_distfiles)
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
	mkdir $(distdir)/mdemo
	-chmod 755 $(distdir)/mdemo
	here=`pwd`; distdir=`cd $(distdir) && pwd` \
	  && cd $(srcdir)/mdemo \
	  && $(AUTOMAKE) --include-deps --build-dir=$$here/mdemo --srcdir-name=$(srcdir)/mdemo --output-dir=$$distdir/mdemo
	@for file in $(mdemo_distfiles); do \
	  d=$(srcdir); \
	  test -f $(distdir)/$$file \
	  || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	  || cp -p $$d/$$file $(distdir)/$$file; \
	done
	mkdir $(distdir)/libltdl
	-chmod 755 $(distdir)/libltdl
	here=`pwd`; distdir=`cd $(distdir) && pwd` \
	  && cd $(srcdir)/libltdl \
	  && $(AUTOMAKE) --include-deps --build-dir=$$here/libltdl --srcdir-name=$(srcdir)/libltdl --output-dir=$$distdir/libltdl
	@for file in $(libltdl_distfiles); do \
	  d=$(srcdir); \
	  test -f $(distdir)/$$file \
	  || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	  || cp -p $$d/$$file $(distdir)/$$file; \
	done

# All our rules should depend on these demo files.
all: demo/Makefile.in demo/configure mdemo/Makefile.in mdemo/configure \
     libltdl/Makefile.in libltdl/configure

# We use our own libtool.m4.
$(srcdir)/acinclude.m4: libtool.m4
	rm -f $(srcdir)/acinclude.m4
	cd $(srcdir) && $(LN_S) libtool.m4 acinclude.m4
$(srcdir)/demo/acinclude.m4: libtool.m4
	rm -f $(srcdir)/demo/acinclude.m4
	cd $(srcdir)/demo && $(LN_S) ../libtool.m4 acinclude.m4
$(srcdir)/mdemo/acinclude.m4: libtool.m4
	rm -f $(srcdir)/mdemo/acinclude.m4
	cd $(srcdir)/mdemo && $(LN_S) ../libtool.m4 acinclude.m4
$(srcdir)/libltdl/acinclude.m4: libtool.m4
	rm -f $(srcdir)/libltdl/acinclude.m4
	cd $(srcdir)/libltdl && $(LN_S) ../libtool.m4 acinclude.m4

# Rules for rebuilding some of the demo source files.
$(srcdir)/demo/Makefile.in: demo/Makefile.am demo/configure.in demo/aclocal.m4
	cd $(srcdir)/demo && $(AUTOMAKE)

$(srcdir)/demo/configure: demo/configure.in demo/aclocal.m4
	cd $(srcdir)/demo && $(AUTOCONF)

$(srcdir)/demo/aclocal.m4: demo/configure.in demo/acinclude.m4
	cd $(srcdir)/demo && $(ACLOCAL)

$(srcdir)/mdemo/Makefile.in: mdemo/Makefile.am mdemo/configure.in mdemo/aclocal.m4
	cd $(srcdir)/mdemo && $(AUTOMAKE)

$(srcdir)/mdemo/configure: mdemo/configure.in mdemo/aclocal.m4
	cd $(srcdir)/mdemo && $(AUTOCONF)

$(srcdir)/mdemo/aclocal.m4: mdemo/configure.in mdemo/acinclude.m4
	cd $(srcdir)/mdemo && $(ACLOCAL)

$(srcdir)/libltdl/Makefile.in: libltdl/Makefile.am libltdl/configure.in libltdl/aclocal.m4
	cd $(srcdir)/libltdl && $(AUTOMAKE)

$(srcdir)/libltdl/configure: libltdl/configure.in libltdl/aclocal.m4
	cd $(srcdir)/libltdl && $(AUTOCONF)

$(srcdir)/libltdl/aclocal.m4: libltdl/configure.in libltdl/acinclude.m4
	cd $(srcdir)/libltdl && $(ACLOCAL)
