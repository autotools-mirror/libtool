/* slist.h -- generalised singly linked lists
   Copyright (C) 2000, 2004 Free Software Foundation, Inc.
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

#include <assert.h>

#include "slist.h"


SList *
slist_new (const void *userdata)
{
  SList *node = malloc (sizeof *node);

  node->next	 = 0;
  node->userdata = userdata;

  return node;
}

SList *
slist_delete (SList *head, void (*delete) (void *data))
{
  assert (delete);

  while (head)
    {
      SList *next = head->next;
      (*delete) (head);
      head = next;
    }

  return 0;
}

/* Call Find repeatedly with MATCH and each element of *PHEAD, until
   FIND returns non-NULL, or the list is exhausted.  If a match is found
   the matching element is removed from *PHEAD, and the value returned
   by the matching call to FIND is returned.

  To avoid memory leaks, unless you already have the address of the
  stale element, you should probably return that from FIND if it makes
  a successful match.  */
void *
slist_remove (SList **phead, const void *match, SListCompare *find)
{
  SList *stale = 0;
  void *result = 0;

  assert (find);

  if (!phead || !*phead)
    return 0;

  /* Does the head of the passed list match? */
  result = (*find) (*phead, match);
  if (result)
    {
      stale = *phead;
      *phead = stale->next;
    }
  /* what about the rest of the elements? */
  else
    {
      SList *head;
      for (head = *phead; head->next; head = head->next)
	{
	  result = (*find) (head->next, match);
	  if (result)
	    {
	      stale		= head->next;
	      head->next	= stale->next;
	    }
	}
    }

  return result;
}

SList *
slist_concat (SList *head, SList *tail)
{
  if (!head)
    {
      return tail;
    }

  while (head->next)
    head = head->next;

  head->next = tail;

  return head;
}

SList *
slist_cons (SList *head, SList *tail)
{
  if (!head)
    {
      return tail;
    }

  head->next = tail;
  return head;
}

SList *
slist_tail (SList *head)
{
  return head ? head->next : 0;
}

SList *
slist_nth (SList *head, size_t n)
{
  for (;n > 1 && head; n--)
    head = head->next;

  return head;
}

/* Call FIND repeatedly with SEARCH and each element of HEAD, until
   FIND returns non-NULL, or the list is exhausted.  If a match is found
   the value returned by the matching call to FIND is returned. */
void *
slist_find (SList *head, const void *match, SListCompare *find)
{
  void *result = 0;

  assert (find);

  for (; head; head = head->next)
    {
      result = (*find) (head, match);
      if (result)
	break;
    }

  return result;
}

size_t
slist_length (SList *head)
{
  size_t n;

  for (n = 0; head; ++n)
    head = head->next;

  return n;
}

SList *
slist_reverse (SList *head)
{
  SList *result = 0;
  SList *next;

  while (head)
    {
      next		= head->next;
      head->next	= result;
      result		= head;
      head 		= next;
    }

  return result;
}

int
slist_foreach (SList *head, SListCallback *foreach, const void *userdata)
{
  assert (foreach);

  for (; head; head = head->next)
    if ((*foreach) (head, userdata) < 0)
      return -1;

  return 0;
}
