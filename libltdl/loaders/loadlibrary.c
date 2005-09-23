/* loader-loadlibrary.c --  dynamic linking for Win32
   Copyright (C) 1998, 1999, 2000, 2004, 2005 Free Software Foundation, Inc.
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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301  USA

*/

#include "lt__private.h"
#include "lt_dlloader.h"

#if defined(__CYGWIN__)
# include <sys/cygwin.h>
#endif

/* Use the preprocessor to rename non-static symbols to avoid namespace
   collisions when the loader code is statically linked into libltdl.
   Use the "<module_name>_LTX_" prefix so that the symbol addresses can
   be fetched from the preloaded symbol list by lt_dlsym():  */
#define get_vtable	loadlibrary_LTX_get_vtable

LT_SCOPE lt_dlvtable *get_vtable (lt_user_data loader_data);


/* Boilerplate code to set up the vtable for hooking this loader into
   libltdl's loader list:  */
static lt_module vm_open  (lt_user_data loader_data, const char *filename);
static int	 vm_close (lt_user_data loader_data, lt_module module);
static void *	 vm_sym   (lt_user_data loader_data, lt_module module,
			  const char *symbolname);

/* Return the vtable for this loader, only the name and sym_prefix
   attributes (plus the virtual function implementations, obviously)
   change between loaders.  */
lt_dlvtable *
get_vtable (lt_user_data loader_data)
{
  static lt_dlvtable *vtable = 0;

  if (!vtable)
    {
      vtable = lt__zalloc (sizeof *vtable);
    }

  if (vtable && !vtable->name)
    {
      vtable->name		= "lt_loadlibrary";
      vtable->module_open	= vm_open;
      vtable->module_close	= vm_close;
      vtable->find_sym		= vm_sym;
      vtable->dlloader_data	= loader_data;
      vtable->priority		= LT_DLLOADER_APPEND;
    }

  if (vtable && (vtable->dlloader_data != loader_data))
    {
      LT__SETERROR (INIT_LOADER);
      return 0;
    }

  return vtable;
}



/* --- IMPLEMENTATION --- */


#include <windows.h>

/* A function called through the vtable to open a module with this
   loader.  Returns an opaque representation of the newly opened
   module for processing with this loader's other vtable functions.  */
static lt_module
vm_open (lt_user_data loader_data, const char *filename)
{
  lt_module	module	   = 0;
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

  {
    /* Silence dialog from LoadLibrary on some failures.
       No way to get the error mode, but to set it,
       so set it twice to preserve any previous flags. */
    UINT errormode = SetErrorMode(SEM_FAILCRITICALERRORS);
    SetErrorMode(errormode | SEM_FAILCRITICALERRORS);

#if defined(__CYGWIN__)
    {
      char wpath[MAX_PATH];
      cygwin_conv_to_full_win32_path (searchname, wpath);
      module = LoadLibrary (wpath);
    }
#else
    module = LoadLibrary (searchname);
#endif

    /* Restore the error mode. */
    SetErrorMode(errormode);
  }
  FREE (searchname);

  /* libltdl expects this function to fail if it is unable
     to physically load the library.  Sadly, LoadLibrary
     will search the loaded libraries for a match and return
     one of them if the path search load fails.

     We check whether LoadLibrary is returning a handle to
     an already loaded module, and simulate failure if we
     find one. */
  {
    lt__handle *        cur        = 0;

    while ((cur = (lt__handle *) lt_dlhandle_next ((lt_dlhandle) cur)))
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
      }
    
    if (cur || !module)
      {
        LT__SETERROR (CANNOT_OPEN);
        module = 0;
      }
  }

  return module;
}


/* A function called through the vtable when a particular module
   should be unloaded.  */
static int
vm_close (lt_user_data loader_data, lt_module module)
{
  int errors = 0;

  if (FreeLibrary(module) == 0)
    {
      LT__SETERROR (CANNOT_CLOSE);
      ++errors;
    }

  return errors;
}


/* A function called through the vtable to get the address of
   a symbol loaded from a particular module.  */
static void *
vm_sym (lt_user_data loader_data, lt_module module, const char *name)
{
  void *address = GetProcAddress (module, name);

  if (!address)
    {
      LT__SETERROR (SYMBOL_NOT_FOUND);
    }

  return address;
}
