/* loader-load_add_on.c --  dynamic linking for BeOS
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

#include <kernel/image.h>

static lt_module
sys_bedl_open (lt_user_data loader_data, const char *filename)
{
  image_id image = 0;

  if (filename)
    {
      image = load_add_on (filename);
    }
  else
    {
      image_info info;
      int32 cookie = 0;
      if (get_next_image_info (0, &cookie, &info) == B_OK)
	image = load_add_on (info.name);
    }

  if (image <= 0)
    {
      LT__MUTEX_SETERROR (CANNOT_OPEN);
      image = 0;
    }

  return (lt_module) image;
}

static int
sys_bedl_close (lt_user_data loader_data, lt_module module)
{
  int errors = 0;

  if (unload_add_on ((image_id) module) != B_OK)
    {
      LT__MUTEX_SETERROR (CANNOT_CLOSE);
      ++errors;
    }

  return errors;
}

static void *
sys_bedl_sym (lt_user_data loader_data, lt_module module, const char *symbol)
{
  void *address = 0;
  image_id image = (image_id) module;

  if (get_image_symbol (image, symbol, B_SYMBOL_TYPE_ANY, address) != B_OK)
    {
      LT__MUTEX_SETERROR (SYMBOL_NOT_FOUND);
      address = 0;
    }

  return address;
}

struct lt_user_dlloader lt__sys_bedl = {
  0, sys_bedl_open, sys_bedl_close, sys_bedl_sym, 0, 0
};
