/* ltdl.h -- generic dlopen functions
   Copyright (C) 1998-2000 Free Software Foundation, Inc.
   Originally by Thomas Tanner <tanner@ffii.org>
   This file is part of GNU Libtool.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

As a special exception to the GNU Library General Public License,
if you distribute this file as part of a program that uses GNU libtool
to create libraries and programs, you may include it under the same
distribution terms that you use for the rest of that program.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free
Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307  USA
*/

/* Only include this header file once. */
#ifndef _LTDL_H_
#define _LTDL_H_ 1

/* Canonicalise Windows and Cygwin recognition macros.  */
#ifdef __CYGWIN32__
#  ifndef __CYGWIN__
#    define __CYGWIN__ __CYGWIN32__
#  endif
#endif
#ifdef _WIN32
#  ifndef WIN32
#    define WIN32 _WIN32
#  endif
#endif

/* __BEGIN_DECLS should be used at the beginning of your declarations,
   so that C++ compilers don't mangle their names.  Use __END_DECLS at
   the end of C declarations. */
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

/* LTDL_PARAMS is a macro used to wrap function prototypes, so that compilers
   that don't understand ANSI C prototypes still work, and ANSI C
   compilers can issue warnings about type mismatches. */
#undef LTDL_PARAMS
#undef lt_ptr_t
#if defined (__STDC__) || defined (_AIX) || (defined (__mips) && defined (_SYSTYPE_SVR4)) || defined(WIN32) || defined(__cplusplus)
# define LTDL_PARAMS(protos)	protos
# define lt_ptr_t	void*
#else
# define LTDL_PARAMS(protos)	()
# define lt_ptr_t	char*
#endif

/* LTDL_STMT_START/END are used to create macros which expand to a
   a single compound statement in a portable way. */
#undef LTDL_STMT_START
#undef LTDL_STMT_END
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


#ifdef WIN32
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
#  ifdef _WIN32
#    ifdef DLL_EXPORT		/* defined by libtool (if required) */
#      define LTDL_SCOPE	__declspec(dllexport)
#    endif
#    ifdef LIBLTDL_DLL_IMPORT	/* define if linking with this dll */
#      define LTDL_SCOPE	extern __declspec(dllimport)
#    endif
#  endif
#  ifndef LTDL_SCOPE		/* static linking or !_WIN32 */
#    define LTDL_SCOPE	extern
#  endif
#endif

#include <stdlib.h>

#define ltdl_error_table						\
	LTDL_ERROR(UNKNOWN, "unknown error")				\
	LTDL_ERROR(DLOPEN_NOT_SUPPORTED, "dlopen support not available")\
	LTDL_ERROR(INVALID_TYPE, "invalid dltype")			\
	LTDL_ERROR(INIT_TYPE, "dltype initialization failed")		\
	LTDL_ERROR(FILE_NOT_FOUND, "file not found")			\
	LTDL_ERROR(DEPLIB_NOT_FOUND, "dependency library not found")	\
	LTDL_ERROR(NO_SYMBOLS, "no symbols defined")			\
	LTDL_ERROR(CANNOT_OPEN, "can't open the module")		\
	LTDL_ERROR(CANNOT_CLOSE, "can't close the module")		\
	LTDL_ERROR(SYMBOL_NOT_FOUND, "symbol not found")		\
	LTDL_ERROR(NO_MEMORY, "not enough memory")			\
	LTDL_ERROR(INVALID_HANDLE, "invalid module handle")		\
	LTDL_ERROR(BUFFER_OVERFLOW, "internal buffer overflow")		\
	LTDL_ERROR(INVALID_ERRORCODE, "invalid errorcode")		\
	LTDL_ERROR(SHUTDOWN, "library already shutdown")

#ifdef __STDC__ 
#  define LTDL_ERROR(name, diagnostic)	LTDL_ERROR_##name,
#else
#  define LTDL_ERROR(name, diagnostic)	LTDL_ERROR_/**/name,
#endif
enum {
	ltdl_error_table
	LTDL_ERROR_MAX
};
#undef LTDL_ERROR

#ifdef _LTDL_COMPILE_
typedef	struct lt_dlhandle_t *lt_dlhandle;
#else
typedef	lt_ptr_t lt_dlhandle;
#endif

typedef lt_ptr_t lt_syshandle;

typedef struct {
	const char *name;
	lt_ptr_t address;
} lt_dlsymlist;

typedef	struct {
	char	*filename;	/* file name */
	char	*name;		/* module name */
	int	ref_count;	/* reference count */
} lt_dlinfo;

typedef int lt_mod_init_t LTDL_PARAMS((void));
typedef int lt_mod_exit_t LTDL_PARAMS((void));
typedef lt_syshandle lt_lib_open_t LTDL_PARAMS((const char *filename));
typedef int lt_lib_close_t LTDL_PARAMS((lt_syshandle handle));
typedef lt_ptr_t lt_find_sym_t LTDL_PARAMS((lt_syshandle handle, const char *symbol));

typedef struct lt_dltype_t {
	struct lt_dltype_t *next;
	const char *sym_prefix;	/* prefix for symbols */
	lt_mod_init_t *mod_init;
	lt_mod_exit_t *mod_exit;
	lt_lib_open_t *lib_open;
	lt_lib_close_t *lib_close;
	lt_find_sym_t *find_sym;
} lt_dltype_t;

__BEGIN_DECLS
extern int lt_dlinit LTDL_PARAMS((void));
extern int lt_dladdtype LTDL_PARAMS((lt_dltype_t *dltype));
extern lt_dltype_t *lt_dlgettypes LTDL_PARAMS((void));
extern int lt_dlsettypes LTDL_PARAMS((lt_dltype_t *dltypes));
extern int lt_dlpreload LTDL_PARAMS((const lt_dlsymlist *preloaded));
extern int lt_dlpreload_default LTDL_PARAMS((const lt_dlsymlist *preloaded));
extern int lt_dlexit LTDL_PARAMS((void));
extern lt_dlhandle lt_dlopen LTDL_PARAMS((const char *filename));
extern lt_dlhandle lt_dlopenext LTDL_PARAMS((const char *filename));
extern int lt_dlclose LTDL_PARAMS((lt_dlhandle handle));
extern lt_ptr_t lt_dlsym LTDL_PARAMS((lt_dlhandle handle, const char *name));
extern const char *lt_dlerror LTDL_PARAMS((void));
extern int lt_dladdsearchdir LTDL_PARAMS((const char *search_dir));
extern int lt_dlsetsearchpath LTDL_PARAMS((const char *search_path));
extern const char *lt_dlgetsearchpath LTDL_PARAMS((void));
extern int lt_dlsetdata LTDL_PARAMS((lt_dlhandle handle, lt_ptr_t data));
extern lt_ptr_t lt_dlgetdata LTDL_PARAMS((lt_dlhandle handle));
extern const lt_dlinfo *lt_dlgetinfo LTDL_PARAMS((lt_dlhandle handle));
extern int lt_dlforeach LTDL_PARAMS((
		int (*func)(lt_dlhandle handle, lt_ptr_t data), lt_ptr_t data));
extern int lt_dladderror LTDL_PARAMS((const char *diagnostic));
extern int lt_dlseterror LTDL_PARAMS((int errorcode));

#define LTDL_SET_PRELOADED_SYMBOLS() 		LTDL_STMT_START{	\
	extern const lt_dlsymlist lt_preloaded_symbols[];		\
	lt_dlpreload_default(lt_preloaded_symbols);			\
						}LTDL_STMT_END

LTDL_SCOPE lt_ptr_t (*lt_dlmalloc)LTDL_PARAMS((size_t size));
LTDL_SCOPE lt_ptr_t (*lt_dlrealloc)LTDL_PARAMS((lt_ptr_t ptr, size_t size));
LTDL_SCOPE void (*lt_dlfree)LTDL_PARAMS((lt_ptr_t ptr));

__END_DECLS

#endif /* !_LTDL_H_ */
