## Process this file with automake to produce Makefile.in

CXX_TESTS = \
	tagdemo-static.test tagdemo-make.test tagdemo-exec.test \
	tagdemo-conf.test tagdemo-make.test tagdemo-exec.test \
	tagdemo-shared.test tagdemo-make.test tagdemo-exec.test

F77_TESTS = \
	f77demo-static.test f77demo-make.test f77demo-exec.test \
	f77demo-conf.test f77demo-make.test f77demo-exec.test \
	f77demo-shared.test f77demo-make.test f77demo-exec.test

COMMON_TESTS = \
	assign.test link.test link-2.test nomode.test \
	quote.test sh.test suffix.test tagtrace.test \
	cdemo-static.test cdemo-make.test cdemo-exec.test \
	demo-static.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test \
	depdemo-static.test depdemo-make.test depdemo-exec.test \
	depdemo-inst.test depdemo-unst.test \
	mdemo-static.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test \
	cdemo-conf.test cdemo-make.test cdemo-exec.test \
	demo-conf.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test demo-deplibs.test \
	depdemo-conf.test depdemo-make.test depdemo-exec.test \
	depdemo-inst.test depdemo-unst.test \
	mdemo-conf.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test mdemo-dryrun.test \
	mdemo2-conf.test mdemo2-make.test mdemo2-exec.test \
	pdemo-conf.test pdemo-make.test pdemo-exec.test \
	pdemo-inst.test \
	demo-nofast.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test \
	depdemo-nofast.test depdemo-make.test depdemo-exec.test \
	depdemo-inst.test depdemo-unst.test \
	demo-pic.test demo-make.test demo-exec.test \
	demo-nopic.test demo-make.test demo-exec.test \
	cdemo-shared.test cdemo-make.test cdemo-exec.test \
	demo-shared.test demo-make.test demo-exec.test demo-inst.test \
	demo-hardcode.test demo-relink.test demo-noinst-link.test \
	demo-unst.test \
	depdemo-shared.test depdemo-make.test depdemo-exec.test \
	depdemo-inst.test depdemo-relink.test depdemo-unst.test \
	mdemo-shared.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test

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

demo-conf.test: $(top_builddir)/libtool

$(top_builddir)/libtool:
	cd $(top_builddir) && $(MAKE) all

# Be sure to reexport important environment variables.
TESTS_ENVIRONMENT = MAKE="$(MAKE)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
	CPPFLAGS="$(CPPFLAGS)" LD="$(LD)" LDFLAGS="$(LDFLAGS)" \
	LIBS="$(LIBS)" LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	OBJEXT="$(OBJEXT)" EXEEXT="$(EXEEXT)" FFLAGS="$(FFLAGS)"

EXTRA_DIST = defs $(COMMON_TESTS) $(CXX_TESTS) $(F77_TESTS)
DIST_SUBDIRS = $(CONF_SUBDIRS)

# FIXME: Automake-1.7b (at least) only honours DIST_SUBDIRS if SUBDIRS is
#        also set.  Remove this line when that bug is fixed.
SUBDIRS = .

# We need to remove any files that the above tests created.
clean-local:
	-for dir in cdemo demo depdemo f77demo mdemo mdemo2 pdemo tagdemo;  \
	do								    \
	    test -f $$dir/Makefile && ( cd $$dir && $(MAKE) distclean; );   \
	done
	rm -rf _inst

## ------------ ##
## package.m4.  ##
## ------------ ##

$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	{					\
	  echo '# Signature of the current package.'; \
	  echo 'm4_define([AT_PACKAGE_NAME],      [@PACKAGE_NAME@])'; \
	  echo 'm4_define([AT_PACKAGE_TARNAME],   [@PACKAGE_TARNAME@])'; \
	  echo 'm4_define([AT_PACKAGE_VERSION],   [@PACKAGE_VERSION@])'; \
	  echo 'm4_define([AT_PACKAGE_STRING],    [@PACKAGE_STRING@])'; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [@PACKAGE_BUGREPORT@])'; \
	} >$(srcdir)/package.m4

## ------------ ##
## Test suite.  ##
## ------------ ##

TESTSUITE_AT = \
	testsuite.at \
	demo.at fortran.at tools.at
TESTSUITE = testsuite

#EXTRA_DIST = $(TESTSUITE_AT) local.at atlocal.in package.m4

#check-local: atconfig $(TESTSUITE)
#	$(SHELL) $(srcdir)/$(TESTSUITE)

#clean-local:
#	$(srcdir)/testsuite --clean

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(srcdir)/$(TESTSUITE): $(srcdir)/package.m4 local.at $(TESTSUITE_AT)
	$(AUTOTEST) -I $(srcdir) testsuite.at -o $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && ./config.status tests/$@

# Run the test suite on the *installed* tree.
#installcheck-local:
	$(SHELL) $(srcdir)/$(TESTSUITE) AUTOTEST_PATH=$(exec_prefix)/bin
