## Process this file with automake to produce Makefile.in

info_TEXINFOS = libtool.texi
libtool_TEXINFOS = PLATFORMS fdl.texi notes.texi
EXTRA_DIST = notes.txt

all-local: notes.txt

notes.txt: notes.texi
	cd $(srcdir) && $(MAKEINFO) --plaintext $(MAKEINFOFLAGS) -o $@ notes.texi
