## Process this file with automake to produce Makefile.in
##
## Copyright (C) 2003, 2004 Free Software Foundation
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; see the file COPYING.  If not, write to
## the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
## Boston, MA 02111-1307, USA.

DISTCLEANFILES =

CXX_TESTS = \
	tagdemo-static.test tagdemo-make.test tagdemo-exec.test \
	tagdemo-conf.test tagdemo-make.test tagdemo-exec.test \
	tagdemo-shared.test tagdemo-make.test tagdemo-exec.test \
	tagdemo-undef.test tagdemo-make.test tagdemo-exec.test

F77_TESTS = \
	f77demo-static.test f77demo-make.test f77demo-exec.test \
	f77demo-conf.test f77demo-make.test f77demo-exec.test \
	f77demo-shared.test f77demo-make.test f77demo-exec.test

COMMON_TESTS = \
	link.test link-2.test nomode.test objectlist.test \
	quote.test sh.test suffix.test tagtrace.test \
	cdemo-static.test cdemo-make.test cdemo-exec.test \
	demo-static.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test \
	depdemo-static.test depdemo-make.test depdemo-exec.test \
	depdemo-inst.test depdemo-unst.test \
	mdemo-static.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test \
	cdemo-conf.test cdemo-make.test cdemo-exec.test \
	demo-conf.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test demo-deplibs.test \
	depdemo-conf.test depdemo-make.test depdemo-exec.test \
	depdemo-inst.test depdemo-unst.test \
	mdemo-conf.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test mdemo-dryrun.test \
	mdemo2-conf.test mdemo2-make.test mdemo2-exec.test \
	pdemo-conf.test pdemo-make.test pdemo-exec.test \
	pdemo-inst.test \
	demo-nofast.test demo-make.test demo-exec.test \
	demo-inst.test demo-unst.test \
	depdemo-nofast.test depdemo-make.test depdemo-exec.test \
	depdemo-inst.test depdemo-unst.test \
	demo-pic.test demo-make.test demo-exec.test \
	demo-nopic.test demo-make.test demo-exec.test \
	cdemo-shared.test cdemo-make.test cdemo-exec.test \
	demo-shared.test demo-make.test demo-exec.test demo-inst.test \
	demo-hardcode.test demo-relink.test demo-noinst-link.test \
	demo-unst.test \
	depdemo-shared.test depdemo-make.test depdemo-exec.test \
	depdemo-inst.test depdemo-relink.test depdemo-unst.test \
	mdemo-shared.test mdemo-make.test mdemo-exec.test \
	mdemo-inst.test mdemo-unst.test \
	cdemo-undef.test cdemo-make.test cdemo-exec.test

if HAVE_CXX
if HAVE_F77
TESTS = $(COMMON_TESTS) $(CXX_TESTS) $(F77_TESTS)
else
TESTS = $(COMMON_TESTS) $(CXX_TESTS)
endif
else
if HAVE_F77
TESTS = $(COMMON_TESTS) $(F77_TESTS)
else
TESTS = $(COMMON_TESTS)
endif
endif

demo-conf.test: $(top_builddir)/libtool

$(top_builddir)/libtool:
	cd $(top_builddir) && $(MAKE) all

# Be sure to reexport important environment variables.
# This is a copy of ../Makefile.am (TESTS_ENVIRONMENT), be sure to
# keep them is sync if you change them before these tests are migrated!
TESTS_ENVIRONMENT = MAKE="$(MAKE)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
	CPPFLAGS="$(CPPFLAGS)" LD="$(LD)" LDFLAGS="$(LDFLAGS)" \
	LIBS="$(LIBS)" LN_S="$(LN_S)" NM="$(NM)" RANLIB="$(RANLIB)" \
	OBJEXT="$(OBJEXT)" EXEEXT="$(EXEEXT)" F77="$(F77)" \
	FFLAGS="$(FFLAGS)" CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" CPP="$(CPP)"

EXTRA_DIST = defs.in defs.m4sh $(COMMON_TESTS) $(CXX_TESTS) $(F77_TESTS)
DIST_SUBDIRS = $(CONF_SUBDIRS)

# FIXME: Automake-1.7b (at least) only honours DIST_SUBDIRS if SUBDIRS is
#        also set.  Remove this line when that bug is fixed.
SUBDIRS = .

# We need to remove any files that the above tests created.
clean-local:
	-for dir in cdemo demo depdemo f77demo mdemo mdemo2 pdemo tagdemo;  \
	do								    \
	    test -f $$dir/Makefile && ( cd $$dir && $(MAKE) distclean; );   \
	done
	rm -rf _inst

$(TESTS): defs
defs: defs.in ../Makefile.am
	cd .. && $(MAKE) $(AM_MAKEFLAGS) tests/defs
DISTCLEANFILES += defs
