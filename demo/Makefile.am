# A brief demonstration of using Automake with Libtool. -*-Makefile-*-
#
AUTOMAKE_OPTIONS = no-dependencies foreign

EXTRA_DIST = $(TESTS) acinclude.m4

hardcode_tests = hc-direct hc-libflag hc-libpath hc-minusL
CLEANFILES = $(hardcode_tests)

# Build a libtool library, libhello.la for installation in libdir.
lib_LTLIBRARIES = libhello.la
libhello_la_SOURCES = hello.c foo.c
libhello_la_LDFLAGS = -version-info 3:12:1 $(LIBADD_M)

include_HEADERS = foo.h

if BINARY_HELLDL
BUILD_helldl = helldl
else
BUILD_helldl = 
endif

bin_PROGRAMS = hell hell.debug $(BUILD_helldl)

# Build hell from main.c and libhello.la
hell_SOURCES = main.c
hell_LDADD = libhello.la

# Create an easier-to-debug version of hell.
hell_debug_SOURCES = main.c
hell_debug_LDADD = libhello.la
hell_debug_LDFLAGS = @STATIC@

if BINARY_HELLDL

# Create a version of hell that does a preloaded dlopen.
helldl_SOURCES = dlmain.c
helldl_LDFLAGS = -export-dynamic -dlpreopen libhello.la
helldl_DEPENDENCIES = libhello.la

else

bin_SCRIPTS = helldl
# create a script that says that -dlopen is not supported
helldl:
	rm -f $@
	echo '#! /bin/sh' > $@
	echo '-dlopen is unsupported' >> $@
	chmod +x $@
endif

# Unfortunately, in order to test libtool thoroughly, we need access
# to its private directory.
objdir = `sed -n -e 's/^objdir=\(.*\)$$/\1/p' ../libtool`

TESTS = run.test

# The following rules are only for the libtool demo and tests.
# Regenerate our acinclude.m4 only if it doesn't exist.
$(srcdir)/acinclude.m4:
	rm -f $(srcdir)/acinclude.m4
	cd $(srcdir) && $(LN_S) ../libtool.m4 acinclude.m4


# Test programs to see what gets hardcoded.
.PHONY: hardcode
hardcode: $(hardcode_tests)
hc-direct: $(hell_OBJECTS) $(hell_DEPENDENCIES)
	@rm -f hc-direct
	@echo "You may ignore any linking errors from the following command:"
	@shlib=./$(objdir)/libhello.a; \
	  eval "`egrep '^library_names' libhello.la`"; \
	  for lib in $$library_names; do \
	    shlib="./$(objdir)/$$lib"; \
	  done; \
	  echo "$(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) $$shlib -lm || echo unsupported > $@"; \
	  eval "$(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) $$shlib -lm || echo unsupported > $@"

# We need to create an alias for $(objdir) so that this test works regardless
# of $hardcode_minus_L
hc-libflag: $(hell_OBJECTS) $(hell_DEPENDENCIES)
	rm -rf hc-libflag _hclibs
	mkdir _hclibs
	objdir=$(objdir); cd _hclibs && for lib in ../$$objdir/libhello*; do \
	  $(LN_S) $$lib `echo "$$lib" | sed 's%^.*/%%'` || exit 1; \
	done
	@eval `egrep -e '^(hardcode_.*|wl)=' ../libtool`; \
	  libdir=`pwd`/$(objdir); \
	  flag=`eval echo \"$$hardcode_libdir_flag_spec\"`; \
	  if test -z "$$flag"; then \
	    echo "echo unsupported > $@"; \
	    echo unsupported > $@ || status="$$?"; \
	  else \
	    echo "$(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) $$flag -L./_hclibs -lhello -lm"; \
	    $(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) $$flag -L./_hclibs -lhello -lm || status="$$?"; \
	  fi; \
	  echo "rm -rf _hclibs"; \
	  rm -rf _hclibs; \
	  exit $$status

hc-libpath: $(hell_OBJECTS) $(hell_DEPENDENCIES)
	@rm -f hc-libpath
	@echo "You may ignore any linking errors from the following command:"
	@eval `egrep -e '^shlibpath_var=' ../libtool`; \
	  echo "$$shlibpath_var=./$(objdir) $(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) -lhello -lm || echo unsupported > $@"; \
	  eval "$$shlibpath_var=./$(objdir) $(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) -lhello -lm || echo unsupported > $@"

hc-minusL: $(hell_OBJECTS) $(hell_DEPENDENCIES)
	@rm -f hc-minusL
	$(CC) $(LDFLAGS) -o $@ $(hell_OBJECTS) -L./$(objdir) -lhello -lm
