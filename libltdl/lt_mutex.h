/* lt_mutex.h -- mutex locking interface
   Copyright (C) 2001, 2004 Free Software Foundation, Inc.
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

/* Only include this header file once. */
#ifndef LT_MUTEX_H
#define LT_MUTEX_H 1

#include <libltdl/lt_system.h>

LT_BEGIN_C_DECLS

typedef void	lt_dlmutex_lock		(void);
typedef void	lt_dlmutex_unlock	(void);
typedef void	lt_dlmutex_seterror	(const char *errmsg);
typedef const char *lt_dlmutex_geterror	(void);

LT_SCOPE int	lt_dlmutex_register	(lt_dlmutex_lock *lock,
					 lt_dlmutex_unlock *unlock,
					 lt_dlmutex_seterror *seterror,
					 lt_dlmutex_geterror *geterror);

LT_END_C_DECLS

#endif /*!LT_MUTEX_H*/
