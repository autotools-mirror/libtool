## Process this file with autoconf to create configure. -*- autoconf -*-
# Copyright (C) 2001, 2003 Free Software Foundation, Inc.
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

AC_PREREQ(2.54)


## ------------------------ ##
## Autoconf initialisation. ##
## ------------------------ ##
AC_INIT([pdemo], [1.0], [bug-libtool@gnu.org])
AC_CONFIG_SRCDIR([longer_file_name_hello.c])
AC_CONFIG_AUX_DIR([../../config])


## ------------------------ ##
## Automake Initialisation. ##
## ------------------------ ##
AM_INIT_AUTOMAKE


## ------------------ ##
## C compiler checks. ##
## ------------------ ##
AC_PROG_CC
AC_C_CONST


## ----------------------- ##
## Libtool initialisation. ##
## ----------------------- ##
AC_LIBTOOL_DLOPEN
AC_LIBTOOL_TAGS([])
AC_PROG_LIBTOOL
AC_SUBST([LIBTOOL_DEPS])

STATIC=
test "X$enable_static" = Xyes && STATIC=-static
AC_SUBST([STATIC])

case $lt_cv_sys_global_symbol_pipe in
  ?*) binary_helldl=yes ;;
esac
AM_CONDITIONAL([BINARY_HELLDL], [test "X$binary_helldl" = Xyes])


## ---------------------------- ##
## C headers required by cdemo. ##
## ---------------------------- ##
AC_CHECK_HEADERS([string.h math.h])


## ---------------------------- ##
## Libraries required by cdemo. ##
## ---------------------------- ##
AC_CHECK_LIBM
AC_SUBST([LIBM])


## -------- ##
## Outputs. ##
## -------- ##
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
