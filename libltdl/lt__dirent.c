/* lt__dirent.c -- internal directory entry scanning interface
   Copyright (C) 2001, 2004 Free Software Foundation, Inc.
   Originally by Bob Friesenhahn <bfriesen@simple.dallas.tx.us>

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
#include <stddef.h>

#include "lt__dirent.h"

#if __WINDOWS__

void
closedir (DIR *entry)
{
  assert (entry != (DIR *) NULL);
  FindClose (entry->hSearch);
  free ((void *) entry);
}


DIR *
opendir (const char *path)
{
  char file_specification[LT_FILENAME_MAX];
  DIR *entry;

  assert (path != (char *) 0);
  (void) strncpy (file_specification, path, LT_FILENAME_MAX-1);
  (void) strcat (file_specification, "\\");
  entry = (DIR *) malloc (sizeof(DIR));
  if (entry != (DIR *) 0)
    {
      entry->firsttime = TRUE;
      entry->hSearch = FindFirstFile (file_specification,
				      &entry->Win32FindData);

      if (entry->hSearch == INVALID_HANDLE_VALUE)
	{
	  (void) strcat (file_specification, "\\*.*");
	  entry->hSearch = FindFirstFile (file_specification,
					  &entry->Win32FindData);
	  if (entry->hSearch == INVALID_HANDLE_VALUE)
	    {
	      entry = (free (entry), (DIR *) 0);
	    }
	}
    }

  return entry;
}


struct dirent *
readdir (DIR *entry)
{
  int status;

  if (entry == (DIR *) 0)
    return (struct dirent *) 0;

  if (!entry->firsttime)
    {
      status = FindNextFile (entry->hSearch, &entry->Win32FindData);
      if (status == 0)
        return (struct dirent *) 0;
    }

  entry->firsttime = FALSE;
  (void) strncpy (entry->file_info.d_name, entry->Win32FindData.cFileName,
		  LT_FILENAME_MAX - 1);
  entry->file_info.d_namlen = strlen (entry->file_info.d_name);

  return &entry->file_info;
}

#endif /*__WINDOWS__*/
