/* ltdl.h -- generic dlopen functions
   Copyright (C) 1998-2000 Free Software Foundation, Inc.
   Originally by Thomas Tanner <tanner@ffii.org>

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

/* Only include this header file once. */
#ifndef LTDL_H
#define LTDL_H 1

#include <libltdl/lt_system.h>

LT_BEGIN_C_DECLS


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




/* LT_STRLEN can be used safely on NULL pointers.  */
#define LT_STRLEN(s)	(((s) && (s)[0]) ? strlen (s) : 0)



/* --- DYNAMIC MODULE LOADING API --- */


typedef	struct lt_dlhandle_struct *lt_dlhandle;	/* A loaded module.  */

/* Initialisation and finalisation functions for libltdl. */
LT_SCOPE int	    lt_dlinit		(void);
LT_SCOPE int	    lt_dlexit		(void);

/* Module search path manipulation.  */
LT_SCOPE int	    lt_dladdsearchdir	 (const char *search_dir);
LT_SCOPE int	    lt_dlinsertsearchdir (const char *before,
						  const char *search_dir);
LT_SCOPE int 	    lt_dlsetsearchpath	 (const char *search_path);
LT_SCOPE const char *lt_dlgetsearchpath	 (void);
LT_SCOPE int	    lt_dlforeachfile	 (
			const char *search_path,
			int (*func) (const char *filename, void *data),
			void *data);

/* Portable libltdl versions of the system dlopen() API. */
LT_SCOPE lt_dlhandle lt_dlopen		(const char *filename);
LT_SCOPE lt_dlhandle lt_dlopenext	(const char *filename);
LT_SCOPE void *	    lt_dlsym		(lt_dlhandle handle, const char *name);
LT_SCOPE const char *lt_dlerror		(void);
LT_SCOPE int	    lt_dlclose		(lt_dlhandle handle);

/* Module residency management. */
LT_SCOPE int	    lt_dlmakeresident	(lt_dlhandle handle);
LT_SCOPE int	    lt_dlisresident	(lt_dlhandle handle);




/* --- MUTEX LOCKING --- */


typedef void	lt_dlmutex_lock		(void);
typedef void	lt_dlmutex_unlock	(void);
typedef void	lt_dlmutex_seterror	(const char *errmsg);
typedef const char *lt_dlmutex_geterror	(void);

LT_SCOPE int	lt_dlmutex_register	(lt_dlmutex_lock *lock,
					 lt_dlmutex_unlock *unlock,
					 lt_dlmutex_seterror *seterror,
					 lt_dlmutex_geterror *geterror);




/* --- PRELOADED MODULE SUPPORT --- */


/* A preopened symbol. Arrays of this type comprise the exported
   symbols for a dlpreopened module. */
typedef struct {
  const char *name;
  void *     address;
} lt_dlsymlist;

LT_SCOPE int	lt_dlpreload	     (const lt_dlsymlist *preloaded);
LT_SCOPE int	lt_dlpreload_default (const lt_dlsymlist *preloaded);

#define LTDL_SET_PRELOADED_SYMBOLS() 			LT_STMT_START{	\
	extern const lt_dlsymlist lt_preloaded_symbols[];		\
	lt_dlpreload_default(lt_preloaded_symbols);			\
							}LT_STMT_END




/* --- MODULE INFORMATION --- */


/* Read only information pertaining to a loaded module. */
typedef	struct {
  char	*filename;		/* file name */
  char	*name;			/* module name */
  int	ref_count;		/* number of times lt_dlopened minus
				   number of times lt_dlclosed. */
} lt_dlinfo;

LT_SCOPE const lt_dlinfo *lt_dlgetinfo	    (lt_dlhandle handle);
LT_SCOPE lt_dlhandle	lt_dlhandle_next    (lt_dlhandle place);
LT_SCOPE lt_dlhandle	lt_dlhandle_find    (const char *module_name);
LT_SCOPE int		lt_dlforeach	    (
				int (*func) (lt_dlhandle handle, void *data),
				void *data);

/* Associating user data with loaded modules. */
typedef unsigned lt_dlcaller_id;

LT_SCOPE lt_dlcaller_id	lt_dlcaller_register  (void);
LT_SCOPE void *		lt_dlcaller_set_data  (lt_dlcaller_id key,
					       lt_dlhandle handle, void *data);
LT_SCOPE void *		lt_dlcaller_get_data  (lt_dlcaller_id key,
					       lt_dlhandle handle);



/* --- USER MODULE LOADER API --- */


typedef	struct lt_dlloader	lt_dlloader;
typedef void *			lt_user_data;
typedef void *			lt_module;

/* Function pointer types for creating user defined module loaders. */
typedef lt_module   lt_module_open	(lt_user_data loader_data,
					 const char *filename);
typedef int	    lt_module_close	(lt_user_data loader_data,
					 lt_module handle);
typedef void *	    lt_find_sym		(lt_user_data loader_data,
					 lt_module handle, const char *symbol);
typedef int	    lt_dlloader_exit	(lt_user_data loader_data);

struct lt_user_dlloader {
  const char	       *sym_prefix;
  lt_module_open       *module_open;
  lt_module_close      *module_close;
  lt_find_sym	       *find_sym;
  lt_dlloader_exit     *dlloader_exit;
  lt_user_data		dlloader_data;
};

LT_SCOPE lt_dlloader    *lt_dlloader_next    (lt_dlloader *place);
LT_SCOPE lt_dlloader    *lt_dlloader_find    (const char *loader_name);
LT_SCOPE const char     *lt_dlloader_name    (lt_dlloader *place);
LT_SCOPE lt_user_data   *lt_dlloader_data    (lt_dlloader *place);
LT_SCOPE int		lt_dlloader_add     (lt_dlloader *place,
				const struct lt_user_dlloader *dlloader,
				const char *loader_name);
LT_SCOPE int		lt_dlloader_remove  (const char *loader_name);



/* --- ERROR MESSAGE HANDLING --- */


/* Defining error strings alongside their symbolic names in a macro in
   this way allows us to expand the macro in different contexts with
   confidence that the enumeration of symbolic names will map correctly
   onto the table of error strings.  */
#define lt_dlerror_table						\
    LT_ERROR(UNKNOWN,		    "unknown error")			\
    LT_ERROR(DLOPEN_NOT_SUPPORTED,  "dlopen support not available")	\
    LT_ERROR(INVALID_LOADER,	    "invalid loader")			\
    LT_ERROR(INIT_LOADER,	    "loader initialization failed")	\
    LT_ERROR(REMOVE_LOADER,	    "loader removal failed")		\
    LT_ERROR(FILE_NOT_FOUND,	    "file not found")			\
    LT_ERROR(DEPLIB_NOT_FOUND,      "dependency library not found")	\
    LT_ERROR(NO_SYMBOLS,	    "no symbols defined")		\
    LT_ERROR(CANNOT_OPEN,	    "can't open the module")		\
    LT_ERROR(CANNOT_CLOSE,	    "can't close the module")		\
    LT_ERROR(SYMBOL_NOT_FOUND,      "symbol not found")			\
    LT_ERROR(NO_MEMORY,		    "not enough memory")		\
    LT_ERROR(INVALID_HANDLE,	    "invalid module handle")		\
    LT_ERROR(BUFFER_OVERFLOW,	    "internal buffer overflow")		\
    LT_ERROR(INVALID_ERRORCODE,     "invalid errorcode")		\
    LT_ERROR(SHUTDOWN,		    "library already shutdown")		\
    LT_ERROR(CLOSE_RESIDENT_MODULE, "can't close resident module")	\
    LT_ERROR(INVALID_MUTEX_ARGS,    "invalid mutex handler registration") \
    LT_ERROR(INVALID_POSITION,	    "invalid search path insert position")

/* Enumerate the symbolic error names. */
enum {
#define LT_ERROR(name, diagnostic)	LT_CONC(LT_ERROR_, name),
	lt_dlerror_table
#undef LT_ERROR

	LT_ERROR_MAX
};

/* These functions are only useful from inside custom module loaders. */
LT_SCOPE int	lt_dladderror	(const char *diagnostic);
LT_SCOPE int	lt_dlseterror	(int errorcode);



/* --- BINARY COMPATIBILITY WITH OLD LIBLTDL --- */

LT_SCOPE void * (*lt_dlmalloc)	(size_t size);
LT_SCOPE void * (*lt_dlrealloc)	(void *ptr, size_t size);
LT_SCOPE void	(*lt_dlfree)	(void *ptr);

# define lt_ptr		void *



/* --- SOURCE COMPATIBILITY WITH ANCIENT LIBLTDL --- */


#ifdef LT_NON_POSIX_NAMESPACE
#  define lt_ptr_t		void *
#  define lt_module_t		lt_module
#  define lt_module_open_t	lt_module_open
#  define lt_module_close_t	lt_module_close
#  define lt_find_sym_t		lt_find_sym
#  define lt_dlloader_exit_t	lt_dlloader_exit
#  define lt_dlloader_t		lt_dlloader
#  define lt_dlloader_data_t	lt_user_data
#endif

LT_END_C_DECLS

#endif /* !LTDL_H */
