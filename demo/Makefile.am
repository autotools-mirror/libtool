# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
# NOTE: Don't forget that in the libtool distribution, files in this
# directory are distributed by the demo_distfiles variable in the top
# level Makefile.
AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = $(TESTS) acinclude.m4

hardcode_tests = hc-direct hc-libpath hc-minusL
CLEANFILES = $(hardcode_tests)

# Build a libtool library, libhello.la for installation in libdir.
lib_LTLIBRARIES = libhello.la
libhello_la_SOURCES = hello.c foo.c
libhello_la_LDFLAGS = -version-info 3:12:1

include_HEADERS = foo.h

bin_PROGRAMS = hell hell.static helldl

# Build hell from main.c and libhello.la
hell_SOURCES = main.c
hell_LDADD = libhello.la

# Create a statically-linked version of hell.
hell_static_SOURCES = main.c
hell_static_LDADD = libhello.la
hell_static_LDFLAGS = -static

# Create a version of hell that does its own dlopening.
helldl_SOURCES = dlmain.c
helldl_LDFLAGS = -dlopen libhello.la

TESTS = run.test

# The following rules are only for the libtool demo and tests.
# Regenerate our acinclude.m4 only if it doesn't exist.
$(srcdir)/acinclude.m4:
	rm -f $(srcdir)/acinclude.m4
	ln -s ../libtool.m4 $(srcdir)/acinclude.m4

# Don't build helldl on unsupported platforms.
helldl: $(helldl_OBJECTS) $(helldl_DEPENDENCIES)
	@rm -f helldl helldlT
	@eval "`egrep '^global_symbol_pipe=' libtool`"; \
	if test -z "$$global_symbol_pipe"; then \
	  echo 'creating helldl (-dlopen is unsupported)'; \
	  echo "#! /bin/sh" > helldlT; \
	  echo "echo '-dlopen is unsupported'" >> helldlT; \
	  chmod +x helldlT; \
	  mv -f helldlT helldl; \
	else \
	  echo '$(LINK) $(helldl_LDFLAGS) $(helldl_OBJECTS) $(helldl_LDADD) $(LIBS)'; \
	  $(LINK) $(helldl_LDFLAGS) $(helldl_OBJECTS) $(helldl_LDADD) $(LIBS); \
	fi

# Test programs to see what gets hardcoded.
.PHONY: hardcode
hardcode: $(hardcode_tests)
hc-direct: $(hell_OBJECTS) $(hell_DEPENDENCIES)
	@rm -f hc-direct
	@shlib=./.libs/libhello.a; \
	  eval "`egrep '^library_names' libhello.la`"; \
	  for lib in $$library_names; do \
	    shlib="./.libs/$$lib"; \
	  done; \
	  echo "$(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) $$shlib $(LIBS)"; \
	  eval "$(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) $$shlib $(LIBS)"

hc-minusL: $(hell_OBJECTS) $(hell_DEPENDENCIES)
	@rm -f hc-minusL
	$(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) -L./.libs -lhello $(LIBS)

hc-libpath: $(hell_OBJECTS) $(hell_DEPENDENCIES)
	@rm -f hc-libpath
	@echo "You may ignore any linking errors from the following command:"
	@eval `egrep -e '^shlibpath_var=' ./libtool`; \
	  echo "$$shlibpath_var=./.libs $(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) -lhello $(LIBS) || echo unsupported > $@"; \
	  eval "$$shlibpath_var=./.libs $(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) -lhello $(LIBS) || echo unsupported > $@"
