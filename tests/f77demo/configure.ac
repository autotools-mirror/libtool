## Process this file with autoconf to create configure. -*- autoconf -*-
# Copyright (C) 2001, 2003, 2005 Free Software Foundation, Inc.
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
AC_INIT([f77demo], [1.0], [bug-libtool@gnu.org])
AC_CONFIG_HEADERS([config.h:config-h.in])
AC_CONFIG_SRCDIR([foof.f])
AC_CONFIG_AUX_DIR([../../libltdl/config])

## ------------------------ ##
## Automake Initialisation. ##
## ------------------------ ##
AM_INIT_AUTOMAKE


## ------------------ ##
## C compiler checks. ##
## ------------------ ##
AC_PROG_CC

## ------------------------ ##
## Fortran compiler checks. ##
## ------------------------ ##
AC_PROG_F77
dnl Check the flags needed to link f77 programs with ld (i.e. cc)
AC_F77_LIBRARY_LDFLAGS
dnl Check for underscoring of external names
AC_F77_WRAPPERS

# As of the writing of this demo, GNU Autoconf's AC_OBJEXT and
# AC_EXEEXT macros only works for C compilers!
# Libtool's setup macro calls AC_OBJEXT and AC_EXEEXT without setting
# the test language to C.  We do it before any libtool setup macros are
# called so that the proper values are cached beforehand.  We also do
# it before any linker flags (LDFLAGS) are set so that fortran specific
# ones don't break the tests.
AC_LANG_PUSH([C])
AC_OBJEXT
AC_EXEEXT
AC_LANG_POP

## ----------------------- ##
## Libtool initialisation. ##
## ----------------------- ##
LT_INIT
AC_SUBST([LIBTOOL_DEPS])

## -------- ##
## Outputs. ##
## -------- ##
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
