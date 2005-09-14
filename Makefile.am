## Makefile.am -- Process this file with automake to produce Makefile.in
##
## Copyright (C) 2003, 2004, 2005 Free Software Foundation, Inc.
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## As a special exception to the GNU Lesser General Public License,
## if you distribute this file as part of a program or library that
## is built using GNU libtool, you may include it under the same
## distribution terms that you use for the rest of that program.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; see the file COPYING.  If not, write to
## the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
## Boston, MA 02110-1301, USA.

ACLOCAL_AMFLAGS  	= -I libltdl/m4

DIST_SUBDIRS		= .

BUILT_SOURCES		= libtool

CLEANFILES		=
MOSTLYCLEANFILES	=
DISTCLEANFILES		=

EXTRA_DIST		= libltdl/COPYING.LIB \
			  libltdl/Makefile.am \
			  libltdl/Makefile.in \
			  libltdl/README \
			  libltdl/config-h.in \
			  libltdl/configure \
			  libltdl/configure.ac \
			  libltdl/aclocal.m4 \
			  libltdl/m4/lt~obsolete.m4

auxdir			= libltdl/config
m4dir			= libltdl/m4

# Using `cd' in backquotes may print the directory name, use this instead:
lt__cd		= CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd


## ---------------- ##
## Libtool scripts. ##
## ---------------- ##

# The libtool distributor and the standalone libtool script.
bin_SCRIPTS = libtoolize libtool

libtoolize: $(srcdir)/libtoolize.in
	rm -f libtoolize.tmp libtoolize
	$(timestamp); \
	input="libtoolize.m4sh"; \
	$(edit) -e "s,@TIMESTAMP\@,$$TIMESTAMP,g" \
		-e 's,@aclocal_DATA\@,$(aclocalfiles),g' \
		-e "s,@pkgltdl_files\@,$(ltdldatafiles),g" \
		-e "s,@pkgconfig_files\@,$(auxfiles),g" \
		$(srcdir)/libtoolize.in > libtoolize.tmp
	chmod a+x libtoolize.tmp
	chmod a-w libtoolize.tmp
	mv -f libtoolize.tmp libtoolize

# Use `$(srcdir)' for the benefit of non-GNU makes: this is
# how libtoolize.in appears in our dependencies.
EXTRA_DIST += libtoolize.m4sh
$(srcdir)/libtoolize.in: $(sh_files) libtoolize.m4sh Makefile.am
	cd $(srcdir); \
	rm -f libtoolize.in; \
	$(M4SH) -B $(auxdir) libtoolize.m4sh > libtoolize.in

libtool: $(top_builddir)/config.status $(srcdir)/$(auxdir)/ltmain.sh \
	 $(srcdir)/stamp-vcl
	cd $(top_builddir) && $(SHELL) ./config.status $@

.PHONY: configure-subdirs
configure-subdirs distdir: $(DIST_MAKEFILE_LIST)
@DIST_MAKEFILE_LIST@:
	dir=`echo $@ | sed 's,^[^/]*$$,.,;s,/[^/]*$$,,'`; \
	test -d $$dir || mkdir $$dir || exit 1; \
	abs_srcdir=`$(lt__cd) $(srcdir) && pwd`; \
	(cd $$dir && $$abs_srcdir/$$dir/configure) || exit 1


# ---------- #
# Bootstrap. #
# ---------- #

edit = sed \
	-e 's,@EGREP\@,$(EGREP),g' \
	-e 's,@FGREP\@,$(FGREP),g' \
	-e 's,@GREP\@,$(GREP),g' \
	-e 's,@LN_S\@,$(LN_S),g' \
	-e 's,@MACRO_VERSION\@,$(VERSION),g' \
	-e 's,@PACKAGE\@,$(PACKAGE),g' \
	-e 's,@PACKAGE_BUGREPORT\@,$(PACKAGE_BUGREPORT),g' \
	-e 's,@PACKAGE_NAME\@,$(PACKAGE),g' \
	-e 's,@PACKAGE_STRING\@,$(PACKAGE) $(VERSION),g' \
	-e 's,@PACKAGE_TARNAME\@,$(PACKAGE),g' \
	-e 's,@PACKAGE_VERSION\@,$(VERSION),g' \
	-e 's,@SED\@,$(SED),g' \
	-e 's,@VERSION\@,$(VERSION),g' \
	-e 's,@aclocaldir\@,$(aclocaldir),g' \
	-e 's,@datadir\@,$(datadir),g' \
	-e 's,@pkgdatadir\@,$(pkgdatadir),g' \
	-e 's,@host_triplet\@,$(host_triplet),g' \
	-e 's,@prefix\@,$(prefix),g' \
	-e "s,@configure_input\@,Generated from $$input; do not edit by hand,g"

timestamp = set dummy `$(MKSTAMP) < $(srcdir)/ChangeLog`; shift; \
	case $(VERSION) in \
	  *[acegikmoqsuwy]) TIMESTAMP=" $$1 $$2 $$3" ;; \
	  *) TIMESTAMP="" ;; \
	esac

sh_files	= $(auxdir)/general.m4sh $(auxdir)/getopt.m4sh
EXTRA_DIST     += bootstrap libtoolize.in $(auxdir)/ltmain.m4sh \
		  $(auxdir)/mkstamp $(sh_files) stamp-vcl \
		  ChangeLog.1996 ChangeLog.1997 ChangeLog.1998 \
		  ChangeLog.1999 ChangeLog.2000 ChangeLog.2001 \
		  ChangeLog.2002 ChangeLog.2003 ChangeLog.2004
CLEANFILES     += libtool libtoolize libtoolize.tmp \
		  $(auxdir)/ltmain.tmp $(m4dir)/ltversion.tmp

## We know that $(srcdir)/ChangeLog has been edited if stamp-vcl
## needs updating, so we assume we have write access to $(srcdir).
## If we try to maintain ./stamp-vcl to avoid writing to a possibly
## read-only $(srcdir), then when the two stamp-vcls differ, distcheck
## will try to update the one in the read-only source tree it makes.
MKSTAMP = $(SHELL) $(srcdir)/$(auxdir)/mkstamp
$(srcdir)/stamp-vcl: vcl-tmp clean-ltmain-sh ChangeLog
vcl-tmp:
	@set dummy `$(MKSTAMP) < $(srcdir)/ChangeLog`; shift; \
	echo "$$1" > vcl.tmp; \
	diff vcl.tmp $(srcdir)/stamp-vcl >/dev/null \
	  || (echo "Updating stamp-vcl"; cp vcl.tmp $(srcdir)/stamp-vcl)
	-@rm -f vcl.tmp

## We used to build ltmain.sh in the build tree, but now it is created
## in the source tree by bootstrap.  This rule removes stale copies from
## previous builds left behind in the build tree, that would override the
## source tree version in current builds.
clean-ltmain-sh:
	@-test "$(srcdir)" = "$(top_builddir)" || \
	  rm -f "$(top_builddir)/$(auxdir)/ltmain.sh"

# We build ltversion.m4 here, instead of from config.status,
# because config.status is rerun each time one of configure's
# dependencies change and ltversion.m4 happens to be a configure
# dependency.  configure and ltversion.m4 would be rebuilt in
# a loop otherwise.
# Use `$(srcdir)/m4' for the benefit of non-GNU makes: this is
# how ltversion.m4 appears in our dependencies.
EXTRA_DIST += $(m4dir)/ltversion.in $(m4dir)/ltversion.m4
$(srcdir)/$(m4dir)/ltversion.m4: $(m4dir)/ltversion.in configure.ac $(srcdir)/stamp-vcl
	set dummy `$(MKSTAMP) < $(srcdir)/ChangeLog`; shift; \
	cd $(srcdir); \
	rm -f $(m4dir)/ltversion.tmp; \
	serial=`echo $$1 | sed 's,^1[.],,g'`; \
	input="ltversion.in"; \
	$(edit) -e "s,@MACRO_REVISION\@,$$1,g" \
		-e "s,@MACRO_SERIAL\@,$$serial,g" \
		$(m4dir)/ltversion.in > $(m4dir)/ltversion.tmp; \
	chmod a-w $(m4dir)/ltversion.tmp; \
	mv -f $(m4dir)/ltversion.tmp $(m4dir)/ltversion.m4

## And for similar reasons, ltmain.sh can't be built from config.status.
## !WARNING! If you edit this rule to change the contents of ltmain.sh,
##           you must `touch $(srcdir)/$(auxdir)/ltmain.in' from the
##           shell if you need ltmain.sh to be regenerated.  Ideally, we
##           should make this rule depend on Makefile but that will break
##           distcheck (at least) by rebuilding ltmain.sh in the source
##           tree whenever config.status regenerates the Makefile.
EXTRA_DIST += $(auxdir)/ltmain.sh
$(srcdir)/$(auxdir)/ltmain.sh: $(sh_files) $(auxdir)/ltmain.m4sh configure.ac \
				$(srcdir)/stamp-vcl
	$(timestamp); \
	cd $(srcdir); \
	rm -f $(auxdir)/ltmain.in $(auxdir)/ltmain.tmp \
	    $(auxdir)/ltmain.sh; \
	$(M4SH) -B $(auxdir) $(auxdir)/ltmain.m4sh \
	    > $(auxdir)/ltmain.in; \
	input="ltmain.m4sh"; \
	$(edit) -e "s,@TIMESTAMP\@,$$TIMESTAMP,g" \
		-e "s,@package_revision\@,$$1,g" \
		$(auxdir)/ltmain.in > $(auxdir)/ltmain.tmp; \
	rm -f $(auxdir)/ltmain.in; \
	chmod a-w $(auxdir)/ltmain.tmp; \
	mv -f $(auxdir)/ltmain.tmp $(auxdir)/ltmain.sh

$(srcdir)/libltdl/Makefile.am: Makefile.am
	cd $(srcdir); \
	in=Makefile.am; out=libltdl/Makefile.am; \
	rm -f $$out; \
	$(SED) -n '/^.. Makefile.am -- /,/^.. Boston, MA/p' $$in > $$out; \
	{ echo 'ACLOCAL_AMFLAGS = -I m4'; \
	  echo 'AUTOMAKE_OPTIONS = foreign'; \
	  echo 'BUILT_SOURCES ='; \
	  echo 'EXTRA_DIST ='; \
	  echo 'CLEANFILES ='; \
	  echo 'MOSTLYCLEANFILES ='; \
	} >> $$out; \
	$(SED) -n '/^. %%% BEGIN /,/^. %%% END / \
	    { s,libltdl_,,; s,libltdl/,,; s,: libltdl/,: ,; \
	      s,\$$(libltdl_,$$(,; p; }' $$in >> $$out;
	chmod a-w $(srcdir)/libltdl/Makefile.am

$(srcdir)/libltdl/Makefile.in: libltdl/Makefile.am
	cd $(srcdir)/libltdl && $(AUTOMAKE) Makefile


## -------- ##
## Libltdl. ##
## -------- ##

# %%% BEGIN libltdl/Makefile.am

DEFS			= -DHAVE_CONFIG_H="<$(CONFIG_H)>" -DLTDL

# -I$(srcdir) is needed for user that built libltdl with a sub-Automake
# (not as a sub-package!) using 'nostdinc':
AM_CPPFLAGS		= -I. -I$(srcdir) -Ilibltdl -I$(srcdir)/libltdl \
			  -I$(srcdir)/libltdl/libltdl
AM_LDFLAGS		= -no-undefined
VERSION_INFO		= -version-info 6:1:0

noinst_LTLIBRARIES	= $(LT_DLLOADERS)

if INSTALL_LTDL
ltdlincludedir		= $(includedir)/libltdl
ltdlinclude_HEADERS	= libltdl/libltdl/lt_system.h \
			  libltdl/libltdl/lt_error.h \
			  libltdl/libltdl/lt_dlloader.h
include_HEADERS		= libltdl/ltdl.h
lib_LTLIBRARIES		= libltdl/libltdl.la
endif

if CONVENIENCE_LTDL
noinst_LTLIBRARIES     += libltdl/libltdlc.la
endif

libltdl_libltdl_la_SOURCES = libltdl/libltdl/lt__alloc.h \
			  libltdl/libltdl/lt__dirent.h \
			  libltdl/libltdl/lt__glibc.h \
			  libltdl/libltdl/lt__private.h \
			  libltdl/libltdl/lt__strl.h \
			  libltdl/libltdl/lt_dlloader.h \
			  libltdl/libltdl/lt_error.h \
	                  libltdl/libltdl/lt_system.h \
			  libltdl/libltdl/slist.h \
			  libltdl/loaders/preopen.c \
			  libltdl/lt__alloc.c \
			  libltdl/lt_dlloader.c \
			  libltdl/lt_error.c \
			  libltdl/ltdl.c \
			  libltdl/ltdl.h \
			  libltdl/slist.c

libltdl_libltdl_la_CPPFLAGS	= -DLTDLOPEN=$(LTDLOPEN) $(AM_CPPFLAGS)
libltdl_libltdl_la_LDFLAGS	= $(AM_LDFLAGS) $(VERSION_INFO) $(LT_DLPREOPEN)
libltdl_libltdl_la_LIBADD	= $(LTLIBOBJS)
libltdl_libltdl_la_DEPENDENCIES	= $(LT_DLLOADERS) $(LTLIBOBJS)

libltdl_libltdlc_la_SOURCES	= $(libltdl_libltdl_la_SOURCES)
libltdl_libltdlc_la_CPPFLAGS	= -DLTDLOPEN=$(LTDLOPEN)c $(AM_CPPFLAGS)
libltdl_libltdlc_la_LDFLAGS	= $(AM_LDFLAGS) $(LT_DLPREOPEN)
libltdl_libltdlc_la_LIBADD	= $(libltdl_libltdl_la_LIBADD)
libltdl_libltdlc_la_DEPENDENCIES= $(libltdl_libltdl_la_DEPENDENCIES)

## The loaders are preopened by libltdl, itself always built from
## pic-objects (either as a shared library, or a convenience library),
## so the loaders themselves must be made from pic-objects too.  We
## use convenience libraries for that purpose:
EXTRA_LTLIBRARIES		= libltdl/dlopen.la \
				  libltdl/dld_link.la \
				  libltdl/dyld.la \
				  libltdl/load_add_on.la \
				  libltdl/loadlibrary.la \
				  libltdl/shl_load.la

libltdl_dlopen_la_SOURCES	= libltdl/loaders/dlopen.c
libltdl_dlopen_la_LDFLAGS	= -module -avoid-version
libltdl_dlopen_la_LIBADD 	= $(LIBADD_DLOPEN)

libltdl_dld_link_la_SOURCES	= libltdl/loaders/dld_link.c
libltdl_dld_link_la_LDFLAGS	= -module -avoid-version
libltdl_dld_link_la_LIBADD	= -ldld

libltdl_dyld_la_SOURCES		= libltdl/loaders/dyld.c
libltdl_dyld_la_LDFLAGS		= -module -avoid-version

libltdl_load_add_on_la_SOURCES	= libltdl/loaders/load_add_on.c
libltdl_load_add_on_la_LDFLAGS	= -module -avoid-version

libltdl_loadlibrary_la_SOURCES	= libltdl/loaders/loadlibrary.c
libltdl_loadlibrary_la_LDFLAGS	= -module -avoid-version

libltdl_shl_load_la_SOURCES	= libltdl/loaders/shl_load.c
libltdl_shl_load_la_LDFLAGS	= -module -avoid-version
libltdl_shl_load_la_LIBADD	= $(LIBADD_SHL_LOAD)

## Make sure these will be cleaned even when they're not built by default:
CLEANFILES		       += libltdl/libltdl.la \
				  libltdl/libltdlc.la \
				  libltdl/libdlloader.la

## Automake-1.9.6 doesn't clean subdir AC_LIBOBJ compiled objects
## automatically:
CLEANFILES		       += $(LIBOBJS) $(LTLIBOBJS)


## --------------------------- ##
## Gnulib Makefile.am snippets ##
## --------------------------- ##

BUILT_SOURCES	+= libltdl/$(ARGZ_H)
EXTRA_DIST	+= libltdl/argz_.h

# We need the following in order to create an <argz.h> when the system
# doesn't have one that works with the given compiler.
all-local $(lib_OBJECTS): libltdl/$(ARGZ_H)
libltdl/argz.h: libltdl/argz_.h
	cp $(srcdir)/libltdl/argz_.h $@-t
	mv $@-t $@
MOSTLYCLEANFILES += libltdl/argz.h \
		    libltdl/argz.h-t

# %%% END libltdl/Makefile.am

if ! SUBDIR_LIBOBJS
## workaround for Autoconf 2.59, Automake 1.9.6:
## we include these files twice, because of missing LIBOBJDIR support.
EXTRA_DIST += \
	argz.c libltdl/argz.c \
	lt__dirent.c libltdl/lt__dirent.c \
	lt__strl.c libltdl/lt__strl.c
endif


## -------------- ##
## Documentation. ##
## -------------- ##

info_TEXINFOS		= doc/libtool.texi
libtool_TEXINFOS	= doc/PLATFORMS doc/fdl.texi doc/notes.texi
EXTRA_DIST	       += doc/notes.txt $(libtool_TEXINFOS)

all-local: $(srcdir)/doc/notes.txt

$(srcdir)/doc/notes.txt: $(srcdir)/doc/notes.texi
	cd $(srcdir)/doc && \
	  $(MAKEINFO) --no-headers $(MAKEINFOFLAGS) -o notes.txt notes.texi


## ------------- ##
## Installation. ##
## ------------- ##

# These are required by libtoolize and must be executable when installed.
# The timestamps on these files must be preserved carefully so we install,
# uninstall and set executable with custom rules here.
auxexefiles	= config/compile config/config.guess config/config.sub \
		  config/depcomp config/install-sh config/missing
auxfiles	= $(auxexefiles) config/ltmain.sh

# Everything that gets picked up by aclocal is automatically distributed,
# this is the list of macro files we install on the user's system.
aclocalfiles	= m4/argz.m4 m4/libtool.m4 m4/ltdl.m4 m4/ltoptions.m4 \
		  m4/ltsugar.m4 m4/ltversion.m4

## These are installed as a subdirectory of pkgdatadir so that
## libtoolize --ltdl can find them later:
ltdldatafiles	= libltdl/COPYING.LIB \
		  libltdl/README \
		  libltdl/Makefile.am \
		  libltdl/Makefile.in \
		  libltdl/configure.ac \
		  libltdl/aclocal.m4 \
		  libltdl/config-h.in \
		  libltdl/configure \
		  libltdl/argz_.h \
		  libltdl/argz.c \
		  libltdl/loaders/dld_link.c \
		  libltdl/loaders/dlopen.c \
		  libltdl/loaders/dyld.c \
		  libltdl/loaders/load_add_on.c \
		  libltdl/loaders/loadlibrary.c \
		  libltdl/loaders/shl_load.c \
		  libltdl/lt__dirent.c \
		  libltdl/lt__strl.c \
		  $(libltdl_libltdl_la_SOURCES)

install-data-local: libltdl/Makefile.in
	@$(NORMAL_INSTALL)
## Don't install over the top of an old pkgdatadir
	-rm -rf $(DESTDIR)$(pkgdatadir)/*
## To avoid spurious reconfiguration when the user installs these files
## with libtoolize, we have to install them in the correct order:
## First, put a copy of the libtool m4 macros in the aclocal dir
	$(mkinstalldirs) $(DESTDIR)$(aclocaldir)
	@cd $(srcdir)/$(m4dir) && \
	list='$(aclocalfiles)'; for p in $$list; do \
	  f=`echo "$$p" | sed 's|^.*/||'`; \
	  echo " $(INSTALL_DATA) '$$f' '$(DESTDIR)$(aclocaldir)/$$f'"; \
	  $(INSTALL_DATA) "$$f" "$(DESTDIR)$(aclocaldir)/$$f"; \
	done; \
## install the helper scripts
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/config
	@cd $(srcdir)/libltdl && \
	list='$(auxfiles)' && for p in $$list; do \
	  echo " $(INSTALL_SCRIPT) '$$p' '$(DESTDIR)$(pkgdatadir)/$$p'"; \
	  $(INSTALL_SCRIPT) "$$p" "$(DESTDIR)$(pkgdatadir)/$$p"; \
	done
## install the libltdl files
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/libltdl
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/libltdl/libltdl
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/libltdl/loaders
	@cd $(srcdir) && \
	list='$(ltdldatafiles)' && for p in $$list; do \
	  echo " $(INSTALL_DATA) '$$p' '$(DESTDIR)$(pkgdatadir)/$$p'"; \
	  $(INSTALL_DATA) "$$p" "$(DESTDIR)$(pkgdatadir)/$$p"; \
	done
	-chmod a+x $(DESTDIR)$(pkgdatadir)/libltdl/configure


## ------------- ##
## Distribution. ##
## ------------- ##

uninstall-hook:
	@$(NORMAL_UNINSTALL)
	@list='$(ltdldatafiles) $(auxfiles)'; for f in $$list; do \
	  echo " rm -f '$(DESTDIR)$(pkgdatadir)/$$f'"; \
	  rm -f "$(DESTDIR)$(pkgdatadir)/$$f"; \
	done
	@for p in $(aclocalfiles); do \
	  f=`echo "$$p" | sed 's|^.*/||'`; \
	  echo " rm -f '$(DESTDIR)$(aclocaldir)/$$f'"; \
	  rm -f "$(DESTDIR)$(aclocaldir)/$$f"; \
	done

dist-hook:
## Ship README.alpha only in alpha release, but renamed to README
	-@test -f $(distdir)/README.alpha && \
	case $(VERSION) in \
	  *[a-z]) mv $(distdir)/README.alpha $(distdir)/README ;; \
	  *)	  rm -f $(distdir)/README.alpha ;; \
	esac


## ----------- ##
## Test suite. ##
## ----------- ##

TESTSUITE	= tests/testsuite
TESTSUITE_AT	= tests/testsuite.at \
		  tests/am-subdir.at \
		  tests/duplicate_members.at \
		  tests/inherited_flags.at \
		  tests/libtoolize.at \
		  tests/standalone.at \
		  tests/stresstest.at \
		  tests/link-order.at \
		  tests/convenience.at \
		  tests/early-libtool.at \
		  tests/template.at

EXTRA_DIST     += $(TESTSUITE) $(TESTSUITE_AT) tests/package.m4

# Be sure to reexport important environment variables:
TESTS_ENVIRONMENT = MAKE="$(MAKE)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
	CPP="$(CPP)" CPPFLAGS="$(CPPFLAGS)" LD="$(LD)" LDFLAGS="$(LDFLAGS)" \
	LIBS="$(LIBS)" LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	OBJEXT="$(OBJEXT)" EXEEXT="$(EXEEXT)" \
	SHELL="$(SHELL)" CONFIG_SHELL="$(SHELL)" \
	CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" CXXCPP="$(CXXCPP)" \
	F77="$(F77)" FFLAGS="$(FFLAGS)" \
	FC="$(FC)" FCFLAGS="$(FCFLAGS)" \
	GCJ="$(GCJ)" GCJFLAGS="$(GCJFLAGS)"

check-recursive: $(srcdir)/$(TESTSUITE)

# Use `$(srcdir)' for the benefit of non-GNU makes: this is
# how `testsuite' appears in our dependencies.
$(srcdir)/$(TESTSUITE): tests/package.m4 $(TESTSUITE_AT)
	cd $(srcdir)/tests; \
	$(AUTOTEST) testsuite.at -o testsuite

$(srcdir)/tests/package.m4: $(srcdir)/configure.ac
	{ \
	  echo '# Signature of the current package.'; \
	  echo 'm4_define([AT_PACKAGE_NAME],      [@PACKAGE_NAME@])'; \
	  echo 'm4_define([AT_PACKAGE_TARNAME],   [@PACKAGE_TARNAME@])'; \
	  echo 'm4_define([AT_PACKAGE_VERSION],   [@PACKAGE_VERSION@])'; \
	  echo 'm4_define([AT_PACKAGE_STRING],    [@PACKAGE_STRING@])'; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [@PACKAGE_BUGREPORT@])'; \
	} | $(edit) > $(srcdir)/tests/package.m4

tests/atconfig: config.status
	$(SHELL) ./config.status tests/atconfig

DISTCLEANFILES += tests/atconfig

CD_TESTDIR	= abs_srcdir=`$(lt__cd) $(srcdir) && pwd`; cd tests

# Hook the test suite into the check rule
check-local: tests/atconfig $(srcdir)/$(TESTSUITE)
	$(CD_TESTDIR); \
	$(TESTS_ENVIRONMENT) $(SHELL) $$abs_srcdir/$(TESTSUITE) $(TESTSUITE_FLAGS)

# Run the test suite on the *installed* tree.
installcheck-local:
	$(CD_TESTDIR); \
	$(TESTS_ENVIRONMENT) $(SHELL) $$abs_srcdir/$(TESTSUITE) $(TESTSUITE_FLAGS) AUTOTEST_PATH=$(exec_prefix)/bin

# We need to remove any file droppings left behind by testsuite
clean-local: clean-local-legacy
	-$(CD_TESTDIR); \
	test -f $$abs_srcdir/$(TESTSUITE) && \
	    $(SHELL) $$abs_srcdir/$(TESTSUITE) --clean


## ------------- ##
## Legacy tests. ##
## ------------- ##

# !WARNING! Don't add any new tests here, we are migrating to an
#           Autotest driven framework, please add new test cases
#           using the new framework above.  When the migration is
#           complete this section should be removed.

CXX_TESTS = \
	tests/tagdemo-static.test tests/tagdemo-make.test \
	tests/tagdemo-exec.test tests/tagdemo-conf.test \
	tests/tagdemo-make.test tests/tagdemo-exec.test \
	tests/tagdemo-shared.test tests/tagdemo-make.test \
	tests/tagdemo-exec.test tests/tagdemo-undef.test \
	tests/tagdemo-make.test tests/tagdemo-exec.test

F77_TESTS = \
	tests/f77demo-static.test tests/f77demo-make.test \
	tests/f77demo-exec.test tests/f77demo-conf.test \
	tests/f77demo-make.test tests/f77demo-exec.test \
	tests/f77demo-shared.test tests/f77demo-make.test \
	tests/f77demo-exec.test

FC_TESTS = \
	tests/fcdemo-static.test tests/fcdemo-make.test \
	tests/fcdemo-exec.test tests/fcdemo-conf.test \
	tests/fcdemo-make.test tests/fcdemo-exec.test \
	tests/fcdemo-shared.test tests/fcdemo-make.test \
	tests/fcdemo-exec.test

COMMON_TESTS = \
	tests/link.test tests/link-2.test tests/nomode.test \
	tests/objectlist.test tests/quote.test tests/sh.test \
	tests/suffix.test tests/tagtrace.test \
	tests/cdemo-static.test tests/cdemo-make.test tests/cdemo-exec.test \
	tests/demo-static.test tests/demo-make.test tests/demo-exec.test \
	tests/demo-inst.test tests/demo-unst.test \
	tests/depdemo-static.test tests/depdemo-make.test \
	tests/depdemo-exec.test tests/depdemo-inst.test \
	tests/depdemo-unst.test \
	tests/mdemo-static.test tests/mdemo-make.test tests/mdemo-exec.test \
	tests/mdemo-inst.test tests/mdemo-unst.test \
	tests/cdemo-conf.test tests/cdemo-make.test tests/cdemo-exec.test \
	tests/demo-conf.test tests/demo-make.test tests/demo-exec.test \
	tests/demo-inst.test tests/demo-unst.test tests/demo-deplibs.test \
	tests/depdemo-conf.test tests/depdemo-make.test \
	tests/depdemo-exec.test tests/depdemo-inst.test \
	tests/depdemo-unst.test \
	tests/mdemo-conf.test tests/mdemo-make.test tests/mdemo-exec.test \
	tests/mdemo-inst.test tests/mdemo-unst.test tests/mdemo-dryrun.test \
	tests/mdemo2-conf.test tests/mdemo2-make.test tests/mdemo2-exec.test \
	tests/pdemo-conf.test tests/pdemo-make.test tests/pdemo-exec.test \
	tests/pdemo-inst.test \
	tests/demo-nofast.test tests/demo-make.test tests/demo-exec.test \
	tests/demo-inst.test tests/demo-unst.test \
	tests/depdemo-nofast.test tests/depdemo-make.test \
	tests/depdemo-exec.test tests/depdemo-inst.test \
	tests/depdemo-unst.test \
	tests/demo-pic.test tests/demo-make.test tests/demo-exec.test \
	tests/demo-nopic.test tests/demo-make.test tests/demo-exec.test \
	tests/cdemo-shared.test tests/cdemo-make.test tests/cdemo-exec.test \
	tests/demo-shared.test tests/demo-make.test tests/demo-exec.test \
	tests/demo-inst.test tests/demo-hardcode.test tests/demo-relink.test \
	tests/demo-noinst-link.test tests/demo-unst.test \
	tests/depdemo-shared.test tests/depdemo-make.test \
	tests/depdemo-exec.test tests/depdemo-inst.test \
	tests/depdemo-relink.test tests/depdemo-unst.test \
	tests/mdemo-shared.test tests/mdemo-make.test tests/mdemo-exec.test \
	tests/mdemo-inst.test tests/mdemo-unst.test \
	tests/cdemo-undef.test tests/cdemo-make.test tests/cdemo-exec.test

TESTS = $(COMMON_TESTS)
if HAVE_CXX
TESTS += $(CXX_TESTS)
endif
if HAVE_F77
TESTS += $(F77_TESTS)
endif
if HAVE_FC
TESTS += $(FC_TESTS)
endif

tests/demo-conf.test: libtool

EXTRA_DIST     += tests/defs.in tests/defs.m4sh \
		  $(COMMON_TESTS) $(CXX_TESTS) $(F77_TESTS) $(FC_TESTS)
DIST_SUBDIRS   += $(CONF_SUBDIRS)

# The defs script shouldn't be recreated whenever the Makefile is
# regenerated since the source tree can be read-only.
check-recursive: tests/defs
tests/defs: $(srcdir)/tests/defs.in
	rm -f tests/defs.tmp tests/defs; \
	input="defs.m4sh"; \
	$(edit) $(srcdir)/tests/defs.in > tests/defs.tmp; \
	mv -f tests/defs.tmp tests/defs

# Use `$(srcdir)/tests' for the benefit of non-GNU makes: this is
# how defs.in appears in our dependencies.
$(srcdir)/tests/defs.in: $(auxdir)/general.m4sh tests/defs.m4sh Makefile.am
	cd $(srcdir); \
	rm -f tests/defs.in; \
	$(M4SH) -B $(auxdir) tests/defs.m4sh > tests/defs.in

# We need to remove any files that the above tests created.
clean-local-legacy:
	-cd tests; \
	for dir in cdemo demo depdemo f77demo fcdemo mdemo mdemo2 pdemo tagdemo; \
	do \
	    test -f $$dir/Makefile && ( cd $$dir && $(MAKE) distclean; ); \
	done
	rm -rf _inst

$(TESTS): tests/defs
DISTCLEANFILES += tests/defs
