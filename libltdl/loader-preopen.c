/* loader-preopen.c -- emulate dynamic linking using preloaded_symbols
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


typedef struct lt_dlsymlists_t
{
  struct lt_dlsymlists_t       *next;
  const lt_dlsymlist	       *syms;
} lt_dlsymlists_t;

static	lt_dlsymlists_t	       *preloaded_symbols		= 0;
static const	lt_dlsymlist   *default_preloaded_symbols	= 0;


int
lt__presym_init (lt_user_data loader_data)
{
  int errors = 0;

  LT__MUTEX_LOCK ();

  preloaded_symbols = 0;
  if (default_preloaded_symbols)
    {
      errors = lt_dlpreload (default_preloaded_symbols);
    }

  LT__MUTEX_UNLOCK ();

  return errors;
}

static int
presym_free_symlists (void)
{
  lt_dlsymlists_t *lists;

  LT__MUTEX_LOCK ();

  lists = preloaded_symbols;
  while (lists)
    {
      lt_dlsymlists_t	*tmp = lists;

      lists = lists->next;
      FREE (tmp);
    }
  preloaded_symbols = 0;

  LT__MUTEX_UNLOCK ();

  return 0;
}

int
lt__presym_add_symlist (const lt_dlsymlist *preloaded)
{
  lt_dlsymlists_t *tmp;
  lt_dlsymlists_t *lists;
  int		   errors   = 0;

  LT__MUTEX_LOCK ();

  lists = preloaded_symbols;
  while (lists)
    {
      if (lists->syms == preloaded)
	{
	  goto done;
	}
      lists = lists->next;
    }

  tmp = MALLOC (lt_dlsymlists_t, 1);
  if (tmp)
    {
      memset (tmp, 0, sizeof(lt_dlsymlists_t));
      tmp->syms = preloaded;
      tmp->next = preloaded_symbols;
      preloaded_symbols = tmp;
    }
  else
    {
      ++errors;
    }

 done:
  LT__MUTEX_UNLOCK ();
  return errors;
}

static lt_module
presym_open (lt_user_data loader_data, const char *filename)
{
  lt_dlsymlists_t *lists;
  lt_module	   module = (lt_module) 0;

  LT__MUTEX_LOCK ();
  lists = preloaded_symbols;

  if (!lists)
    {
      LT__MUTEX_SETERROR (NO_SYMBOLS);
      goto done;
    }

  /* Can't use NULL as the reflective symbol header, as NULL is
     used to mark the end of the entire symbol list.  Self-dlpreopened
     symbols follow this magic number, chosen to be an unlikely
     clash with a real module name.  */
  if (!filename)
    {
      filename = "@PROGRAM@";
    }

  while (lists)
    {
      const lt_dlsymlist *syms = lists->syms;

      while (syms->name)
	{
	  if (!syms->address && strcmp(syms->name, filename) == 0)
	    {
	      module = (lt_module) syms;
	      goto done;
	    }
	  ++syms;
	}

      lists = lists->next;
    }

  LT__MUTEX_SETERROR (FILE_NOT_FOUND);

 done:
  LT__MUTEX_UNLOCK ();
  return module;
}

static int
presym_close (lt_user_data loader_data, lt_module module)
{
  /* Just to silence gcc -Wall */
  module = 0;
  return 0;
}

static void *
presym_sym (lt_user_data loader_data, lt_module module, const char *symbol)
{
  lt_dlsymlist *syms = (lt_dlsymlist*) module;

  ++syms;
  while (syms->address)
    {
      if (strcmp(syms->name, symbol) == 0)
	{
	  return syms->address;
	}

    ++syms;
  }

  LT__MUTEX_SETERROR (SYMBOL_NOT_FOUND);

  return 0;
}

static int
presym_exit (lt_user_data loader_data)
{
  presym_free_symlists ();
  return 0;
}

struct lt_user_dlloader lt__presym = {
  0, presym_open, presym_close, presym_sym, presym_exit, 0
};


int
lt_dlpreload (const lt_dlsymlist *preloaded)
{
  int errors = 0;

  if (preloaded)
    {
      errors = lt__presym_add_symlist (preloaded);
    }
  else
    {
      presym_free_symlists();

      LT__MUTEX_LOCK ();
      if (default_preloaded_symbols)
	{
	  errors = lt_dlpreload (default_preloaded_symbols);
	}
      LT__MUTEX_UNLOCK ();
    }

  return errors;
}

int
lt_dlpreload_default (const lt_dlsymlist *preloaded)
{
  LT__MUTEX_LOCK ();
  default_preloaded_symbols = preloaded;
  LT__MUTEX_UNLOCK ();
  return 0;
}
