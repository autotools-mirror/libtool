## Process Makefile.am with automake to create Makefile.in.
##
## Copyright (C) 1996 Free Software Foundation, Inc.
## This Makefile.am is free software; the Free Software Foundation
## gives unlimited permission to copy, distribute and modify it.
##
## Written by Gordon Matzigkeit <gord@gnu.ai.mit.edu>
AUTOMAKE_OPTIONS = gnits

CLEANFILES = aclibtool.T
MAINTAINERCLEANFILES = aclibtool.texi

info_TEXINFOS = libtool.texi
libtool_TEXINFOS = aclibtool.texi

## Quoted version of $(top_srcdir)/libtool.m4.
$(srcdir)/aclibtool.texi: $(top_srcdir)/libtool.m4
	rm -f aclibtool.T
	sed -e 's/{/@{/g' -e 's/}/@}/g' $(top_srcdir)/libtool.m4 \
	   > aclibtool.T
	mv aclibtool.T $(srcdir)/aclibtool.texi
