## Process this file with automake to create Makefile.in -*-Makefile-*-

AUTOMAKE_OPTIONS = gnits

TESTS = demo-static.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test hardcode.test \
	mdemo-static.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test \
	cdemo-static.test cdemo-make.test cdemo-exec.test \
	demo-conf.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test hardcode.test \
	mdemo-conf.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test \
	cdemo-conf.test cdemo-make.test cdemo-exec.test \
	demo-shared.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test hardcode.test \
	mdemo-shared.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test \
	cdemo-shared.test cdemo-make.test cdemo-exec.test \
	link.test link-2.test nomode.test \
	quote.test sh.test suffix.test

demo-conf.test: $(top_builddir)/libtool

$(top_builddir)/libtool:
	cd $(top_builddir) && $(MAKE) all

# Be sure to reexport important environment variables.
TESTS_ENVIRONMENT = CC="$(CC)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" \
	LD="$(LD)" NM="$(NM)" RANLIB="$(RANLIB)" LN_S="$(LN_S)"

EXTRA_DIST = defs $(TESTS)

# We need to remove any files that the above tests created.
clean-local:
	-test -f ../demo/Makefile && cd ../demo && $(MAKE) distclean
	-test -f ../cdemo/Makefile && cd ../cdemo && $(MAKE) distclean
	-test -f ../mdemo/Makefile && cd ../mdemo && $(MAKE) distclean
	rm -rf _inst
