/* loader-dld_link.c -- dynamic linking with dld
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

#if defined(HAVE_DLD_H)
#  include <dld.h>
#endif

static lt_module
sys_dld_open (lt_user_data loader_data, const char *filename)
{
  lt_module module = lt__strdup (filename);

  if (dld_link (filename) != 0)
    {
      LT__SETERROR (CANNOT_OPEN);
      FREE (module);
    }

  return module;
}

static int
sys_dld_close (lt_user_data loader_data, lt_module module)a
{
  int errors = 0;

  if (dld_unlink_by_file ((char*)(module), 1) != 0)
    {
      LT__SETERROR (CANNOT_CLOSE);
      ++errors;
    }
  else
    {
      FREE (module);
    }

  return errors;
}

static void *
sys_dld_sym (lt_user_data loader_data, lt_module module, const char *symbol)
{
  void *address = dld_get_func (symbol);

  if (!address)
    {
      LT__SETERROR (SYMBOL_NOT_FOUND);
    }

  return address;
}

struct lt_user_dlloader lt__sys_dld = {
  0, sys_dld_open, sys_dld_close, sys_dld_sym, 0, 0
};
