dnl Process this file with autoconf to create configure.

AC_PREREQ(2.50)
AC_INIT
AC_CONFIG_SRCDIR([main.c])
AM_INIT_AUTOMAKE(cdemo,0.1)

AC_PROG_CC
AC_EXEEXT
AM_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

AC_CHECK_HEADERS(math.h)

AC_CHECK_LIBM
AC_SUBST(LIBM)

dnl Output the makefile
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
