# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = $(TESTS) acinclude.m4

hardcode_tests = hc-direct hc-minusL hc-libpath
CLEANFILES = $(hardcode_tests)

# Build a libtool library, libhello.la for installation in libdir.
lib_LTLIBRARIES = libhello.la
libhello_la_SOURCES = hello.c foo.c
libhello_la_LDFLAGS = -version-info 3:12:1

include_HEADERS = foo.h

bin_PROGRAMS = hell hell.static

# Build hell from main.c and libhello.la
hell_SOURCES = main.c
hell_LDADD = libhello.la

# Create a statically-linked version of hell.
hell_static_SOURCES = main.c
hell_static_LDADD = libhello.la
hell_static_LDFLAGS = -static

TESTS = run.test

# The following rules are only for the libtool demo and tests.
# Regenerate our acinclude.m4 only if it doesn't exist.
$(srcdir)/acinclude.m4:
	rm -f $(srcdir)/acinclude.m4
	ln -s ../libtool.m4 $(srcdir)/acinclude.m4

# Test programs to see what gets hardcoded.
.PHONY: hardcode
hardcode: $(hardcode_tests)
hc-direct: $(hell_OBJECTS) $(hell_DEPENDENCIES)
	@shlib=./.libs/libhello.a; \
	  eval "`egrep '^library_names' libhello.la`"; \
	  for lib in $$library_names; do \
	    shlib="./.libs/$$lib"; \
	  done; \
	  echo "$(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) $$shlib $(LIBS)"; \
	  eval "$(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) $$shlib $(LIBS)"

hc-minusL: $(hell_OBJECTS) $(hell_DEPENDENCIES)
	$(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) -L./.libs -lhello $(LIBS)

hc-libpath: $(hell_OBJECTS) $(hell_DEPENDENCIES)
	@echo "You may ignore any linking errors from the following command:"
	@eval `egrep -e '^shlibpath_var=' ./libtool`; \
	  echo "$$shlibpath_var=./.libs $(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) -lhello $(LIBS) || echo unsupported > $@"; \
	  eval "$$shlibpath_var=./.libs $(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) -lhello $(LIBS) || echo unsupported > $@"
