/* lt_dlloader.h -- dynamic library loader interface
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

#if !defined(LT_DLLOADER_H)
#define LT_DLLOADER_H 1

#include <libltdl/lt_system.h>
#include <libltdl/lt_error.h>

LT_BEGIN_C_DECLS

typedef struct lt_user_dlloader lt_user_dlloader;
typedef	struct lt_dlloader	lt_dlloader;
typedef void *			lt_user_data;
typedef void *			lt_module;

/* Type of a function to get a loader's vtable:  */
typedef lt_user_dlloader *lt_get_vtable (lt_user_data loader_data);

/* Function pointer types for creating user defined module loaders:  */
typedef int	    lt_dlloader_init	(lt_user_data loader_data);
typedef int	    lt_dlloader_exit	(lt_user_data loader_data);
typedef lt_module   lt_module_open	(lt_user_data loader_data,
					 const char *filename);
typedef int	    lt_module_close	(lt_user_data loader_data,
					 lt_module handle);
typedef void *	    lt_find_sym		(lt_user_data loader_data,
					 lt_module handle, const char *symbol);

/* Default priority is LT_DLLOADER_PREPEND if none is explicitly given.  */
typedef enum {
  LT_DLLOADER_PREPEND = 0, LT_DLLOADER_APPEND
} lt_dlloader_priority;

struct lt_user_dlloader {
  const char *		name;
  const char *		sym_prefix;
  lt_module_open *	module_open;
  lt_module_close *	module_close;
  lt_find_sym *		find_sym;
  lt_dlloader_init *	dlloader_init;
  lt_dlloader_exit *	dlloader_exit;
  lt_user_data		dlloader_data;
  lt_dlloader_priority	priority;
};

LT_SCOPE lt_dlloader    *lt_dlloader_next    (lt_dlloader *place);
LT_SCOPE lt_dlloader    *lt_dlloader_find    (const char *loader_name);
LT_SCOPE const char     *lt_dlloader_name    (lt_dlloader *place);
LT_SCOPE lt_user_data   *lt_dlloader_data    (lt_dlloader *place);
LT_SCOPE int		lt_dlloader_add
				(const struct lt_user_dlloader *dlloader,
				 lt_user_data data);
LT_SCOPE int		lt_dlloader_remove  (const char *loader_name);


LT_END_C_DECLS

#endif /*!defined(LT_DLLOADER_H)*/
