## Process this file with autoconf to create configure. -*- autoconf -*-
# Copyright (C) 2001, 2003, 2004, 2005 Free Software Foundation, Inc.
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
AC_INIT([tagdemo], [1.0], [bug-libtool@gnu.org])
AC_CONFIG_SRCDIR([foo.cpp])
AC_CONFIG_AUX_DIR([../../libltdl/config])

AC_CANONICAL_TARGET


## ------------------------ ##
## Automake Initialisation. ##
## ------------------------ ##
AM_INIT_AUTOMAKE


## ---------------- ##
## Compiler checks. ##
## ---------------- ##
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CC_C_O

AC_PROG_CXX
AC_PROG_CXXCPP

# Check for namespace support and new-style headers
AC_LANG_PUSH([C++])
AC_MSG_CHECKING([whether the compiler implements namespaces])
AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM([[namespace A { namespace B { int i = 0; }}]],
		     [[using namespace A::B; return i;]])],
    [AC_MSG_RESULT([yes])
     AC_DEFINE([HAVE_NAMESPACES],[1],
	       [define if the compiler implements namespaces])],
    [AC_MSG_RESULT([no])])

AC_MSG_CHECKING([whether the compiler has ISO C++ iostream])
AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM([[#include <iostream>
#ifdef HAVE_NAMESPACES
using namespace std;
#endif ]], [[cout << "bingo\n"; return 0;]])],
    [AC_MSG_RESULT([yes])
     AC_DEFINE([HAVE_IOSTREAM],[1],
	       [define if the compiler has ISO C++ iostream])],
    [AC_MSG_RESULT([no])])
AC_LANG_POP([C++])


# As of the writing of this demo, GNU Autoconf's AC_OBJEXT and
# AC_EXEEXT macros only works for C compilers!
# Libtool's setup macro calls AC_OBJEXT and AC_EXEEXT without setting
# the test language to C.  We do it before any libtool setup macros are
# called so that the proper values are cached beforehand.  We also do
# it before any linker flags (LDFLAGS) are set so that C++ specific
# ones don't break the tests.
AC_LANG_PUSH([C])
AC_OBJEXT
AC_EXEEXT
AC_LANG_POP


## ----------------------- ##
## Libtool initialisation. ##
## ----------------------- ##

# Set the test language to C++.
AC_LANG([C++])
LT_INIT


## ------------------------------ ##
## C headers required by tagdemo. ##
## ------------------------------ ##
AC_CHECK_HEADERS([math.h])


## ------------------------------ ##
## Libraries required by tagdemo. ##
## ------------------------------ ##
LT_LIB_M


## -------- ##
## Outputs. ##
## -------- ##
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
