## Process this file with automake to create Makefile.in

AUTOMAKE_OPTIONS = gnits

TESTS = demo-conf.test demo-make.test demo-exec.test demo-inst.test \
	demo-unst.test hardcode.test link.test link-2.test suffix.test \
	test-e.test

EXTRA_DIST = defs tlibtool $(TESTS)

# We need to remove any files that the above tests created.
distclean-local:
	test -f ../demo/Makefile && cd ../demo && $(MAKE) distclean
	rm -rf =inst
