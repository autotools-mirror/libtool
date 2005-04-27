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

ACLOCAL_AMFLAGS  = -I m4

BUILD_SUBDIRS	= . libltdl
SUBDIRS		= $(BUILD_SUBDIRS)
DIST_SUBDIRS	= $(BUILD_SUBDIRS)
EXTRA_DIST	=

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
		-e 's,@nobase_pkgvdata_DATA\@,$(nobase_pkgvdata_DATA),g' \
		-e "s,@pkgvltdl_files\@,`echo $(ltdldatafiles)`,g" \
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
	$(M4SH) -B ./config libtoolize.m4sh > libtoolize.in

libtool: $(top_builddir)/config.status $(srcdir)/config/ltmain.sh \
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
	-e 's,@host_triplet\@,$(host_triplet),g' \
	-e 's,@pkgvdatadir\@,$(pkgvdatadir),g' \
	-e 's,@prefix\@,$(prefix),g' \
	-e "s,@configure_input\@,Generated from $$input; do not edit by hand,g"

timestamp = set dummy `$(MKSTAMP) < $(srcdir)/ChangeLog`; shift; \
	case $(VERSION) in \
	  *[acegikmoqsuwy]) TIMESTAMP=" $$1 $$2 $$3" ;; \
	  *) TIMESTAMP="" ;; \
	esac

sh_files	= config/general.m4sh config/getopt.m4sh
EXTRA_DIST     += bootstrap libtoolize.in config/ltmain.m4sh config/mkstamp \
		  $(sh_files) stamp-vcl ChangeLog.1996 ChangeLog.1997 \
		  ChangeLog.1998 ChangeLog.1999 ChangeLog.2000 ChangeLog.2001 \
		  ChangeLog.2002 ChangeLog.2003
CLEANFILES 	= libtool libtoolize \
		  libtoolize.tmp config/ltmain.tmp m4/ltversion.tmp
DISTCLEANFILES =

# These are required by libtoolize and must be executable when installed.
# Since _SCRIPTS gets the program transform applied we make them
# executable by hand
nobase_dist_pkgvdata_DATA = config/config.guess config/config.sub \
	config/ltmain.sh config/install-sh

# Everything that gets picked up by aclocal is automatically distributed,
# this is the list of macro files we install on the user's system.
nobase_pkgvdata_DATA = m4/argz.m4 m4/libtool.m4 m4/ltdl.m4 \
	m4/ltoptions.m4 m4/ltsugar.m4 m4/ltversion.m4

## We know that $(srcdir)/ChangeLog has been edited if stamp-vcl
## needs updating, so we assume we have write access to $(srcdir).
## If we try to maintain ./stamp-vcl to avoid writing to a possibly
## read-only $(srcdir), then when the two stamp-vcls differ, distcheck
## will try to update the one in the read-only source tree it makes.
MKSTAMP = $(SHELL) $(srcdir)/config/mkstamp
$(srcdir)/stamp-vcl: vcl-tmp clean-ltmain-sh ChangeLog
vcl-tmp:
	@set dummy `$(MKSTAMP) < $(srcdir)/ChangeLog`; shift; \
	echo "$$1" > vcl.tmp; \
	cmp -s vcl.tmp $(srcdir)/stamp-vcl \
	  || (echo "Updating stamp-vcl"; cp vcl.tmp $(srcdir)/stamp-vcl)
	-@rm -f vcl.tmp

## We used to build ltmain.sh in the build tree, but now it is created
## in the source tree by bootstrap.  This rule removes stale copies from
## previous builds left behind in the build tree, that would override the
## source tree version in current builds.
clean-ltmain-sh:
	@-test "$(srcdir)" = "$(top_builddir)" || \
	  rm -f "$(top_builddir)/config/ltmain.sh"

# We build ltversion.m4 here, instead of from config.status,
# because config.status is rerun each time one of configure's
# dependencies change and ltversion.m4 happens to be a configure
# dependency.  configure and ltversion.m4 would be rebuilt in
# a loop otherwise.
# Use `$(srcdir)/m4' for the benefit of non-GNU makes: this is
# how ltversion.m4 appears in our dependencies.
EXTRA_DIST += m4/ltversion.in m4/ltversion.m4
$(srcdir)/m4/ltversion.m4: m4/ltversion.in configure.ac $(srcdir)/stamp-vcl
	set dummy `$(MKSTAMP) < $(srcdir)/ChangeLog`; shift; \
	cd $(srcdir); \
	rm -f m4/ltversion.tmp; \
	serial=`echo $$1 | sed 's,^1[.],,g'`; \
	input="ltversion.in"; \
	$(edit) -e "s,@MACRO_REVISION\@,$$1,g" \
		-e "s,@MACRO_SERIAL\@,$$serial,g" \
		m4/ltversion.in > m4/ltversion.tmp; \
	chmod a-w m4/ltversion.tmp; \
	mv -f m4/ltversion.tmp m4/ltversion.m4

## And for similar reasons, ltmain.sh can't be built from config.status.
## !WARNING! If you edit this rule to change the contents of ltmain.sh,
##           you must `touch $(srcdir)/config/ltmain.in' from the
##           shell if you need ltmain.sh to be regenerated.  Ideally, we
##           should make this rule depend on Makefile but that will break
##           distcheck (at least) by rebuilding ltmain.sh in the source
##           tree whenever config.status regenerates the Makefile.
EXTRA_DIST += config/ltmain.sh
$(srcdir)/config/ltmain.sh: $(sh_files) config/ltmain.m4sh configure.ac \
				$(srcdir)/stamp-vcl
	$(timestamp); \
	cd $(srcdir); \
	rm -f config/ltmain.in config/ltmain.tmp config/ltmain.sh; \
	$(M4SH) -B ./config config/ltmain.m4sh > config/ltmain.in; \
	input="ltmain.m4sh"; \
	$(edit) -e "s,@TIMESTAMP\@,$$TIMESTAMP,g" \
		-e "s,@package_revision\@,$$1,g" \
		config/ltmain.in > config/ltmain.tmp; \
	rm -f config/ltmain.in; \
	chmod a-w config/ltmain.tmp; \
	mv -f config/ltmain.tmp config/ltmain.sh


## -------------- ##
## Documentation. ##
## -------------- ##

info_TEXINFOS		= doc/libtool.texi
libtool_TEXINFOS	= doc/PLATFORMS doc/fdl.texi doc/notes.texi
EXTRA_DIST	       += doc/notes.txt $(libtool_TEXINFOS)

all-local: $(srcdir)/doc/notes.txt

$(srcdir)/doc/notes.txt: $(srcdir)/doc/notes.texi
	cd $(srcdir)/doc && \
	  $(MAKEINFO) --plaintext $(MAKEINFOFLAGS) -o notes.txt notes.texi


## ------------- ##
## Installation. ##
## ------------- ##

## These are installed as a subdirectory of pkgdatadir so that
## libtoolize --ltdl can find them later:
ltdldatadir		= $(pkgvdatadir)/libltdl
ltdldatafiles		= COPYING.LIB README \
			  Makefile.am Makefile.in \
			  argz_.h argz.c \
			  configure.ac configure \
			  libltdl/lt__alloc.h \
			  libltdl/lt__dirent.h \
			  libltdl/lt__glibc.h \
			  libltdl/lt__private.h \
                          libltdl/lt__strl.h \
			  libltdl/lt_dlloader.h \
			  libltdl/lt_error.h \
                          libltdl/lt_system.h \
			  libltdl/slist.h \
			  loaders/dld_link.c \
			  loaders/dlopen.c \
			  loaders/dyld.c \
			  loaders/load_add_on.c \
			  loaders/loadlibrary.c \
			  loaders/preopen.c \
			  loaders/shl_load.c \
			  lt__alloc.c \
			  lt__dirent.c \
			  lt__strl.c \
			  lt_dlloader.c \
			  lt_error.c \
			  ltdl.c ltdl.h \
			  slist.c

install-data-local:
## Don't install over the top of an old pkgvdatadir
	-rm -rf $(DESTDIR)$(pkgvdatadir)
## Remove old pkgdatadir
	-rm -rf $(DESTDIR)$(pkgdatadir)
## Remove old macro definitions
	-rm -rf $(DESTDIR)$(aclocaldir)/ltdl.m4
	-rm -rf $(DESTDIR)$(aclocaldir)/libtool.m4
## To avoid spurious reconfiguration when the user installs these files
## with libtoolize, we have to preserve their timestamps carefully:
	$(mkinstalldirs) $(DESTDIR)$(ltdldatadir)
	( cd $(srcdir)/libltdl && $(AMTAR) chf - $(ltdldatafiles); ) \
	  | ( umask 0 && cd $(DESTDIR)$(ltdldatadir) && $(AMTAR) xf -; )

install-data-hook:
	chmod +x $(DESTDIR)$(pkgvdatadir)/config/config.guess
	chmod +x $(DESTDIR)$(pkgvdatadir)/config/config.sub
	chmod +x $(DESTDIR)$(pkgvdatadir)/config/install-sh


## ------------- ##
## Distribution. ##
## ------------- ##

## Make versioned links.  We only run the transform on the root name;
## then we make a versioned link with the transformed base name.  This
## seemed like the most reasonable approach.
install-exec-hook:
	@$(POST_INSTALL)
	@for p in $(bin_SCRIPTS); do \
	  f="`echo $$p|sed '$(transform)'`"; \
	  fv="$$f-$(APIVERSION)"; \
	  rm -f $(DESTDIR)$(bindir)/$$fv; \
	  echo " $(LN) $(DESTDIR)$(bindir)/$$f $(DESTDIR)$(bindir)/$$fv"; \
	  $(LN) $(DESTDIR)$(bindir)/$$f $(DESTDIR)$(bindir)/$$fv; \
	done

uninstall-hook:
	@for p in $(bin_SCRIPTS); do \
	  f="`echo $$p|sed '$(transform)'`"; \
	  fv="$$f-$(APIVERSION)"; \
	  rm -f $(DESTDIR)$(bindir)/$$fv; \
	done
	@for f in $(ltdldatafiles); do \
	  echo " rm -rf '$(DESTDIR)$(ltdldatadir)/$$f'"; \
	  rm -f "$(DESTDIR)$(ltdldatadir)/$$f"; \
	done


## Ship README.alpha only in alpha release, but renamed to README
dist-hook:
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
		  tests/stresstest.at \
		  tests/link-order.at \
		  tests/convenience.at \
		  tests/template.at

EXTRA_DIST     += $(TESTSUITE) $(TESTSUITE_AT) tests/package.m4

# Be sure to reexport important environment variables:
TESTS_ENVIRONMENT = MAKE="$(MAKE)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
	CPP="$(CPP)" CPPFLAGS="$(CPPFLAGS)" LD="$(LD)" LDFLAGS="$(LDFLAGS)" \
	LIBS="$(LIBS)" LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	OBJEXT="$(OBJEXT)" EXEEXT="$(EXEEXT)" CONFIG_SHELL="$(SHELL)" \
	CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" CXXCPP="$(CXXCPP)" \
	F77="$(F77)" FFLAGS="$(FFLAGS)" \
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

if HAVE_CXX
if HAVE_F77
TESTS = $(COMMON_TESTS) $(CXX_TESTS) $(F77_TESTS)
else
TESTS = $(COMMON_TESTS) $(CXX_TESTS)
endif
else
if HAVE_F77
TESTS = $(COMMON_TESTS) $(F77_TESTS)
else
TESTS = $(COMMON_TESTS)
endif
endif

tests/demo-conf.test: libtool

EXTRA_DIST     += tests/defs.in tests/defs.m4sh \
		  $(COMMON_TESTS) $(CXX_TESTS) $(F77_TESTS)
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
$(srcdir)/tests/defs.in: config/general.m4sh tests/defs.m4sh Makefile.am
	cd $(srcdir); \
	rm -f tests/defs.in; \
	$(M4SH) -B ./config tests/defs.m4sh > tests/defs.in

# We need to remove any files that the above tests created.
clean-local-legacy:
	-cd tests; \
	for dir in cdemo demo depdemo f77demo mdemo mdemo2 pdemo tagdemo; \
	do \
	    test -f $$dir/Makefile && ( cd $$dir && $(MAKE) distclean; ); \
	done
	rm -rf _inst

$(TESTS): tests/defs
DISTCLEANFILES += tests/defs
