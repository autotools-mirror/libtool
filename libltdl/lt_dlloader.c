/* lt_dlloader.c -- dynamic library loader interface
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

#include "lt_dlloader.h"
#include "lt__private.h"

#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1

static void *	loader_cmp (const SList *node, const void *userdata);

/* A list of all the dlloaders we know about, each stored in the
   USERDATA field of an SList node:  */
static	SList    *loaders		= 0;

/* Return NULL, unless the loader in this NODE has a matching name,
   in which case we return the vtable from matching node so that its
   address is passed back out (for possible freeing) by slist_remove.  */
static void *
loader_cmp (const SList *node, const void *userdata)
{
  const lt_dlvtable *vtable = node->userdata;
  const char *	    name    = userdata;

  assert (vtable);

  return streq (vtable->name, name) ? (void *) vtable : 0;
}


/* Hook VTABLE into our global LOADERS list according to its own
   PRIORITY field value.  */
int
lt_dlloader_add (const lt_dlvtable *vtable)
{
  if ((vtable == 0)	/* diagnose null parameters */
      || (vtable->module_open == 0)
      || (vtable->module_close == 0)
      || (vtable->find_sym == 0))
    {
      LT__SETERROR (INVALID_LOADER);
      return RETURN_FAILURE;
    }

  switch (vtable->priority)
    {
    case LT_DLLOADER_PREPEND:
      loaders = slist_cons (slist_new (vtable), loaders);
      break;

    case LT_DLLOADER_APPEND:
      loaders = slist_concat (loaders, slist_new (vtable));
      break;

    default:
      LT__SETERROR (INVALID_LOADER);
      return RETURN_FAILURE;
      /*NOTREACHED*/
    }

  return RETURN_SUCCESS;
}


/* An iterator for the global loader list: if LOADER is NULL, then
   return the first element, otherwise the following element.  */
lt_dlloader
lt_dlloader_next (lt_dlloader loader)
{
  SList *node = (SList *) loader;
  return (lt_dlloader) (node ? node->next : loaders);
}


const lt_dlvtable *
lt_dlloader_get	(lt_dlloader loader)
{
  return ((SList *) loader)->userdata;
}

/* Return the contents of the first item in the global loader list
   with a matching NAME after removing it from that list.  If there
   was no match, return NULL; if there is an error, return NULL and
   set an error for lt_dlerror; in either case the loader list is
   not changed.  */
lt_dlvtable *
lt_dlloader_remove (const char *name)
{
  const lt_dlvtable *	vtable	= lt_dlloader_find (name);
  lt__handle *		handle	= 0;
  int			errors	= 0;

  if (!vtable)
    {
      LT__SETERROR (INVALID_LOADER);
      return 0;
    }

  /* Fail if there are any open modules which use this loader.  */
  for  (handle = 0; handle; handle = handle->next)
    {
      if (handle->vtable == vtable)
	{
	  LT__SETERROR (REMOVE_LOADER);
	  return 0;
	}
    }

  /* Call the loader finalisation function.  */
  if (vtable && vtable->dlloader_exit)
    {
      if (vtable->dlloader_exit (vtable->dlloader_data) != 0)
	{
	  /* If there is an exit function, and it returns non-zero
	     then it must set an error, and we will not remove it
	     from the list.  */
	  return 0;
	}
    }

  /* If we got this far, remove the loader from our global list.  */
  return slist_remove (&loaders, name, loader_cmp);
}


const lt_dlvtable *
lt_dlloader_find (const char *name)
{
  return slist_find (loaders, name, loader_cmp);
}
