/* dlmain.c -- hello test program that uses simulated dynamic linking
   Copyright (C) 1996-1999 Free Software Foundation, Inc.
   This file is part of GNU Libtool.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
USA. */

#include "foo.h"
#include <stdio.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

struct dld_symlist
{
  char *name;
  void *address;
};

extern struct dld_symlist dld_preloaded_symbols[];

#ifdef __CYGWIN32__
int
win32_force_data_import_address __P((void))
{
  struct dld_symlist *s;
  
  s = dld_preloaded_symbols;
  while (s->name)
    {
      if (!strcmp ("nothing", s->name))
        s->address = &nothing;
      s++;
    }

  return 0;
}
#endif
      

int
main (argc, argv)
     int argc;
     char **argv;
{
  struct dld_symlist *s;
  int (*pfoo)() = 0;
  int (*phello)() = 0;
  int *pnothing = 0;

  printf ("Welcome to *modular* GNU Hell!\n");

#ifdef __CYGWIN32__
  /* runtime table initialisation */
  (void) win32_force_data_import_address();
#endif

  /* Look up the symbols we require for this demonstration. */
  s = dld_preloaded_symbols;
  while (s->name)
    {
      if (s->address) {
        char *name = s->name;
        printf ("found symbol: %s\n", name);
        if (!strcmp ("hello", name))
 	  phello = s->address;
        else if (!strcmp ("foo", name))
  	  pfoo = s->address;
        else if (!strcmp ("nothing", name))
  	  pnothing = s->address;
      } else 
        printf ("found file: %s\n", s->name);
      s ++;
    }

  /* Try assigning to the nothing variable. */
  if (pnothing)
    *pnothing = 1;
  else
    fprintf (stderr, "did not find the `nothing' variable\n");

  /* Just call the functions and check return values. */
  if (pfoo)
    {
      if ((*pfoo) () != FOO_RET)
	return 1;
    }
  else
    fprintf (stderr, "did not find the `foo' function\n");

  if (phello)
    {
      if ((*phello) () != HELLO_RET)
	return 3;
    }
  else
    fprintf (stderr, "did not find the `hello' function\n");

  return 0;
}
