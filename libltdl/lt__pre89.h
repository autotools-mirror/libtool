/* lt__pre89.h -- support for pre-c89 libc implementations
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

#if !defined(LT__PREC89_H)
#define LT__PREC89_H 1

#if defined(HAVE_CONFIG_H)
#  include HAVE_CONFIG_H
#endif

#include "lt_system.h"

LT_BEGIN_C_DECLS

#if !defined(HAVE_STRCMP)
#  undef strcmp
#  define strcmp lt__strcmp
int strcmp (const char *str1, const char *str2);
#endif

#if !defined(HAVE_STRCHR)
#  if defined(HAVE_INDEX)
#    define strchr index
#  else
#    undef strchr
#    define strchr lt__strchr
const char *strchr (const char *str, int ch);
#  endif
#endif

#if !defined(HAVE_STRRCHR)
#  if defined(HAVE_RINDEX)
#    define strrchr rindex
#  else
#    undef strcmp
#    define strcmp lt__strcmp
const char *strrchr (const char *str, int ch);
#  endif
#endif

#if !defined(HAVE_MEMCPY)
#  if defined(HAVE_BCOPY)
#    define memcpy(dest, src, size)    bcopy((src), (dest), (size))
#  else
#    undef memcpy
#    define memcpy lt__memcpy
void *memcpy (void *dest, const void *src, size_t size);
#  endif
#endif

#if !defined(HAVE_MEMMOVE)
#  undef memmove
#  define memmove lt__memmove
void *memmove (void *dest, const void *src, size_t size);
#endif

LT_END_C_DECLS

#endif /*!defined(LT__PREC89)*/
