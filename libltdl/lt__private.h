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

#ifndef LT__PRIVATE_H
#define LT__PRIVATE_H 1

#ifdef HAVE_CONFIG_H
#  include HAVE_CONFIG_H
#endif

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>

#if HAVE_UNISTD_H
#  include <unistd.h>
#endif

#if HAVE_STRING_H
#  include <string.h>
#else
#  if HAVE_STRINGS_H
#    include <strings.h>
#  endif
#endif
#if HAVE_MEMORY_H
#  include <memory.h>
#endif

#include "lt__alloc.h"
#include "lt__dirent.h"
#include "lt__pre89.h"
#include "lt_system.h"
#include "ltdl.h"

#if WITH_DMALLOC
#  include <dmalloc.h>
#endif

#ifdef DLL_EXPORT
#  define LT_GLOBAL_DATA	__declspec(dllexport)
#else
#  define LT_GLOBAL_DATA
#endif

LT_BEGIN_C_DECLS

#ifndef errno
extern int errno;
#endif

LT_END_C_DECLS

#endif /*!LT__PRIVATE_H*/
