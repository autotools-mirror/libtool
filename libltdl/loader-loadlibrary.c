/* loader-loadlibrary.c --  dynamic linking for Win32
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

#include <windows.h>

/* Forward declaration; required to implement handle search below. */
static lt_dlhandle handles;

static lt_module
sys_wll_open (lt_user_data loader_data, const char *filename)
{
  lt_dlhandle	cur;
  lt_module	module	   = 0;
  const char   *errormsg   = 0;
  char	       *searchname = 0;
  char	       *ext;
  char		self_name_buf[MAX_PATH];

  if (!filename)
    {
      /* Get the name of main module */
      *self_name_buf = 0;
      GetModuleFileName (NULL, self_name_buf, sizeof (self_name_buf));
      filename = ext = self_name_buf;
    }
  else
    {
      ext = strrchr (filename, '.');
    }

  if (ext)
    {
      /* FILENAME already has an extension. */
      searchname = lt__strdup (filename);
    }
  else
    {
      /* Append a `.' to stop Windows from adding an
	 implicit `.dll' extension. */
      searchname = MALLOC (char, 2+ LT_STRLEN (filename));
      if (searchname)
	sprintf (searchname, "%s.", filename);
    }
  if (!searchname)
    return 0;

#if defined(__CYGWIN__)
  {
    char wpath[MAX_PATH];
    cygwin_conv_to_full_win32_path(searchname, wpath);
    module = LoadLibrary(wpath);
  }
#else
  module = LoadLibrary (searchname);
#endif
  FREE (searchname);

  /* libltdl expects this function to fail if it is unable
     to physically load the library.  Sadly, LoadLibrary
     will search the loaded libraries for a match and return
     one of them if the path search load fails.

     We check whether LoadLibrary is returning a handle to
     an already loaded module, and simulate failure if we
     find one. */
  cur = handles;
  while (cur)
    {
      if (!cur->module)
	{
	  cur = 0;
	  break;
	}

      if (cur->module == module)
	{
	  break;
	}

      cur = cur->next;
  }

  if (cur || !module)
    {
      LT__SETERROR (CANNOT_OPEN);
      module = 0;
    }

  return module;
}

static int
sys_wll_close (lt_user_data loader_data, lt_module module)
{
  int	      errors   = 0;

  if (FreeLibrary(module) == 0)
    {
      LT__SETERROR (CANNOT_CLOSE);
      ++errors;
    }

  return errors;
}

static void *
sys_wll_sym (lt_user_data loader_data, lt_module module,const char *symbol)
{
  void *     address  = GetProcAddress (module, symbol);

  if (!address)
    {
      LT__SETERROR (SYMBOL_NOT_FOUND);
    }

  return address;
}

struct lt_user_dlloader lt__sys_wll = {
  0, sys_wll_open, sys_wll_close, sys_wll_sym, 0, 0
};
