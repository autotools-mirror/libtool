## Process this file with autoconf to create configure. -*- autoconf -*-
# Copyright 2001  Free Software Foundation, Inc.
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
LT_MAJOR=`echo "AC_PACKAGE_VERSION" | sed ['s,\..*$,,g']`
LT_MINOR=`echo "AC_PACKAGE_VERSION" | sed ['s,^[0-9]*\.\([0-9]*\).*$,\1,']`
LT_MICRO=`echo "AC_PACKAGE_VERSION" | sed ['s,^[0-9]*\.[0-9]*\(\.[0-9]*\).*$,\1,']`
LT_ALPHA=`echo "AC_PACKAGE_VERSION" | sed ['s,^[0-9.]*,,']`

test "$LT_MINOR" = "AC_PACKAGE_VERSION" && LT_MINOR=0
test "$LT_MICRO" = "AC_PACKAGE_VERSION" && LT_MICRO=""

# Then we try to work out what the release before this one would have been
# numbered.  The only time we come unstuck is when this is the first release
# from a stable branch (LT_MICRO=LT_ALPHA=""), so OLDVERSION is the last
# release from the old stable branch, and we don't know what version that
# was, so leave it unset so that the Makefile can complain.
case $LT_ALPHA in
  [[ab]])
    case $LT_MICRO in
      [.[01]])
	LASTRELEASE="$LT_MAJOR.$LT_MINOR" ;;
      *)
	LASTRELEASE="$LT_MAJOR.$LT_MINOR$LT_MICRO" ;;
    esac
    ;;
  [[cegikmoqsuwy]])
    LASTRELEASE=`echo "AC_PACKAGE_VERSION" | tr 'c-y' 'b-w'` ;;
  [[dfhjlnprtvxz]])
    LASTRELEASE=`echo "AC_PACKAGE_VERSION" | tr 'd-z' 'b-x'` ;;
  *) # No LT_ALPHA component
    case $LT_MICRO in
      .0)
	LASTRELEASE="" ;;
      .1)
        LASTRELEASE="$LT_MAJOR.$LT_MINOR" ;;
      .*)
	lt_micro_value=`echo $LT_MICRO | sed 's,^\.,,'`
	LASTRELEASE="$LT_MAJOR.$LT_MINOR.`expr $lt_micro_value - 1`" ;;
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
case $LT_ALPHA in
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
AM_INIT_AUTOMAKE([1.7 gnits])


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
  ac_configure_args="$ac_configure_args --enable-ltdl-install"
fi
AC_CONFIG_SUBDIRS([libltdl])

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
AC_CONFIG_COMMANDS([libltdl/ltmain.sh],
    [cp -f config/ltmain.sh libltdl/ltmain.sh])
AC_LIBTOOL_DLOPEN
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL



## -------- ##
## Outputs. ##
## -------- ##
AC_CONFIG_FILES([Makefile doc/Makefile tests/Makefile])
AC_OUTPUT
