/* lt_mutex.c -- mutex locking implementation
   Copyright (C) 2001, 2004 Free Software Foundation, Inc.
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

#include "lt_mutex.h"
#include "lt_error.h"
#include "lt__private.h"

/* The mutex functions stored here are global, and are necessarily the
   same for all threads that wish to share access to libltdl.  */
lt_dlmutex_lock	    *lt__mutex_lock_func     = 0;
lt_dlmutex_unlock   *lt__mutex_unlock_func   = 0;
lt_dlmutex_seterror *lt__mutex_seterror_func = 0;
lt_dlmutex_geterror *lt__mutex_geterror_func = 0;
const char	    *lt__last_error	      = 0;


/* Either set or reset the mutex functions.  Either all the arguments must
   be valid functions, or else all can be NULL to turn off locking entirely.
   The registered functions should be manipulating a static global lock
   from the lock() and unlock() callbacks, which needs to be reentrant.  */
int
lt_dlmutex_register (lt_dlmutex_lock *lock, lt_dlmutex_unlock *unlock,
    lt_dlmutex_seterror *seterror, lt_dlmutex_geterror *geterror)
{
  lt_dlmutex_unlock *old_unlock = unlock;
  int		     errors	= 0;

  /* Lock using the old lock() callback, if any.  */
  LT__MUTEX_LOCK ();

  if ((lock && unlock && seterror && geterror)
      || !(lock || unlock || seterror || geterror))
    {
      lt__mutex_lock_func     = lock;
      lt__mutex_unlock_func   = unlock;
      lt__mutex_geterror_func = geterror;
    }
  else
    {
      LT__MUTEX_SETERROR (INVALID_MUTEX_ARGS);
      ++errors;
    }

  /* Use the old unlock() callback we saved earlier, if any.  Otherwise
     record any errors using internal storage.  */
  if (old_unlock)
    (*old_unlock) ();

  /* Return the number of errors encountered during the execution of
     this function.  */
  return errors;
}
