## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = gnits

TESTS = cdemo-static.test cdemo-make.test cdemo-exec.test \
	demo-static.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test \
	mdemo-static.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test \
	cdemo-conf.test cdemo-make.test cdemo-exec.test \
	demo-conf.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test deplibs.test \
	mdemo-conf.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test dryrun.test \
	demo-nofast.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test \
	cdemo-shared.test cdemo-make.test cdemo-exec.test \
	demo-shared.test demo-make.test demo-exec.test demo-inst.test \
	hardcode.test build-relink.test noinst-link.test demo-unst.test \
	mdemo-shared.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test \
	assign.test link.test link-2.test nomode.test \
	quote.test sh.test suffix.test

cdemo-static.test: $(top_builddir)/libtool

$(top_builddir)/libtool:
	cd $(top_builddir) && $(MAKE) all

# We should export these variables when we run ltconfig.
CFLAGS = @CFLAGS@
CPPLAGS = @CPPFLAGS@
LDFLAGS = @LDFLAGS@
LIBS = @LIBS@

# Be sure to reexport important environment variables.
TESTS_ENVIRONMENT = CC="$(CC)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" \
	LD="$(LD)" LDFLAGS="$(LDFLAGS)" LIBS="$(LIBS)" \
	LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)"

EXTRA_DIST = defs $(TESTS)

# We need to remove any files that the above tests created.
clean-local:
	-test -f ../cdemo/Makefile && cd ../cdemo && $(MAKE) distclean
	-test -f ../demo/Makefile && cd ../demo && $(MAKE) distclean
	-test -f ../mdemo/Makefile && cd ../mdemo && $(MAKE) distclean
	rm -rf _inst
