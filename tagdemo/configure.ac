dnl -*-Autoconf-*-
dnl $Id$

dnl
dnl An autoconf script to automatically configure the sample C++ "foo"
dnl application.
dnl Process this file with autoconf to produce a configure script.
dnl

AC_PREREQ(2.50)
dnl Can't use $PACKAGE/$VERSION here
AC_INIT(foo, 0.1)
AC_CONFIG_SRCDIR([foo.cpp])dnl

dnl Check what platform we are running on.
AC_CANONICAL_TARGET([])

dnl Cause GNU Automake to initialize the state of things and run
dnl some sanity checks
PACKAGE=foo
VERSION=0.1
AM_INIT_AUTOMAKE($PACKAGE, $VERSION)

dnl Check the C compiler and preprocessor.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CC_C_O

dnl Check the C++ compiler and preprocessor.
AC_PROG_CXX
AC_PROG_CXXCPP

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

dnl Setup Libtool

dnl Set the test language to C++.
AC_LANG([C++])

dnl Check for libtool and turn on Automake processing for Libtool
AM_PROG_LIBTOOL

AC_CHECK_HEADERS(math.h)

AC_CHECK_LIBM
AC_SUBST(LIBM)

AC_CONFIG_FILES(Makefile)
AC_CONFIG_COMMANDS([default], [[echo "Done configuring package $PACKAGE"]])
AC_OUTPUT
