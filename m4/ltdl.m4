# ltdl.m4 - Configure ltdl for the target system. -*-Autoconf-*-
# Copyright (C) 1999-2005 Free Software Foundation, Inc.
#
# This file is free software; the Free Software Foundation gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.

# serial 7 LTDL_INIT

# LT_WITH_LTDL([DIRECTORY])
# -------------------------
# Clients of libltdl can use this macro to allow the installer to
# choose between a shipped copy of the ltdl sources or a preinstalled
# version of the library.
AC_DEFUN([LT_WITH_LTDL],
[AC_ARG_WITH([included_ltdl],
    [AS_HELP_STRING([--with-included-ltdl],
                    [use the GNU ltdl sources included here])])

if test "x$with_included_ltdl" != xyes; then
  # We are not being forced to use the included libltdl sources, so
  # decide whether there is a useful installed version we can use.
  AC_CHECK_HEADER([ltdl.h],
      [AC_CHECK_LIB([ltdl], [lt_dlcaller_register],
          [with_included_ltdl=no],
          [with_included_ltdl=yes])],

      [],
      [AC_INCLUDES_DEFAULT]
  )
fi

if test "x$enable_ltdl_install" != xyes; then
  # If the user did not specify an installable libltdl, then default
  # to a convenience lib.
  LTDL_CONVENIENCE([$1])
fi

if test "x$with_included_ltdl" = xno; then
  # If the included ltdl is not to be used. then Use the
  # preinstalled libltdl we found.
  AC_DEFINE([HAVE_LTDL], [1],
    [Define this if a modern libltdl is already installed])
  LIBLTDL=-lltdl
fi

# Report our decision...
AC_MSG_CHECKING([whether to use included libltdl])
AC_MSG_RESULT([$with_included_ltdl])

AC_CONFIG_SUBDIRS(m4_if($#, 1, [$1], [libltdl]))
])# LT_WITH_LTDL

# Old name:
AU_DEFUN([AC_WITH_LTDL], [LT_WITH_LTDL])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_WITH_LTDL], [])


# LTDL_CONVENIENCE([DIRECTORY])
# -----------------------------
# sets LIBLTDL to the link flags for the libltdl convenience library and
# LTDLINCL to the include flags for the libltdl header and adds
# --enable-ltdl-convenience to the configure arguments.  Note that LIBLTDL
# and LTDLINCL are not AC_SUBSTed, nor is AC_CONFIG_SUBDIRS called.  If
# DIRECTORY is not provided, it is assumed to be `libltdl'.  LIBLTDL will
# be prefixed with '${top_builddir}/' and LTDLINCL will be prefixed with
# '${top_srcdir}/' (note the single quotes!).  If your package is not
# flat and you're not using automake, define top_builddir and
# top_srcdir appropriately in the Makefiles.
AC_DEFUN([LTDL_CONVENIENCE],
[case $enable_ltdl_convenience in
  no) AC_MSG_ERROR([this package needs a convenience libltdl]) ;;
  "") enable_ltdl_convenience=yes
      ac_configure_args="$ac_configure_args --enable-ltdl-convenience" ;;
  esac
LIBLTDL='${top_builddir}/'m4_if($#, 1, [$1], ['libltdl'])/libltdlc.la
LTDLINCL='-I${top_srcdir}/'m4_if($#, 1, [$1], ['libltdl'])

AC_SUBST([LIBLTDL])
AC_SUBST([LTDLINCL])

# For backwards non-gettext consistent compatibility...
INCLTDL="$LTDLINCL"
AC_SUBST([INCLTDL])
])# LTDL_CONVENIENCE

# Old name:
AU_DEFUN([AC_LIBLTDL_CONVENIENCE], [LTDL_CONVENIENCE])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIBLTDL_CONVENIENCE], [])


# LTDL_INSTALLABLE([DIRECTORY])
# -----------------------------
# sets LIBLTDL to the link flags for the libltdl installable library and
# LTDLINCL to the include flags for the libltdl header and adds
# --enable-ltdl-install to the configure arguments.  Note that LIBLTDL
# and LTDLINCL are not AC_SUBSTed, nor is AC_CONFIG_SUBDIRS called.  If
# DIRECTORY is not provided and an installed libltdl is not found, it is
# assumed to be `libltdl'.  LIBLTDL will be prefixed with '${top_builddir}/'
# and LTDLINCL will be prefixed with '${top_srcdir}/' (note the single
# quotes!).  If your package is not flat and you're not using automake,
# define top_builddir and top_srcdir appropriately in the Makefiles.
# In the future, this macro may have to be called after LT_INIT.
AC_DEFUN([LTDL_INSTALLABLE],
[AC_CHECK_LIB(ltdl, lt_dlinit,
  [test x"$enable_ltdl_install" != xyes && enable_ltdl_install=no],
  [if test x"$enable_ltdl_install" = xno; then
     AC_MSG_WARN([libltdl not installed, but installation disabled])
   else
     enable_ltdl_install=yes
   fi
  ])
if test x"$enable_ltdl_install" = x"yes"; then
  ac_configure_args="$ac_configure_args --enable-ltdl-install"
  LIBLTDL='${top_builddir}/'m4_if($#, 1, [$1], ['libltdl'])/libltdl.la
  LTDLINCL='-I${top_srcdir}/'m4_if($#, 1, [$1], ['libltdl'])
else
  ac_configure_args="$ac_configure_args --enable-ltdl-install=no"
  LIBLTDL="-lltdl"
  LTDLINCL=
fi

AC_SUBST([LIBLTDL])
AC_SUBST([LTDLINCL])

# For backwards non-gettext consistent compatibility...
INCLTDL="$LTDLINCL"
AC_SUBST([INCLTDL])
])# LTDL_INSTALLABLE

# Old name:
AU_DEFUN([AC_LIBLTDL_INSTALLABLE], [LTDL_INSTALLABLE])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIBLTDL_INSTALLABLE], [])


# LTDL_INIT
# ---------
# Perform all the checks necessary for compilation of the ltdl objects
#  -- including compiler checks and header checks.
AC_DEFUN([LTDL_INIT],
[AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_C_CONST])dnl
AC_REQUIRE([AC_HEADER_STDC])dnl
AC_REQUIRE([AC_HEADER_DIRENT])dnl
AC_REQUIRE([LT_SYS_MODULE_EXT])dnl
AC_REQUIRE([LT_SYS_MODULE_PATH])dnl
AC_REQUIRE([LT_SYS_DLSEARCH_PATH])dnl
AC_REQUIRE([LT_LIB_DLLOAD])dnl
AC_REQUIRE([LT_SYS_SYMBOL_USCORE])dnl
AC_REQUIRE([LT_FUNC_DLSYM_USCORE])dnl
AC_REQUIRE([LT_SYS_DLOPEN_DEPLIBS])dnl
AC_REQUIRE([gl_FUNC_ARGZ])dnl

m4_require([_LT_CHECK_OBJDIR])dnl
m4_require([_LT_HEADER_DLFCN])dnl
m4_require([_LT_ENABLE_INSTALL])dnl
m4_require([_LT_CHECK_DLPREOPEN])dnl

# In order that ltdl.c can compile, run AC_CONFIG_HEADERS for the user
# if they did not call it themself.  This is so that ltdl.h can pick up
# the parent projects config.h file, The first file in AC_CONFIG_HEADERS
# must contain the definitions required by ltdl.c.
m4_ifset([_AC_LIST_TAGS],
    [CONFIG_H=`echo "_AC_LIST_TAGS" | $GREP HEADERS | $SED 's,^[[ 	]]*,,;s,[[ :)]].*$,,'`],
  [m4_ifset([AC_LIST_HEADERS],
    [CONFIG_H=`echo "AC_LIST_HEADERS" | $SED 's,^[[ 	]]*,,;s,[[ :]].*$,,'`],
  [CONFIG_H=config.h;AC_CONFIG_HEADERS([config.h])]])
AC_SUBST([CONFIG_H])

AC_CHECK_HEADERS([memory.h unistd.h dl.h sys/dl.h dld.h mach-o/dyld.h],
	[], [], [AC_INCLUDES_DEFAULT])
AC_CHECK_HEADERS([string.h strings.h], [break], [], [AC_INCLUDES_DEFAULT])

AC_CHECK_FUNCS([closedir opendir readdir], [], [AC_LIBOBJ([lt__dirent])])
AC_CHECK_FUNCS([strlcat strlcpy], [], [AC_LIBOBJ([lt__strl])])

name=ltdl
LTDLOPEN=`eval "\\$ECHO \"$libname_spec\""`
AC_SUBST([LTDLOPEN])
])# LTDL_INIT

# Old name:
AU_DEFUN([AC_LIB_LTDL], [LTDL_INIT])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIB_LTDL], [])


# _LT_ENABLE_INSTALL
# ------------------
m4_defun([_LT_ENABLE_INSTALL],
[AC_ARG_ENABLE([ltdl-install],
    [AS_HELP_STRING([--enable-ltdl-install], [install libltdl])])

AM_CONDITIONAL(INSTALL_LTDL, test x"${enable_ltdl_install-no}" != xno)
AM_CONDITIONAL(CONVENIENCE_LTDL, test x"${enable_ltdl_convenience-no}" != xno)
])])# _LT_ENABLE_INSTALL


# LT_SYS_DLOPEN_DEPLIBS
# ---------------------
AC_DEFUN([LT_SYS_DLOPEN_DEPLIBS],
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_CACHE_CHECK([whether deplibs are loaded by dlopen],
  [lt_cv_sys_dlopen_deplibs],
  [# PORTME does your system automatically load deplibs for dlopen?
  # or its logical equivalent (e.g. shl_load for HP-UX < 11)
  # For now, we just catch OSes we know something about -- in the
  # future, we'll try test this programmatically.
  lt_cv_sys_dlopen_deplibs=unknown
  case $host_os in
  aix3*|aix4.1.*|aix4.2.*)
    # Unknown whether this is true for these versions of AIX, but
    # we want this `case' here to explicitly catch those versions.
    lt_cv_sys_dlopen_deplibs=unknown
    ;;
  aix[[45]]*)
    lt_cv_sys_dlopen_deplibs=yes
    ;;
  darwin*)
    # Assuming the user has installed a libdl from somewhere, this is true
    # If you are looking for one http://www.opendarwin.org/projects/dlcompat
    lt_cv_sys_dlopen_deplibs=yes
    ;;
  gnu* | linux* | kfreebsd*-gnu | knetbsd*-gnu)
    # GNU and its variants, using gnu ld.so (Glibc)
    lt_cv_sys_dlopen_deplibs=yes
    ;;
  hpux10*|hpux11*)
    lt_cv_sys_dlopen_deplibs=yes
    ;;
  irix[[12345]]*|irix6.[[01]]*)
    # Catch all versions of IRIX before 6.2, and indicate that we don't
    # know how it worked for any of those versions.
    lt_cv_sys_dlopen_deplibs=unknown
    ;;
  irix*)
    # The case above catches anything before 6.2, and it's known that
    # at 6.2 and later dlopen does load deplibs.
    lt_cv_sys_dlopen_deplibs=yes
    ;;
  netbsd*)
    lt_cv_sys_dlopen_deplibs=yes
    ;;
  openbsd*)
    lt_cv_sys_dlopen_deplibs=yes
    ;;
  osf[[1234]]*)
    # dlopen did load deplibs (at least at 4.x), but until the 5.x series,
    # it did *not* use an RPATH in a shared library to find objects the
    # library depends on, so we explicitly say `no'.
    lt_cv_sys_dlopen_deplibs=no
    ;;
  osf5.0|osf5.0a|osf5.1)
    # dlopen *does* load deplibs and with the right loader patch applied
    # it even uses RPATH in a shared library to search for shared objects
    # that the library depends on, but there's no easy way to know if that
    # patch is installed.  Since this is the case, all we can really
    # say is unknown -- it depends on the patch being installed.  If
    # it is, this changes to `yes'.  Without it, it would be `no'.
    lt_cv_sys_dlopen_deplibs=unknown
    ;;
  osf*)
    # the two cases above should catch all versions of osf <= 5.1.  Read
    # the comments above for what we know about them.
    # At > 5.1, deplibs are loaded *and* any RPATH in a shared library
    # is used to find them so we can finally say `yes'.
    lt_cv_sys_dlopen_deplibs=yes
    ;;
  qnx*)
    lt_cv_sys_dlopen_deplibs=yes
    ;;
  solaris*)
    lt_cv_sys_dlopen_deplibs=yes
    ;;
  esac
  ])
if test "$lt_cv_sys_dlopen_deplibs" != yes; then
 AC_DEFINE([LTDL_DLOPEN_DEPLIBS], [1],
    [Define if the OS needs help to load dependent libraries for dlopen().])
fi
])# LT_SYS_DLOPEN_DEPLIBS

# Old name:
AU_DEFUN([AC_LTDL_SYS_DLOPEN_DEPLIBS], [LT_SYS_DLOPEN_DEPLIBS])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LTDL_SYS_DLOPEN_DEPLIBS], [])


# LT_SYS_MODULE_EXT
# -----------------
AC_DEFUN([LT_SYS_MODULE_EXT],
[m4_require([_LT_SYS_DYNAMIC_LINKER])dnl
AC_CACHE_CHECK([which extension is used for runtime loadable modules],
  [libltdl_cv_shlibext],
[
module=yes
eval libltdl_cv_shlibext=$shrext_cmds
  ])
if test -n "$libltdl_cv_shlibext"; then
  m4_pattern_allow([LT_MODULE_EXT])dnl
  AC_DEFINE_UNQUOTED([LT_MODULE_EXT], ["$libltdl_cv_shlibext"],
    [Define to the extension used for runtime loadable modules, say, ".so".])
fi
])# LT_SYS_MODULE_EXT

# Old name:
AU_DEFUN([AC_LTDL_SHLIBEXT], [LT_SYS_MODULE_EXT])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LTDL_SHLIBEXT], [])


# LT_SYS_MODULE_PATH
# ------------------
AC_DEFUN([LT_SYS_MODULE_PATH],
[m4_require([_LT_SYS_DYNAMIC_LINKER])dnl
AC_CACHE_CHECK([which variable specifies run-time module search path],
  [lt_cv_module_path_var], [lt_cv_module_path_var="$shlibpath_var"])
if test -n "$lt_cv_module_path_var"; then
  m4_pattern_allow([LT_MODULE_PATH_VAR])dnl
  AC_DEFINE_UNQUOTED([LT_MODULE_PATH_VAR], ["$lt_cv_module_path_var"],
    [Define to the name of the environment variable that determines the run-time module search path.])
fi
])# LT_SYS_MODULE_PATH

# Old name:
AU_DEFUN([AC_LTDL_SHLIBPATH], [LT_SYS_MODULE_PATH])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LTDL_SHLIBPATH], [])


# LT_SYS_DLSEARCH_PATH
# ---------------------
AC_DEFUN([LT_SYS_DLSEARCH_PATH],
[m4_require([_LT_SYS_DYNAMIC_LINKER])dnl
AC_CACHE_CHECK([for the default library search path],
  [lt_cv_sys_dlsearch_path],
  [lt_cv_sys_dlsearch_path="$sys_lib_dlsearch_path_spec"])
if test -n "$lt_cv_sys_dlsearch_path"; then
  sys_dlsearch_path=
  for dir in $lt_cv_sys_dlsearch_path; do
    if test -z "$sys_dlsearch_path"; then
      sys_dlsearch_path="$dir"
    else
      sys_dlsearch_path="$sys_dlsearch_path$PATH_SEPARATOR$dir"
    fi
  done
  m4_pattern_allow([LT_DLSEARCH_PATH])dnl
  AC_DEFINE_UNQUOTED([LT_DLSEARCH_PATH], ["$sys_dlsearch_path"],
    [Define to the system default library search path.])
fi
])# LT_SYS_DLSEARCH_PATH

# Old name:
AU_DEFUN([AC_LTDL_SYSSEARCHPATH], [LT_SYS_DLSEARCH_PATH])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LTDL_SYSSEARCHPATH], [])


# _LT_CHECK_DLPREOPEN
# -----------------
m4_defun([_LT_CHECK_DLPREOPEN],
[m4_require([_LT_CMD_GLOBAL_SYMBOLS])dnl
AC_CACHE_CHECK([whether libtool supports -dlopen/-dlpreopen],
  [libltdl_cv_preloaded_symbols],
  [if test -n "$lt_cv_sys_global_symbol_pipe"; then
    libltdl_cv_preloaded_symbols=yes
  else
    libltdl_cv_preloaded_symbols=no
  fi
  ])
if test x"$libltdl_cv_preloaded_symbols" = xyes; then
  AC_DEFINE([HAVE_PRELOADED_SYMBOLS], [1],
    [Define if libtool can extract symbol lists from object files.])
fi
])# _LT_CHECK_DLPREOPEN


# LT_LIB_DLLOAD
# -------------
AC_DEFUN([LT_LIB_DLLOAD],
[m4_pattern_allow([^LT_DLLOADERS$])
LT_DLLOADERS=
AC_SUBST([LT_DLLOADERS])

AC_LANG_PUSH([C])

LIBADD_DLOPEN=
AC_CHECK_LIB([dl], [dlopen],
	[AC_DEFINE([HAVE_LIBDL], [1],
		   [Define if you have the libdl library or equivalent.])
	LIBADD_DLOPEN="-ldl" libltdl_cv_lib_dl_dlopen="yes"
	LT_DLLOADERS="$LT_DLLOADERS dlopen.la"],
    [AC_LINK_IFELSE([AC_LANG_PROGRAM([[#if HAVE_DLFCN_H
#  include <dlfcn.h>
#endif
    ]], [[dlopen(0, 0);]])],
	    [AC_DEFINE([HAVE_LIBDL], [1],
		       [Define if you have the libdl library or equivalent.])
	    libltdl_cv_func_dlopen="yes"
	    LT_DLLOADERS="$LT_DLLOADERS dlopen.la"],
	[AC_CHECK_LIB([svld], [dlopen],
		[AC_DEFINE([HAVE_LIBDL], [1],
			 [Define if you have the libdl library or equivalent.])
	        LIBADD_DLOPEN="-lsvld" libltdl_cv_func_dlopen="yes"
		LT_DLLOADERS="$LT_DLLOADERS dlopen.la"])])])
if test x"$libltdl_cv_func_dlopen" = xyes || test x"$libltdl_cv_lib_dl_dlopen" = xyes
then
  lt_save_LIBS="$LIBS"
  LIBS="$LIBS $LIBADD_DLOPEN"
  AC_CHECK_FUNCS([dlerror])
  LIBS="$lt_save_LIBS"
fi
AC_SUBST([LIBADD_DLOPEN])

LIBADD_SHL_LOAD=
AC_CHECK_FUNC([shl_load],
	[AC_DEFINE([HAVE_SHL_LOAD], [1],
		   [Define if you have the shl_load function.])
	LT_DLLOADERS="$LT_DLLOADERS shl_load.la"],
    [AC_CHECK_LIB([dld], [shl_load],
	    [AC_DEFINE([HAVE_SHL_LOAD], [1],
		       [Define if you have the shl_load function.])
	    LT_DLLOADERS="$LT_DLLOADERS shl_load.la"
	    LIBADD_SHL_LOAD="-ldld"])])
AC_SUBST([LIBADD_SHL_LOAD])

case $host_os in
darwin[[1567]].*)
# We only want this for pre-Mac OS X 10.4.
  AC_CHECK_FUNC([_dyld_func_lookup],
	[AC_DEFINE([HAVE_DYLD], [1],
		   [Define if you have the _dyld_func_lookup function.])
	LT_DLLOADERS="$LT_DLLOADERS dyld.la"])
  ;;
beos*)
  LT_DLLOADERS="$LT_DLLOADERS load_add_on.la"
  ;;
cygwin* | mingw* | os2* | pw32*)
  LT_DLLOADERS="$LT_DLLOADERS loadlibrary.la"
  ;;
esac

AC_CHECK_LIB([dld], [dld_link],
	[AC_DEFINE([HAVE_DLD], [1],
		   [Define if you have the GNU dld library.])
		LT_DLLOADERS="$LT_DLLOADERS dld_link.la"])
AC_SUBST([LIBADD_DLD_LINK])

m4_pattern_allow([^LT_DLPREOPEN$])
LT_DLPREOPEN=
if test -n "$LT_DLLOADERS"
then
  for lt_loader in $LT_DLLOADERS; do
    LT_DLPREOPEN="$LT_DLPREOPEN-dlpreopen $lt_loader "
  done
  AC_DEFINE([HAVE_LIBDLLOADER], [1],
            [Define if libdlloader will be built on this platform])
fi
AC_SUBST([LT_DLPREOPEN])

dnl This isn't used anymore, but set it for backwards compatibility
LIBADD_DL="$LIBADD_DLOPEN $LIBADD_SHL_LOAD"
AC_SUBST([LIBADD_DL])

AC_LANG_POP
])# LT_LIB_DLLOAD

# Old name:
AU_DEFUN([AC_LTDL_DLLIB], [LT_LIB_DLLOAD])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LTDL_DLLIB], [])


# LT_SYS_SYMBOL_USCORE
# ---------------------
# does the compiler prefix global symbols with an underscore?
AC_DEFUN([LT_SYS_SYMBOL_USCORE],
[m4_require([_LT_CMD_GLOBAL_SYMBOLS])dnl
AC_CACHE_CHECK([for _ prefix in compiled symbols],
  [lt_cv_sys_symbol_underscore],
  [lt_cv_sys_symbol_underscore=no
  cat > conftest.$ac_ext <<EOF
void nm_test_func(){}
int main(){nm_test_func;return 0;}
EOF
  if AC_TRY_EVAL(ac_compile); then
    # Now try to grab the symbols.
    ac_nlist=conftest.nm
    if AC_TRY_EVAL(NM conftest.$ac_objext \| $lt_cv_sys_global_symbol_pipe \> $ac_nlist) && test -s "$ac_nlist"; then
      # See whether the symbols have a leading underscore.
      if grep '^. _nm_test_func' "$ac_nlist" >/dev/null; then
        lt_cv_sys_symbol_underscore=yes
      else
        if grep '^. nm_test_func ' "$ac_nlist" >/dev/null; then
	  :
        else
	  echo "configure: cannot find nm_test_func in $ac_nlist" >&AS_MESSAGE_LOG_FD
        fi
      fi
    else
      echo "configure: cannot run $lt_cv_sys_global_symbol_pipe" >&AS_MESSAGE_LOG_FD
    fi
  else
    echo "configure: failed program was:" >&AS_MESSAGE_LOG_FD
    cat conftest.c >&AS_MESSAGE_LOG_FD
  fi
  rm -rf conftest*
  ])
  sys_symbol_underscore=$lt_cv_sys_symbol_underscore
  AC_SUBST([sys_symbol_underscore])
])# LT_SYS_SYMBOL_USCORE

# Old name:
AU_DEFUN([AC_LTDL_SYMBOL_USCORE], [LT_SYS_SYMBOL_USCORE])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LTDL_SYMBOL_USCORE], [])


# LT_FUNC_DLSYM_USCORE
# --------------------
AC_DEFUN([LT_FUNC_DLSYM_USCORE],
[AC_REQUIRE([LT_SYS_SYMBOL_USCORE])dnl
if test x"$lt_cv_sys_symbol_underscore" = xyes; then
  if test x"$libltdl_cv_func_dlopen" = xyes ||
     test x"$libltdl_cv_lib_dl_dlopen" = xyes ; then
	AC_CACHE_CHECK([whether we have to add an underscore for dlsym],
	  [libltdl_cv_need_uscore],
	  [libltdl_cv_need_uscore=unknown
          save_LIBS="$LIBS"
          LIBS="$LIBS $LIBADD_DLOPEN"
	  _LT_TRY_DLOPEN_SELF(
	    [libltdl_cv_need_uscore=no], [libltdl_cv_need_uscore=yes],
	    [],				 [libltdl_cv_need_uscore=cross])
	  LIBS="$save_LIBS"
	])
  fi
fi

if test x"$libltdl_cv_need_uscore" = xyes; then
  AC_DEFINE([NEED_USCORE], [1],
    [Define if dlsym() requires a leading underscore in symbol names.])
fi
])# LT_FUNC_DLSYM_USCORE

# Old name:
AU_DEFUN([AC_LTDL_DLSYM_USCORE], [LT_FUNC_DLSYM_USCORE])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LTDL_DLSYM_USCORE], [])
