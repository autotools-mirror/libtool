/* main.c -- hello test program
   Copyright (C) 1996 Free Software Foundation, Inc.
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
#include "ltdl.h"
#include <stdio.h>
#include <string.h>

int testlib(char *lib)
{
  lt_dlhandle handle;	
  int (*pfoo1)() = 0;
  int (*pfoo2)() = 0;
  int (*phello)() = 0;
  int *pnothing = 0;

  handle = lt_dlopen(lib);
  if (!handle) {
    fprintf (stderr, "can't open library %s!\n", lib);
    return 1;
  }
  phello = lt_dlsym(handle, "hello");  
  pfoo1 = lt_dlsym(handle, "foo1");  
  pfoo2 = lt_dlsym(handle, "foo2");  
  pnothing = lt_dlsym(handle, "nothing");  

  if (phello)
    {
      int value = (*phello) ();
      
      printf ("hello returned: %i\n", value);
      if (value == HELLO_RET)
        printf("hello is ok!\n");
    }
  else
    fprintf (stderr, "did not find the `hello' function\n");

  /* Try assigning to the nothing variable. */
  if (pnothing)
    *pnothing = 1;
  else
    fprintf (stderr, "did not find the `nothing' variable\n");

  /* Just call the functions and check return values. */
  if (pfoo1)
    {
      if ((*pfoo1) () == FOO_RET)
        printf("foo1 is ok!\n");
    }
  else if (pfoo2)
    {
      if ((*pfoo2) () == FOO_RET)
        printf("foo2 is ok!\n");
    }
  else
    fprintf (stderr, "did not find the `foo' function\n");

  lt_dlclose(handle);
  return 0;
}

int
main (int argc, char **argv)
{
  int i;

  printf ("Welcome to *modular* GNU Hell!\n");

  if (argc < 2) {
    fprintf (stderr, "usage: %s libname [libname...]\n", argv[0]);
  }
  
  for (i = 1; i < argc; i++)
    if (testlib(argv[i]))
       return 1;
  return 0;
}
