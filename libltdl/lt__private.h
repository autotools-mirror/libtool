/* lt__private.h -- internal apis for libltdl
   Copyright (C) 2004 Free Software Foundation, Inc.
   Originally by Gary V. Vaughan  <gary@gnu.org>

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
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307  USA

*/

#if !defined(LT__PRIVATE_H)
#define LT__PRIVATE_H 1

#if defined(HAVE_CONFIG_H)
#  include HAVE_CONFIG_H
#endif

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>

#if defined(HAVE_UNISTD_H)
#  include <unistd.h>
#endif

#if defined(HAVE_STRING_H)
#  include <string.h>
#else
#  if defined(HAVE_STRINGS_H)
#    include <strings.h>
#  endif
#endif
#if defined(HAVE_MEMORY_H)
#  include <memory.h>
#endif

/* Import internal interfaces...  */
#include "lt__alloc.h"
#include "lt__dirent.h"
#include "lt__glibc.h"

/* ...and all exported interfaces.  */
#include "ltdl.h"

#if defined(WITH_DMALLOC)
#  include <dmalloc.h>
#endif

#if defined(DLL_EXPORT)
#  define LT_GLOBAL_DATA	__declspec(dllexport)
#else
#  define LT_GLOBAL_DATA
#endif


LT_BEGIN_C_DECLS

#if !defined(errno)
extern int errno;
#endif



/* --- ERROR HANDLING --- */

/* Extract the diagnostic strings from the error table macro in the same
   order as the enumerated indices in lt_error.h. */

static const char *lt__error_strings[] =
  {
#define LT_ERROR(name, diagnostic)	(diagnostic),
    lt_dlerror_table
#undef LT_ERROR

    0
  };

#define LT__STRERROR(name)	lt__error_strings[LT_CONC(LT_ERROR_,name)]



/* --- MUTEX LOCKING --- */

/* Macros to make it easier to run the lock functions only if they have
   been registered.  The reason for the complicated lock macro is to
   ensure that the stored error message from the last error is not
   accidentally erased if the current function doesn't generate an
   error of its own.  */

#define LT__MUTEX_LOCK()			LT_STMT_START {	\
	if (lt__mutex_lock_func) (*lt__mutex_lock_func)();	\
						} LT_STMT_END
#define LT__MUTEX_UNLOCK()			LT_STMT_START { \
	if (lt__mutex_unlock_func) (*lt__mutex_unlock_func)();\
						} LT_STMT_END
#define LT__MUTEX_SETERRORSTR(errormsg)		LT_STMT_START {	\
	if (lt__mutex_seterror_func)				\
		(*lt__mutex_seterror_func) (errormsg);		\
	else 	lt__last_error = (errormsg);	} LT_STMT_END
#define LT__MUTEX_GETERROR(errormsg)		LT_STMT_START {	\
	if (lt__mutex_seterror_func)				\
		(errormsg) = (*lt__mutex_geterror_func) ();	\
	else	(errormsg) = lt__last_error;	} LT_STMT_END
#define LT__MUTEX_SETERROR(errorcode)	     			\
	LT__MUTEX_SETERRORSTR(LT__STRERROR(errorcode))

/* The mutex functions stored here are global, and are necessarily the
   same for all threads that wish to share access to libltdl.  */
LT_SCOPE lt_dlmutex_lock	*lt__mutex_lock_func;
LT_SCOPE lt_dlmutex_unlock	*lt__mutex_unlock_func;
LT_SCOPE lt_dlmutex_seterror	*lt__mutex_seterror_func;
LT_SCOPE lt_dlmutex_geterror	*lt__mutex_geterror_func;
LT_SCOPE const char		*lt__last_error;

LT_END_C_DECLS

#endif /*!defined(LT__PRIVATE_H)*/
