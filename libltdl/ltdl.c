/* ltdl.c -- system independent dlopen wrapper
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

#ifdef LT_RENAME

/* emulate dynamic linking using dld_preloaded_symbols */

struct dld_symlist
{
  char *name;
  void *address;
};

extern struct dld_symlist dld_preloaded_symbols[];

static void
sys_dlinit (void)
{
}

static lt_dlhandle
sys_dlopen (char *filename)
{
	struct dld_symlist *s = dld_preloaded_symbols;

	while (s->name) {
		if (!s->address && !strcmp(s->name, filename))
			break;
		s++;
	}
	if (!s->name)
		return 0;
	return (void*)s;
}

static void
sys_dlclose (lt_dlhandle handle)
{
}

static void *
sys_dlsym (lt_dlhandle handle, char *symbol)
{
	struct dld_symlist *s = (struct dld_symlist*)handle;

	if (!s)
		return 0;
	s++;
	while (s->address) {
		if (!strncmp(s->name, "ltexp_", 6)) {
			char	*p = strstr(s->name, "___");
			if (p && !strcmp(&p[3], symbol))
				return s->address;
		}
		s++;
	}
	return 0;
}

#else
#ifdef HAVE_LIBDL

/* dynamic linking with dlopen/dlsym */

#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif

#ifdef RTLD_LAZY	/* Solaris 2. */
#  define DLOPEN_MODE	RTLD_LAZY
#else
#ifdef DL_LAZY
#  define DLOPEN_MODE	DL_LAZY
#else
#  define DLOPEN_MODE	1	/* Thats what it says in the man page. */
#endif
#endif

static void
sys_dlinit (void)
{
}

static lt_dlhandle
sys_dlopen (char *filename)
{
	return dlopen(filename, DLOPEN_MODE);
}

static void
sys_dlclose (lt_dlhandle handle)
{
	dlclose(handle);
}

static void *
sys_dlsym (lt_dlhandle handle, char *symbol)
{
#ifdef __OpenBSD__
	char	sym[128];
	
	strcpy(sym, "_");
	strcat(sym, symbol);	/* prefix symbol with leading underscore */
	return dlsym(handle, sym);
#else
	return dlsym(handle, symbol);
#endif
}

#else
#ifdef HAVE_SHL_LOAD

/* dynamic linking with shl_load (HP-UX) */

#ifdef HAVE_DL_H
#include <dl.h>
#endif

static void
sys_dlinit (void)
{
}

static lt_dlhandle
sys_dlopen (char *filename)
{
	/* Probably too much BIND_* flags */
	return shl_load (filename, BIND_IMMEDIATE || BIND_FIRST ||
		BIND_TOGETHER || BIND_VERBOSE || DYNAMIC_PATH, 0L);
}

static void
sys_dlclose (lt_dlhandle handle)
{
	shl_unload((shl_t) handle);
}

static void *
sys_dlsym (lt_dlhandle handle, char *symbol)
{
	int status, i;
	struct shl_symbol *sym;

	status = shl_getsymbols((shl_t) handle, TYPE_PROCEDURE,
			EXPORT_SYMBOLS, malloc, &sym);
	for (i = 0; i < status; i++)
		if (strcmp(symbol, sym[i].name) == 0)
			return sym[i].value;
	return 0;
}

#else
#ifdef HAVE_DLD

/* dynamic linking with dld */

static void
sys_dlinit (void)
{
}

static lt_dlhandle
sys_dlopen (char *filename)
{
	if (dld_link (filename))
		return 0;
	return filename;
}

static void
sys_dlclose (lt_dlhandle handle)
{
	dld_unlink_by_file ((char*)handle, 1);
}

static void *
sys_dlsym (lt_dlhandle handle, char *symbol)
{
	return dld_get_func (symbol);
}

#else
#ifdef _WIN32

/* dynamic linking for Win32 */

#include <windows.h> 

static void
sys_dlinit (void)
{
}

static lt_dlhandle
sys_dlopen (char *filename)
{
	return LoadLibrary(filename);
}

static void
sys_dlclose (lt_dlhandle handle)
{
	FreeLibrary(handle);
}

static void *
sys_dlsym (lt_dlhandle handle, char *symbol)
{
	return GetProcAddress(handle, symbol);
}

#else 

/* no dynamic linking available */

static void
sys_dlinit (void)
{
}

static lt_dlhandle
sys_dlopen (char *filename)
{
	return 0;
}

static void
sys_dlclose (lt_dlhandle handle)
{
}

static void *
sys_dlsym (lt_dlhandle handle, char *symbol)
{
	return 0;
}

#endif
#endif
#endif
#endif
#endif

void
lt_dlinit (void)
{
	sys_dlinit();
}

lt_dlhandle
lt_dlopen (char *filename)
{
	return sys_dlopen(filename);
}


void
lt_dlclose (lt_dlhandle handle)
{
	sys_dlclose(handle);
}

void *
lt_dlsym (lt_dlhandle handle, char *symbol)
{
	return sys_dlsym(handle, symbol);
}
