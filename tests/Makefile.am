## Process this file with automake to create Makefile.in -*-Makefile-*-

AUTOMAKE_OPTIONS = gnits

makesequence = demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test hardcode.test
TESTS =	demo-conf.test $(makesequence) link.test link-2.test nomode.test \
	quote.test sh.test suffix.test

# Be sure to reexport important environment variables.
TESTS_ENVIRONMENT = CC="$(CC)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" \
	LD="$(LD)" NM="$(NM)" RANLIB="$(RANLIB)" LN_S="$(LN_S)"

EXTRA_DIST = defs tlibtool $(TESTS)

# We need to remove any files that the above tests created.
clean-local:
	-test -f ../demo/Makefile && cd ../demo && $(MAKE) distclean
	rm -rf _inst
