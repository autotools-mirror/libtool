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

/* A generalised list.  This is deliberately transparent so that you
   can make the NEXT field of all your chained data structures first,
   and then cast them to `(SList *)' so that they can be manipulated
   by this API.

   Alternatively, you can generate raw SList elements using slist_new(),
   and put the element data in the USERDATA field.  Either way you
   get to manage the memory involved by yourself.
*/

#if !defined(SLIST_H)
#define SLIST_H 1

#include <libltdl/lt_system.h>


LT_BEGIN_C_DECLS

typedef struct slist {
  struct slist *next;		/* chain forward pointer*/
  const void *	userdata;	/* incase you want to use raw `SList's */
} SList;

typedef void *	SListCompare	(const SList *node, const void *userdata);
typedef int	SListCallback	(const SList *node, const *userdata);

LT_SCOPE SList *slist_new	(const void *userdata);
LT_SCOPE SList *slist_delete	(SList *head, void (*delete) (void *data));
LT_SCOPE void *	slist_remove	(SList **phead, const void *match,
				 SListCompare *find);
LT_SCOPE SList *slist_concat	(SList *head, SList *tail);
LT_SCOPE SList *slist_cons	(SList *head, SList *tail);
LT_SCOPE SList *slist_tail	(SList *head);
LT_SCOPE SList *slist_nth	(SList *head, size_t n);
LT_SCOPE void *	slist_find	(SList *head, const void *match,
				 SListCompare *find);
LT_SCOPE size_t slist_length	(SList *head);
LT_SCOPE SList *slist_reverse	(SList *head);
LT_SCOPE int	slist_foreach   (SList *head, SListCallback *foreach,
				 const void *userdata);

LT_END_C_DECLS

#endif /*!defined(SLIST_H)*/
