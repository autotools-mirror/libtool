/* ltdls.c -- static dlopen functions
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

#ifdef HAVE_STRING_H
#include <string.h>
#endif

struct dld_symlist
{
  char *name;
  void *address;
};

extern struct dld_symlist dld_preloaded_symbols[];

lt_dlhandle	lt_dlopen(char *name)
{
	struct dld_symlist *s;

	s = dld_preloaded_symbols;
	while (s->name) {
		if (!s->address && !strcmp(s->name, name))
			break;
		s++;
	}
	if (!s->name)
		return NULL;
	return strdup(name);
}

void		lt_dlclose(lt_dlhandle handle)
{
	free(handle);
}

void		*lt_dlsym(lt_dlhandle handle, char *name)
{
	struct dld_symlist *s;
	char	*p;

	s = dld_preloaded_symbols;
	while (s->name) {
		if (!s->address && !strcmp(s->name, handle))
			break;
		s++;
	}
	if (!s->name)
		return NULL;
	s++;
	while (s->address) {
		p = strstr(s->name, "___");
		if (p && !strcmp(&p[3], name))
			return s->address;
		s++;
	}
	return NULL;
}

