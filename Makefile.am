## Process Makefile.am with automake to create Makefile.in.
## Gordon Matzigkeit <gord@gnu.ai.mit.edu>, 1996
AUTOMAKE_OPTIONS = gnits
SUBDIRS = doc tests

# Distribute ltconfig and ltmain.sh so that the demo directory works.
EXTRA_DIST = libtool.m4 libtoolize.in ltconfig ltconfig.in \
	ltmain.sh ltmain.sh.in README-automake
CLEANFILES = libtool libtoolize

# Files in the demo subdirectory that go in the distribution.
demo_distfiles = Makefile.in Makefile.am README aclocal.m4 \
	ansi2knr.1 ansi2knr.c \
	configure configure.in foo.c foo.h hello.c main.c \
	run.test

# These are required by libtoolize.
pkgdata_SCRIPTS = config.guess config.sub ltconfig
pkgdata_DATA = ltmain.sh

# This macro files should be visible to Automake's aclocal.
aclocaldir = @aclocaldir@
aclocal_DATA = libtool.m4

# The standalone libtool script, and the libtool distributor.
bin_SCRIPTS = libtool libtoolize

libtool: ltconfig
	@echo 'WARNING: Warnings from ltconfig can be ignored. :-)'
	$(srcdir)/ltconfig --srcdir=$(srcdir) $(pkgdatadir)/ltmain.sh

# These depend on configure.in for version numbers.
libtoolize: libtoolize.in configure.in
	CONFIG_FILES=libtoolize CONFIG_HEADERS= $(top_builddir)/config.status
	chmod +x libtoolize

$(srcdir)/ltconfig: ltconfig.in configure.in
	CONFIG_FILES=ltconfig CONFIG_HEADERS= $(top_builddir)/config.status
	chmod +x ltconfig

$(srcdir)/ltmain.sh: ltmain.sh.in configure.in
	CONFIG_FILES=ltmain.sh CONFIG_HEADERS= $(top_builddir)/config.status

# Distribute the demo subdirectory.
dist-hook:
	mkdir $(distdir)/demo
	-chmod 755 $(distdir)/demo
	here=`pwd`; distdir=`cd $(distdir) && pwd` \
	  && cd $(srcdir)/demo \
	  && automake --include-deps --build-dir=$$here/demo --srcdir-name=$(srcdir)/demo --output-dir=$$distdir/demo
	@for file in $(demo_distfiles); do \
	  d=$(srcdir)/demo; \
	  test -f $(distdir)/demo/$$file \
	  || ln $$d/$$file $(distdir)/demo/$$file 2> /dev/null \
	  || cp -p $$d/$$file $(distdir)/demo/$$file; \
	done

