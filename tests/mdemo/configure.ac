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
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
# 02111-1307  USA

AC_PREREQ(2.54)


## ------------------------ ##
## Autoconf initialisation. ##
## ------------------------ ##
AC_INIT([mdemo], [1.0], [bug-libtool@gnu.org])
AC_CONFIG_SRCDIR([main.c])
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
LTDL_CONVENIENCE([../../libltdl])
AC_SUBST([INCLTDL])
AC_SUBST([LIBLTDL])

LT_INIT([dlopen win32-dll])
AC_SUBST(LIBTOOL_DEPS)

STATIC=""
test "X$enable_static" = Xyes && STATIC="-static"
AC_SUBST([STATIC])


## ---------------------------- ##
## C headers required by mdemo. ##
## ---------------------------- ##
AC_CHECK_HEADERS([math.h])


## ---------------------------- ##
## Libraries required by mdemo. ##
## ---------------------------- ##
LT_LIB_M


## -------- ##
## Outputs. ##
## -------- ##
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
