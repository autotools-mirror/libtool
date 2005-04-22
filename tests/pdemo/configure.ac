## Process this file with autoconf to create configure. -*- autoconf -*-
# Copyright (C) 2001, 2003, 2004 Free Software Foundation, Inc.
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
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301  USA

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
LT_INIT([dlopen])
AC_SUBST([LIBTOOL_DEPS])

STATIC=
test "X$enable_static" = Xyes && STATIC=-static
AC_SUBST([STATIC])

case $lt_cv_sys_global_symbol_pipe in
  ?*) binary_helldl=yes ;;
esac
AM_CONDITIONAL([BINARY_HELLDL], [test "X$binary_helldl" = Xyes])


## ---------------------------- ##
## C headers required by pdemo. ##
## ---------------------------- ##
AC_CHECK_HEADERS([string.h math.h])


## ---------------------------- ##
## Libraries required by pdemo. ##
## ---------------------------- ##
LT_LIB_M


## -------- ##
## Outputs. ##
## -------- ##
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
