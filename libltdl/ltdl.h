/* ltdl.h -- generic dlopen functions
   Copyright (C) 1998-2000 Free Software Foundation, Inc.
   Originally by Thomas Tanner <tanner@ffii.org>
   This file is part of GNU Libtool.

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

/* Only include this header file once. */
#ifndef LTDL_H
#define LTDL_H 1

#include <sys/types.h>		/* for size_t declaration */


/* --- MACROS FOR PORTABILITY --- */


/* LTDL_BEGIN_C_DECLS should be used at the beginning of your declarations,
   so that C++ compilers don't mangle their names.  Use LTDL_END_C_DECLS at
   the end of C declarations. */
#ifdef __cplusplus
# define LTDL_BEGIN_C_DECLS	extern "C" {
# define LTDL_END_C_DECLS	}
#else
# define LTDL_BEGIN_C_DECLS	/* empty */
# define LTDL_END_C_DECLS	/* empty */
#endif

LTDL_BEGIN_C_DECLS


/* LTDL_PARAMS is a macro used to wrap function prototypes, so that compilers
   that don't understand ANSI C prototypes still work, and ANSI C
   compilers can issue warnings about type mismatches.  */
#if defined (__STDC__) || defined (_AIX) || (defined (__mips) && defined (_SYSTYPE_SVR4)) || defined(WIN32) || defined(__cplusplus)
# define LTDL_PARAMS(protos)	protos
# define lt_ptr_t	void*
#else
# define LTDL_PARAMS(protos)	()
# define lt_ptr_t	char*
#endif

/* LTDL_STMT_START/END are used to create macros which expand to a
   a single compound statement in a portable way.  */
#if defined (__GNUC__) && !defined (__STRICT_ANSI__) && !defined (__cplusplus)
#  define LTDL_STMT_START        (void)(
#  define LTDL_STMT_END          )
#else
#  if (defined (sun) || defined (__sun__))
#    define LTDL_STMT_START      if (1)
#    define LTDL_STMT_END        else (void)0
#  else
#    define LTDL_STMT_START      do
#    define LTDL_STMT_END        while (0)
#  endif
#endif

/* LTDL_CONC creates a new concatenated symbol for the compiler
   in a portable way.  */
#if defined(__STDC__) || defined(__cplusplus)
#  define LTDL_CONC(s,t)	s##t
#else
#  define LTDL_CONC(s,t)	s/**/t
#endif




/* --- WINDOWS SUPPORT --- */


/* Canonicalise Windows and Cygwin recognition macros.  */
#ifdef __CYGWIN32__
#  ifndef __CYGWIN__
#    define __CYGWIN__ __CYGWIN32__
#  endif
#endif
#if defined(_WIN32) || defined(WIN32)
#  ifndef __WINDOWS__
#    ifdef _WIN32
#      define __WINDOWS__ _WIN32
#    else
#      ifdef WIN32
#        define __WINDOWS__ WIN32
#      endif
#    endif
#  endif
#endif

#ifdef __WINDOWS__
#  ifndef __CYGWIN__
/* LTDL_DIRSEP_CHAR is accepted *in addition* to '/' as a directory
   separator when it is set. */
#    define LTDL_DIRSEP_CHAR	'\\'
#    define LTDL_PATHSEP_CHAR	';'
#  endif
#endif
#ifndef LTDL_PATHSEP_CHAR
#  define LTDL_PATHSEP_CHAR	':'
#endif

/* DLL building support on win32 hosts;  mostly to workaround their
   ridiculous implementation of data symbol exporting. */
#ifndef LTDL_SCOPE
#  ifdef __WINDOWS__
#    ifdef DLL_EXPORT		/* defined by libtool (if required) */
#      define LTDL_SCOPE	__declspec(dllexport)
#    endif
#    ifdef LIBLTDL_DLL_IMPORT	/* define if linking with this dll */
#      define LTDL_SCOPE	extern __declspec(dllimport)
#    endif
#  endif
#  ifndef LTDL_SCOPE		/* static linking or !__WINDOWS__ */
#    define LTDL_SCOPE	extern
#  endif
#endif




/* --- DYNAMIC MODULE LOADING API --- */


typedef	struct lt_dlhandle_t *lt_dlhandle;	/* A loaded module.  */

/* Initialisation and finalisation functions for libltdl. */
extern	int	    lt_dlinit		LTDL_PARAMS((void));
extern	int	    lt_dlexit		LTDL_PARAMS((void));

/* Module search path manipultation.  */
extern	int	    lt_dladdsearchdir	LTDL_PARAMS((const char *search_dir));
extern	int 	    lt_dlsetsearchpath	LTDL_PARAMS((const char *search_path));
extern	const char *lt_dlgetsearchpath	LTDL_PARAMS((void));

/* Portable libltdl versions of the system dlopen() API. */
extern	lt_dlhandle lt_dlopen		LTDL_PARAMS((const char *filename));
extern	lt_dlhandle lt_dlopenext	LTDL_PARAMS((const char *filename));
extern	lt_ptr_t    lt_dlsym		LTDL_PARAMS((lt_dlhandle handle,
						     const char *name));
extern	const char *lt_dlerror		LTDL_PARAMS((void));
extern	int	    lt_dlclose		LTDL_PARAMS((lt_dlhandle handle));

/* Pointers to memory management functions to be used by libltdl. */
LTDL_SCOPE  lt_ptr_t (*lt_dlmalloc)	LTDL_PARAMS((size_t size));
LTDL_SCOPE  void   (*lt_dlfree)		LTDL_PARAMS((lt_ptr_t ptr));




/* --- PRELOADED MODULE SUPPORT --- */


/* A preopened symbol. Arrays of this type comprise the exported
   symbols for a dlpreopened module. */
typedef struct {
  const char *name;
  lt_ptr_t address;
} lt_dlsymlist;

extern	int	lt_dlpreload	LTDL_PARAMS((const lt_dlsymlist *preloaded));
extern	int	lt_dlpreload_default
				LTDL_PARAMS((const lt_dlsymlist *preloaded));

#define LTDL_SET_PRELOADED_SYMBOLS() 		LTDL_STMT_START{	\
	extern const lt_dlsymlist lt_preloaded_symbols[];		\
	lt_dlpreload_default(lt_preloaded_symbols);			\
						}LTDL_STMT_END




/* --- MODULE INFORMATION --- */


/* Read only information pertaining to a loaded module. */
typedef	struct {
  char	*filename;		/* file name */
  char	*name;			/* module name */
  int	ref_count;		/* number of times lt_dlopened minus
				   number of times lt_dlclosed. */
} lt_dlinfo;

extern	const lt_dlinfo	 *lt_dlgetinfo    LTDL_PARAMS((lt_dlhandle handle));
extern	int		  lt_dlforeach    LTDL_PARAMS((
			int (*func)(lt_dlhandle handle, lt_ptr_t data),
			lt_ptr_t data));




/* --- USER MODULE LOADER API --- */


typedef	struct lt_dlloader_t    lt_dlloader_t;
typedef lt_ptr_t	        lt_dlloader_data_t;
typedef lt_ptr_t	        lt_module_t;

/* Function pointer types for creating user defined module loaders. */
typedef lt_module_t lt_module_open_t	LTDL_PARAMS((
					    lt_dlloader_data_t loader_data,
					    const char *filename));
typedef int	    lt_module_close_t	LTDL_PARAMS((
					    lt_dlloader_data_t loader_data,
					    lt_module_t handle));
typedef lt_ptr_t    lt_find_sym_t	LTDL_PARAMS((
					    lt_dlloader_data_t loader_data,
					    lt_module_t handle,
					    const char *symbol));
typedef int	    lt_dlloader_exit_t	LTDL_PARAMS((
					    lt_dlloader_data_t loader_data));

struct lt_user_dlloader {
  const char	       *sym_prefix;
  lt_module_open_t     *module_open;
  lt_module_close_t    *module_close;
  lt_find_sym_t	       *find_sym;
  lt_dlloader_exit_t   *dlloader_exit;
  lt_dlloader_data_t	dlloader_data;
};

extern	lt_dlloader_t  *lt_dlloader_next    LTDL_PARAMS((
						lt_dlloader_t *place));
extern	lt_dlloader_t  *lt_dlloader_find    LTDL_PARAMS((
						const char *loader_name));
extern	const char     *lt_dlloader_name    LTDL_PARAMS((
						lt_dlloader_t *place));
extern	lt_dlloader_data_t *lt_dlloader_data LTDL_PARAMS((
						lt_dlloader_t *place));
extern	int		lt_dlloader_add     LTDL_PARAMS((
						lt_dlloader_t *place,
						const struct lt_user_dlloader *dlloader,
						const char *loader_name));
extern	int		lt_dlloader_remove  LTDL_PARAMS((
						const char *loader_name));



/* --- ERROR MESSAGE HANDLING --- */


/* Defining error strings alongside their symbolic names in a macro in
   this way allows us to expand the macro in different contexts with
   confidence that the enumeration of symbolic names will map correctly
   onto the table of error strings.  */
#define ltdl_error_table						\
    LTDL_ERROR(UNKNOWN,		    "unknown error")			\
    LTDL_ERROR(DLOPEN_NOT_SUPPORTED,"dlopen support not available")	\
    LTDL_ERROR(INVALID_LOADER,	    "invalid loader")			\
    LTDL_ERROR(INIT_LOADER,	    "loader initialization failed")	\
    LTDL_ERROR(REMOVE_LOADER,	    "loader removal failed")		\
    LTDL_ERROR(FILE_NOT_FOUND,	    "file not found")			\
    LTDL_ERROR(DEPLIB_NOT_FOUND,    "dependency library not found")	\
    LTDL_ERROR(NO_SYMBOLS,	    "no symbols defined")		\
    LTDL_ERROR(CANNOT_OPEN,	    "can't open the module")		\
    LTDL_ERROR(CANNOT_CLOSE,	    "can't close the module")		\
    LTDL_ERROR(SYMBOL_NOT_FOUND,    "symbol not found")			\
    LTDL_ERROR(NO_MEMORY,	    "not enough memory")		\
    LTDL_ERROR(INVALID_HANDLE,	    "invalid module handle")		\
    LTDL_ERROR(BUFFER_OVERFLOW,	    "internal buffer overflow")		\
    LTDL_ERROR(INVALID_ERRORCODE,   "invalid errorcode")		\
    LTDL_ERROR(SHUTDOWN,	    "library already shutdown")

/* Enumerate the symbolic error names. */
enum {
#define LTDL_ERROR(name, diagnostic)	LTDL_CONC(LTDL_ERROR_, name),
	ltdl_error_table
#undef LTDL_ERROR

	LTDL_ERROR_MAX
};

/* These functions are only useful from inside custom module loaders. */
extern int lt_dladderror LTDL_PARAMS((const char *diagnostic));
extern int lt_dlseterror LTDL_PARAMS((int errorcode));

LTDL_END_C_DECLS

#endif /* !LTDL_H */
