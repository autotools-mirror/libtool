/* lt_error.c -- error propogation interface
   Copyright (C) 1999, 2000, 2001, 2004 Free Software Foundation, Inc.
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
License along with this library; if not, write to the Free
Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307  USA
*/

#include "lt_error.h"
#include "lt_mutex.h"
#include "lt__private.h"

static	const char    **user_error_strings	= 0;
static	int		errorcount		= LT_ERROR_MAX;

int
lt_dladderror (const char *diagnostic)
{
  int		errindex = 0;
  int		result	 = -1;
  const char  **temp     = (const char **) 0;

  assert (diagnostic);

  LT__MUTEX_LOCK ();

  errindex = errorcount - LT_ERROR_MAX;
  temp = REALLOC (const char *, user_error_strings, 1 + errindex);
  if (temp)
    {
      user_error_strings		= temp;
      user_error_strings[errindex]	= diagnostic;
      result				= errorcount++;
    }

  LT__MUTEX_UNLOCK ();

  return result;
}

int
lt_dlseterror (int errindex)
{
  int		errors	 = 0;

  LT__MUTEX_LOCK ();

  if (errindex >= errorcount || errindex < 0)
    {
      /* Ack!  Error setting the error message! */
      LT__MUTEX_SETERROR (INVALID_ERRORCODE);
      ++errors;
    }
  else if (errindex < LT_ERROR_MAX)
    {
      /* No error setting the error message! */
      LT__MUTEX_SETERRORSTR (lt__error_strings[errindex]);
    }
  else
    {
      /* No error setting the error message! */
      LT__MUTEX_SETERRORSTR (user_error_strings[errindex - LT_ERROR_MAX]);
    }

  LT__MUTEX_UNLOCK ();

  return errors;
}
