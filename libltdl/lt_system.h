/* lt_system.h -- system portability abstraction layer
   Copyright (C) 2004 Free Software Foundation, Inc.
   Originally by Gary V. Vaughan <gary@gnu.org>

   NOTE: The canonical source of this file is maintained with the
   GNU Libtool package.  Report bugs to bug-libtool@gnu.org.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

As a special exception to the GNU Lesser General Public License,
if you distribute this file as part of a program or library that
is built using GNU libtool, you may include it under the same
distribution terms that you use for the rest of that program.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free
Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307  USA
*/

#ifndef LT_SYSTEM_H
#define LT_SYSTEM_H 1

#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>

/* Some systems do not define EXIT_*, even with STDC_HEADERS.  */
#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
# define EXIT_FAILURE 1
#endif

/* Just pick a big number... */
#define LT_FILENAME_MAX 2048


/* Saves on those hard to debug '\0' typos....  */
#define LT_EOS_CHAR	'\0'

/* LTDL_BEGIN_C_DECLS should be used at the beginning of your declarations,
   so that C++ compilers don't mangle their names.  Use LTDL_END_C_DECLS at
   the end of C declarations. */
#ifdef __cplusplus
# define LT_BEGIN_C_DECLS	extern "C" {
# define LT_END_C_DECLS		}
#else
# define LT_BEGIN_C_DECLS	/* empty */
# define LT_END_C_DECLS		/* empty */
#endif

/* LT_STMT_START/END are used to create macros which expand to a
   a single compound statement in a portable way.  */
#if defined (__GNUC__) && !defined (__STRICT_ANSI__) && !defined (__cplusplus)
#  define LT_STMT_START        (void)(
#  define LT_STMT_END          )
#else
#  if (defined (sun) || defined (__sun__))
#    define LT_STMT_START      if (1)
#    define LT_STMT_END        else (void)0
#  else
#    define LT_STMT_START      do
#    define LT_STMT_END        while (0)
#  endif
#endif

/* Canonicalise Windows and Cygwin recognition macros.
   To match the values set by recent Cygwin compilers, make sure that if
   __CYGWIN__ is defined (after canonicalisation), __WINDOWS__ is NOT!  */
#if defined(__CYGWIN32__) && !defined(__CYGWIN__)
# define __CYGWIN__ __CYGWIN32__
#endif
#if defined(__CYGWIN__)
# if defined(__WINDOWS__)
#   undef __WINDOWS__
# endif
#elif defined(_WIN32)
# define __WINDOWS__ _WIN32
#elif defined(WIN32)
# define __WINDOWS__ WIN32
#endif
#if defined(__CYGWIN__) && defined(__WINDOWS__)
# undef __WINDOWS__
#endif


/* DLL building support on win32 hosts;  mostly to workaround their
   ridiculous implementation of data symbol exporting. */
#ifndef LT_SCOPE
#  ifdef __WINDOWS__
#    ifdef DLL_EXPORT		/* defined by libtool (if required) */
#      define LT_SCOPE	__declspec(dllexport)
#    endif
#    ifdef LIBLTDL_DLL_IMPORT	/* define if linking with this dll */
#      define LT_SCOPE	extern __declspec(dllimport)
#    endif
#  endif
#  ifndef LT_SCOPE		/* static linking or !__WINDOWS__ */
#    define LT_SCOPE	extern
#  endif
#endif


#ifdef __WINDOWS__
/* LT_DIRSEP_CHAR is accepted *in addition* to '/' as a directory
   separator when it is set. */
# define LT_DIRSEP_CHAR		'\\'
# define LT_PATHSEP_CHAR	';'
#else
# define LT_PATHSEP_CHAR	':'
#endif

#if defined(_MSC_VER) /* Visual Studio */
#  define R_OK 4
#endif

/* fopen() mode flags for reading a text file */
#undef	LT_READTEXT_MODE
#if defined(__WINDOWS__) || defined(__CYGWIN__)
#  define LT_READTEXT_MODE "rt"
#else
#  define LT_READTEXT_MODE "r"
#endif

/* LT_CONC creates a new concatenated symbol for the compiler
   in a portable way.  */
#if defined(__STDC__) || defined(__cplusplus) || defined(_MSC_VER)
#  define LT_CONC(s,t)	s##t
#else
#  define LT_CONC(s,t)	s/**/t
#endif

#endif /*!LT__SYSTEM_H */
