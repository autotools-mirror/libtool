# A brief demonstration of using Automake with Libtool.
AUTOMAKE_OPTIONS = ansi2knr foreign

EXTRA_DIST = $(TESTS) acinclude.m4

# Build a libtool library, libhell.la for installation in libdir.
lib_PROGRAMS = libhell.la
libhell_la_SOURCES = hello.c foo.c
libhell_la_LDFLAGS = -version-info 3:12:1 -rpath $(libdir)

include_HEADERS = foo.h

bin_PROGRAMS = hell hell.static

# Build hell from main.c and libhell.la
hell_SOURCES = main.c
hell_LDADD = libhell.la

# Create a statically-linked version of hell.
hell_static_SOURCES = main.c
hell_static_LDADD = libhell.la
hell_static_LDFLAGS = -static

TESTS = run.test

# Regenerate our acinclude.m4 only if it doesn't exist.
$(srcdir)/acinclude.m4:
	rm -f $(srcdir)/acinclude.m4
	ln -s ../libtool.m4 $(srcdir)/acinclude.m4
