dnl Process this file with autoconf to create configure. -*-Autoconf-*-

AC_PREREQ(2.50)
AC_INIT(depdemo, 0.1)
AC_CONFIG_SRCDIR([main.c])
AM_INIT_AUTOMAKE(depdemo,0.1)

AC_PROG_CC
AC_EXEEXT
AM_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

if ${CONFIG_SHELL} ./libtool --features | grep "enable static" >/dev/null; then
  STATIC=-static
else
  STATIC=
fi
AC_SUBST(STATIC)

AC_CHECK_HEADERS(math.h)

AC_CHECK_LIBM
AC_SUBST(LIBM)

dnl Output the makefile
AC_CONFIG_FILES([Makefile
l1/Makefile
l2/Makefile
l3/Makefile
l4/Makefile
])
AC_OUTPUT
