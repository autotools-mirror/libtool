/* loader-dlopen.c --  dynamic linking with dlopen/dlsym
   Copyright (C) 1998, 1999, 2000, 2004 Free Software Foundation, Inc.
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
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307  USA

*/

#include "lt__private.h"
#include "lt_dlloader.h"

#if defined(HAVE_DLFCN_H)
#  include <dlfcn.h>
#endif

#if defined(HAVE_SYS_DL_H)
#  include <sys/dl.h>
#endif

/* We may have to define LT_LAZY_OR_NOW in the command line if we
   find out it does not work in some platform. */
#if !defined(LT_LAZY_OR_NOW)
#  if defined(RTLD_LAZY)
#    define LT_LAZY_OR_NOW	RTLD_LAZY
#  else
#    if defined(DL_LAZY)
#      define LT_LAZY_OR_NOW	DL_LAZY
#    endif
#  endif /* !RTLD_LAZY */
#endif
#if !defined(LT_LAZY_OR_NOW)
#  if defined(RTLD_NOW)
#    define LT_LAZY_OR_NOW	RTLD_NOW
#  else
#    if defined(DL_NOW)
#      define LT_LAZY_OR_NOW	DL_NOW
#    endif
#  endif /* !RTLD_NOW */
#endif
#if !defined(LT_LAZY_OR_NOW)
#  define LT_LAZY_OR_NOW	0
#endif /* !LT_LAZY_OR_NOW */

#if defined(HAVE_DLERROR)
#  define DLERROR(arg)	dlerror ()
#else
#  define DLERROR(arg)	LT__STRERROR (arg)
#endif

#define DL__MUTEX_SETERROR(errorcode) \
	LT__MUTEX_SETERRORSTR (DLERROR (errorcode))

static lt_module
sys_dl_open (lt_user_data loader_data, const char *filename)
{
  lt_module   module   = dlopen (filename, LT_LAZY_OR_NOW);

  if (!module)
    {
      DL__MUTEX_SETERROR (CANNOT_OPEN);
    }

  return module;
}

static int
sys_dl_close (lt_user_data loader_data, lt_module module)
{
  int errors = 0;

  if (dlclose (module) != 0)
    {
      DL__MUTEX_SETERROR (CANNOT_CLOSE);
      ++errors;
    }

  return errors;
}

static void *
sys_dl_sym (lt_user_data loader_data, lt_module module, const char *symbol)
{
  void *address = dlsym (module, symbol);

  if (!address)
    {
      DL__MUTEX_SETERROR (SYMBOL_NOT_FOUND);
    }

  return address;
}

struct lt_user_dlloader lt__sys_dl =
  {
#  if defined(NEED_USCORE)
    "_",
#  else
    0,
#  endif
    sys_dl_open, sys_dl_close, sys_dl_sym, 0, 0 };
