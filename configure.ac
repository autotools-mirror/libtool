## Process this file with autoconf to create configure. -*- autoconf -*-
# Copyright (C) 2001, 2004 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
# 02111-1307  USA


AC_PREREQ(2.58) ## We use AS_HELP_STRING
## Oldest automake required for bootstrap is below in AM_INIT_AUTOMAKE.


## ------------------------ ##
## Autoconf initialisation. ##
## ------------------------ ##
AC_INIT([libtool], [1.5a], [bug-libtool@gnu.org])
AC_CONFIG_HEADERS([config.h:config-h.in])
AC_CONFIG_SRCDIR([ltmain.in])
AC_CONFIG_AUX_DIR([config])


## ------------------------ ##
## Autotest initialisation. ##
## ------------------------ ##

dnl AC_CONFIG_TESTDIR([tests])
dnl AC_CONFIG_FILES([tests/atlocal])


## ---------------------------------------- ##
## Display a configure time version banner. ##
## ---------------------------------------- ##

# Calculating the previous version is somewhat involved, so do it once
# here, and SUBST the result for the maintainer release rules.  The
# versioning scheme we use is described here:
#	http://www.gnu.org/software/libtool/contribute.html

# First we break the version number up into its constituent parts.
lt_major=`echo "AC_PACKAGE_VERSION" | sed ['s,\..*$,,g']`
lt_minor=`echo "AC_PACKAGE_VERSION" | sed ['s,^[0-9]*\.\([0-9]*\).*$,\1,']`
lt_micro=`echo "AC_PACKAGE_VERSION" | sed ['s,^[0-9]*\.[0-9]*\(\.[0-9]*\).*$,\1,']`
lt_alpha=`echo "AC_PACKAGE_VERSION" | sed ['s,^[0-9.]*,,']`

test "$lt_minor" = "AC_PACKAGE_VERSION" && lt_minor=0
test "$lt_micro" = "AC_PACKAGE_VERSION" && lt_micro=""

# Then we try to work out what the release before this one would have been
# numbered.  The only time we come unstuck is when this is the first release
# from a stable branch (lt_micro=lt_alpha=""), so LASTRELEASE is the last
# release from the old stable branch, and we don't know what version that
# was, so leave it unset so that the Makefile can complain.
case $lt_alpha in
  [[ab]])
    case $lt_micro in
      [.[01]])
	LASTRELEASE="$lt_major.$lt_minor" ;;
      *)
	LASTRELEASE="$lt_major.$lt_minor$lt_micro" ;;
    esac
    ;;
  [[cegikmoqsuwy]])
    LASTRELEASE=`echo "AC_PACKAGE_VERSION" | tr 'c-y' 'b-w'` ;;
  [[dfhjlnprtvxz]])
    LASTRELEASE=`echo "AC_PACKAGE_VERSION" | tr 'd-z' 'b-x'` ;;
  *) # No lt_alpha component
    case $lt_micro in
      .0)
	LASTRELEASE="" ;;
      .1)
        LASTRELEASE="$lt_major.$lt_minor" ;;
      .*)
	lt_micro_value=`echo $lt_micro | sed 's,^\.,,'`
	LASTRELEASE="$lt_major.$lt_minor.`expr $lt_micro_value - 1`" ;;
      *)
	LASTRELEASE="" ;;
    esac
    ;;
esac
AC_SUBST([LASTRELEASE])

# This is a sanity check so we can see which version is used in bug reports.
# It is assumed that we only want to see the date extension for cvs libtool
# versions (i.e. "odd" letters) and not actual alpha releases.
TIMESTAMP=
case $lt_alpha in
  [[acegikmoqsuwy]])
    TIMESTAMP=`${CONFIG_SHELL} ${ac_aux_dir}/mkstamp < ${srcdir}/ChangeLog`
    AS_BOX([Configuring AC_PACKAGE_TARNAME (Build:$TIMESTAMP) AC_PACKAGE_VERSION])
    echo
    ;;
esac
AC_SUBST([TIMESTAMP])


## ------------------------ ##
## Automake Initialisation. ##
## ------------------------ ##

dnl These are bootstrap requirements, once built, libtool may work with
dnl much older releases of autoconf and automake.  See release notes.
AM_INIT_AUTOMAKE([1.8 gnits dist-bzip2]) ## We use auto-m4_including


## ------------------------------- ##
## Libtool specific configuration. ##
## ------------------------------- ##
pkgdatadir='${datadir}'"/${PACKAGE}"
AC_SUBST([pkgdatadir]) # automake does not need this, but libtoolize does

aclocaldir='${datadir}/aclocal'
AC_SUBST([aclocaldir])

AC_ARG_ENABLE(ltdl-install,
    [AS_HELP_STRING([--disable-ltdl-install], [do not install libltdl])])
if test x"${enable_ltdl_install+set}" != xset; then
  enable_ltdl_install=yes
fi

# All subdirectories that are configured on demand, but that must be
# included in the distribution.  This substitution is for tests/Makefile.am,
# so the directory names are relative to that directory.
CONF_SUBDIRS="cdemo demo depdemo f77demo mdemo mdemo2 pdemo tagdemo"
AC_SUBST([CONF_SUBDIRS])

DIST_MAKEFILE_LIST=
for dir in $CONF_SUBDIRS; do
  DIST_MAKEFILE_LIST="${DIST_MAKEFILE_LIST}tests/$dir/Makefile "
done
AC_SUBST([DIST_MAKEFILE_LIST])



## ---------------- ##
## compiler checks. ##
## ---------------- ##

# Use the specified CC and LD
AC_PROG_CC
AC_EXEEXT
AC_PROG_LD
AC_PROG_NM
AC_PROG_LN_S

pushdef([AC_MSG_ERROR], [CXX=no])
AC_PROG_CXX
popdef([AC_MSG_ERROR])
AM_CONDITIONAL(HAVE_CXX, [test "x$CXX" != xno])

pushdef([AC_MSG_ERROR], [F77=no])
AC_PROG_F77
popdef([AC_MSG_ERROR])
if test -z "$F77"; then
  F77="no"
fi
AM_CONDITIONAL(HAVE_F77, [test "x$F77" != xno])

LT_AC_PROG_GCJ
AM_CONDITIONAL(HAVE_GCJ, [test "x$GCJ" != xno])

LT_AC_PROG_RC
AM_CONDITIONAL(HAVE_RC, [test "x$RC" != xno])



## ----------------------- ##
## Libtool initialisation. ##
## ----------------------- ##
AC_CONFIG_FILES([config/ltmain.sh:./ltmain.in])
AC_LIBTOOL_DLOPEN
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL
AC_LIB_LTDL



## -------- ##
## Outputs. ##
## -------- ##
AC_CONFIG_FILES([Makefile libltdl/Makefile doc/Makefile tests/Makefile])
AC_OUTPUT
