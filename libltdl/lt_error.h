/* lt_error.h -- error propogation interface
   Copyright (C) 1999, 2000, 2001, 2004 Free Software Foundation, Inc.
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
#if !defined(LT_ERROR_H)
#define LT_ERROR_H 1

#include <libltdl/lt_system.h>

LT_BEGIN_C_DECLS

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


LT_END_C_DECLS

#endif /*!defined(LT_ERROR_H)*/
