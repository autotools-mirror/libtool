/* lt__glibc.h -- support for non glibc environments
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

#ifndef LT__GLIBC_H
#define LT__GLIBC_H 1

#ifdef HAVE_CONFIG_H
#  include HAVE_CONFIG_H
#endif

#include "lt_system.h"

/* First redefine any glibc symbols we reimplement... */
#undef  argz_append
#define argz_append		lt__argz_append
#undef  argz_create_sep
#define argz_create_sep		lt__argz_create_sep
#undef  argz_insert
#define argz_insert		lt__argz_insert
#undef  argz_next
#define argz_next		lt__argz_next
#undef  argz_stringify
#define argz_stringify		lt__argz_stringify

/* ...import our implementations into the lt__ namespace... */
#include "argz.h"

/* ...finally, we revert to the library implementations of any symbols
   that are provided by the host since they may be more optimised (say
   with inline assembler) than the generic versions we provide here.  */
#if HAVE_ARGZ_APPEND
#  undef argz_append
#endif
#if HAVE_ARGZ_CREATE_SEP
#  undef argz_create_sep
#endif
#if HAVE_ARGZ_INSERT
#  undef argz_insert
#endif
#if HAVE_ARGZ_NEXT
#  undef argz_next
#endif
#if HAVE_ARGZ_STRINGIFY
#  undef argz_stringify
#endif

#endif /*!LT__GLIBC_H*/
