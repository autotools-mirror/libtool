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

void testlib(char *lib, char *alt)
{
  lt_dlhandle handle;	
  int (*pfoo1)() = 0;
  int (*pfoo2)() = 0;
  int (*phello)() = 0;
  int *pnothing = 0;

  handle = lt_dlopen(lib);
  if (!handle)
	  handle = lt_dlopen(alt);
  if (!handle) {
    fprintf (stderr, "can't open library %s!\n", lib);
    return;
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
}

int
main (argc, argv)
     int argc;
     char **argv;
{

  printf ("Welcome to *modular* GNU Hell!\n");

  testlib(".libs/libfoo1.so", ".libs/libfoo1.a");

  testlib(".libs/libfoo2.so", ".libs/libfoo2.a");
  
  return 0;
}
