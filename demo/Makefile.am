# A brief demonstration of using Automake with Libtool.
AUTOMAKE_OPTIONS = foreign no-dependencies

EXTRA_DIST = libinfo

# Build a libtool library, libhell.la for installation in libdir.
lib_PROGRAMS = libhell.la
libhell_la_SOURCES = hello.c foo.c
libhell_la_LDFLAGS = -version-file $(srcdir)/libinfo -rpath $(libdir)

include_HEADERS = foo.h

# Build hell from main.c and libhell.la
bin_PROGRAMS = hell
hell_SOURCES = main.c
hell_LDADD = libhell.la

# Regenerate the acinclude.m4 from the parent, if it doesn't exist.
$(top_srcdir)/acinclude.m4:
	ln -s $(top_srcdir)/../libtool.m4 $(top_srcdir)/acinclude.m4
