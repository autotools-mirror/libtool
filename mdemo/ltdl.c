/* ltdl.c -- dlopen functions
   Copyright (C) 1998 Thomas Tanner <tanner@gmx.de>
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

#include "ltdl.h"

#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif

#ifdef HAVE_DL_H
#include <dl.h>
#endif

lt_dlhandle	lt_dlopen(char *name)
{
	return dlopen(name, RTLD_LAZY);
}

void		lt_dlclose(lt_dlhandle handle)
{
	dlclose(handle);
}

void		*lt_dlsym(lt_dlhandle handle, char *name)
{
	return dlsym(handle, name);
}
