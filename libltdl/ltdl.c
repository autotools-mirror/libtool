/* ltdl.c -- system independent dlopen wrapper
   Copyright (C) 1998 Thomas Tanner <tanner@gmx.de>
   This file is part of GNU Libtool.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free
Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#define _LTDL_COMPILE_

#if HAVE_STRING_H
#include <string.h>
#endif

#if HAVE_STRINGS_H
#include <strings.h>
#endif

#if HAVE_CTYPE_H
#include <ctype.h>
#endif

#if HAVE_MALLOC_H
#include <malloc.h>
#endif

#if HAVE_MEMORY_H
#include <memory.h>
#endif

#if HAVE_STDLIB_H
#include <stdlib.h>
#endif

#if HAVE_UNISTD_H
#include <unistd.h>
#endif

#if HAVE_STDIO_H
#include <stdio.h>
#endif

#include "ltdl.h"

typedef struct lt_dltype_t {
	struct lt_dltype_t *next;
	int (*mod_init) __P((void));
	int (*mod_exit) __P((void));
	int (*lib_open) __P((lt_dlhandle handle, const char *filename));
	int (*lib_close) __P((lt_dlhandle handle));
	lt_ptr_t (*find_sym) __P((lt_dlhandle handle, const char *symbol));
} lt_dltype_t, *lt_dltype;

#define LT_DLTYPE_TOP NULL

typedef	struct lt_dlhandle_t {
	struct lt_dlhandle_t *next;
	lt_dltype_t *type;	/* dlopening interface */
	char	*filename;	/* file name */
	char	*name;		/* module name */
	int	usage;		/* usage */
	lt_ptr_t handle;	/* system handle */
	lt_ptr_t system;	/* system specific data */
} lt_dlhandle_t;

#if ! HAVE_STRDUP

#undef strdup
#define strdup xstrdup

static char *
strdup(str)
	const char *str;
{
	char *tmp;

	if (!str)
		return str;
	tmp = malloc(strlen(str)+1);
	if (tmp)
		strcpy(tmp, str);
	return tmp;
}

#endif

#if ! HAVE_STRRCHR

# if HAVE_RINDEX

#  define strrchr rindex

# else

#  define strrchr xstrrchr

static const char*
strrchr(str, ch)
	const char *str;
	int ch;
{
	const char *p;

	for (p = str; p != '\0'; p++)
		/*NOWORK*/;

	while (*p != (char)ch && p >= str) 
		p--;

	return (*p == (char)ch) ? p : NULL;
}

# endif

#endif

#if HAVE_LIBDL

/* dynamic linking with dlopen/dlsym */

#if HAVE_DLFCN_H
# include <dlfcn.h>
#endif

#ifdef RTLD_LAZY	
#  define DLOPEN_MODE	RTLD_LAZY
#else
# ifdef DL_LAZY
#  define DLOPEN_MODE	DL_LAZY
# else
#  define DLOPEN_MODE	1
# endif
#endif

static int
dl_init ()       
{
	return 0;
}

static int
dl_exit ()       
{
	return 0;
}

static int
dl_open (handle, filename)
	lt_dlhandle handle;
	const char *filename;
{
	handle->handle = dlopen(filename, DLOPEN_MODE);
	return !(handle->handle);
}

static int
dl_close (handle)
	lt_dlhandle handle;
{
	return dlclose(handle->handle);
}

static lt_ptr_t
dl_sym (handle, symbol)
	lt_dlhandle handle;
	const char *symbol;
{
	return dlsym(handle->handle, symbol);
}

static
lt_dltype_t
dl = { LT_DLTYPE_TOP, dl_init, dl_exit,
       dl_open, dl_close, dl_sym };

#undef LT_DLTYPE_TOP
#define LT_DLTYPE_TOP &dl

#endif

#if HAVE_SHL_LOAD

/* dynamic linking with shl_load (HP-UX) */

#ifdef HAVE_DL_H
#include <dl.h>
#endif

static int
shl_init ()       
{
	return 0;
}

static int
shl_exit ()       
{
	return 0;
}

static int
shl_open (handle, filename)
	lt_dlhandle handle;
	const char *filename;
{
	/* Probably too much BIND_* flags */
	handle->handle = shl_load (filename, BIND_IMMEDIATE || BIND_FIRST ||
		BIND_TOGETHER || BIND_VERBOSE || DYNAMIC_PATH, 0L);
	return !(handle->handle);
}

static int
shl_close (handle)
	lt_dlhandle handle;
{
	shl_unload((shl_t) (handle->handle));
	return 0;
}

static lt_ptr_t
shl_sym (handle, symbol)
	lt_dlhandle handle;
	const char *symbol;
{
	int status, i;
	struct shl_symbol *sym;

	status = shl_getsymbols((shl_t) (handle->handle), TYPE_PROCEDURE,
			EXPORT_SYMBOLS, malloc, &sym);
	for (i = 0; i < status; i++)
		if (strcmp(symbol, sym[i].name) == 0)
			return sym[i].value;
	return 0;
}

static
lt_dltype_t
shl = { LT_DLTYPE_TOP, shl_init, shl_exit,
	shl_open, shl_close, shl_sym };

#undef LT_DLTYPE_TOP
#define LT_DLTYPE_TOP &shl

#endif

#if HAVE_DLD

/* dynamic linking with dld */

static int
dld_init ()       
{
	return 0;
}

static int
dld_exit ()       
{
	return 0;
}

static int
dld_open (handle, filename)
	lt_dlhandle handle;
	const char *filename;
{
	if (dld_link(filename))
		return 1;
	handle->handle = strdup(filename);
	return 0;
}

static int
dld_close (handle)
	lt_dlhandle handle;
{
	dld_unlink_by_file((char*)(handle->handle), 1);
	free(handle->filename);
	return 0;
}

static lt_ptr_t
dld_sym (handle, symbol)
	lt_dlhandle handle;
	const char *symbol;
{
	return dld_get_func(symbol);
}

static
lt_dltype_t
dld = { LT_DLTYPE_TOP, dld_init, dld_exit,
	dld_open, dld_close, dld_sym };

#undef LT_DLTYPE_TOP
#define LT_DLTYPE_TOP &dld

#endif

#ifdef _WIN32

/* dynamic linking for Win32 */

#include <windows.h> 

static int
wll_init ()       
{
	return 0;
}

static int
wll_exit ()       
{
	return 0;
}

static int
wll_open (handle, filename)
	lt_dlhandle handle;
	const char *filename;
{
	handle->handle = LoadLibrary(filename);
	return !(handle->handle);
}

static int
wll_close (handle)
	lt_dlhandle handle;
{
	FreeLibrary(handle->handle);
	return 0;
}

static lt_ptr_t
wll_sym (handle, symbol)
	lt_dlhandle handle;
	const char *symbol;
{
	return GetProcAddress(handle->handle, symbol);
}

static
lt_dltype_t
wll = { LT_DLTYPE_TOP, wll_init, wll_exit,
	wll_open, wll_close, wll_sym };

#undef LT_DLTYPE_TOP
#define LT_DLTYPE_TOP &wll

#endif

#if DEBUG
#if HAVE_DLPREOPEN

/* emulate dynamic linking using dld_preloaded_symbols */

struct dld_symlist
{
  char *name;
  lt_ptr_t address;
};

extern struct dld_symlist dld_preloaded_symbols[];

static int
dldpre_init ()       
{
	return 0;
}

static int
dldpre_exit ()       
{
	return 0;
}

static int
dldpre_open (handle, filename)
	lt_dlhandle handle;
	const char *filename;
{
	struct dld_symlist *s = dld_preloaded_symbols;

	while (s->name) {
		if (!s->address && !strcmp(s->name, filename))
			break;
		s++;
	}
	if (!s->name)
		return 1;
	handle->handle = s;
	return 0;
}

static int
dldpre_close (handle)
	lt_dlhandle handle;
{
	return 0;
}

static lt_ptr_t
dldpre_sym (handle, symbol)
	lt_dlhandle handle;
	const char *symbol;
{
	struct dld_symlist *s = (struct dld_symlist*)(handle->handle);

	if (!s)
		return 0;
	s++;
	while (s->address) {
		if (strcmp(s->name, symbol) == 0)
			return s->address;
		s++;
	}
	return 0;
}

static 
lt_dltype_t
dldpre = { LT_DLTYPE_TOP, dldpre_init, dldpre_exit,
	   dldpre_open, dldpre_close, dldpre_sym };

#undef LT_DLTYPE_TOP
#define LT_DLTYPE_TOP &dldpre

#endif
#endif

static lt_dlhandle handles;
static int initialized = 0;

static lt_dltype types = LT_DLTYPE_TOP;
#undef LT_DLTYPE_TOP

int
lt_dlinit ()       
{
	/* initialize libltdl */
	lt_dltype *type = &types;
	int typecount = 0;

	if (initialized) {	/* Initialize only at first call. */
		initialized++;
		return 0;
	}
	handles = 0;

	while (*type) {
		if ((*type)->mod_init())
			*type = (*type)->next; /* Remove it from the list */
		else {
			type = &(*type)->next; /* Keep it */
			typecount++;
		}
	}
	if (typecount == 0)
		return 1;
	initialized = 1;
	return 0;
}

int
lt_dlexit ()       
{
	/* shut down libltdl */
	lt_dltype type = types;
	int	error;
	
	if (!initialized)
		return 1;	/* already deinitialized */	
	if (initialized != 1) { /* shut down only at last call. */
		initialized--;
		return 0;
	}
	/* close all modules */
	error = 0;
	while (handles)
		if (lt_dlclose(handles))
			error = 1;
	initialized = 0;
	while (type) {
		if (type->mod_exit())
			error++;
		type = type->next;
	}
	return error;
}

static void
trim (dest, s)
	char *dest;
	const char *s;
{
	char *i = strrchr(s, '\'');
	int len = strlen(s);

	if (len > 3 && s[0] == '\'') {
		strncpy(dest, &s[1], (i - s) - 1);
		dest[len-3] = '\0';
	} else
		*dest = '\0';
}

static int
tryall_dlopen (handle, fullname)
	lt_dlhandle handle;
	const char *fullname;
{
	lt_dltype type = types;
	while (type) {
		if (type->lib_open(handle, fullname) == 0)
			break;
		type = type->next;
	}
	handle->type = type;
	return !type;
}

#undef	MAX_FILENAME
#define MAX_FILENAME 1024

static int
find_module (handle, search_path, dir, libdir, dlname, old_name)
	lt_dlhandle handle; 
	const char *search_path; 
	const char *dir; 
	const char *libdir;
	const char *dlname;
	const char *old_name;
{
	char	fullname[MAX_FILENAME]; /* FIXME: unchecked */
	
	/* search a module */
	if (*dlname) {
		/* try to open the installed module */
		strcpy(fullname, libdir);
		strcat(fullname, "/");
		strcat(fullname, dlname);
		if (tryall_dlopen(handle, fullname) == 0)
			return 0;
		/* try to open the not-installed module */
		strcpy(fullname, dir);
		strcat(fullname, ".libs/");
		strcat(fullname, dlname);
		if (tryall_dlopen(handle, fullname) == 0)
			return 0;
		strcpy(fullname, dir);
		strcat(fullname, dlname);
		if (tryall_dlopen(handle, fullname) == 0)
			return 0;
	}
	if (*old_name && tryall_dlopen(handle, old_name) == 0)
		return 0;  
	return 1;
}

#undef	READTEXT_MODE

#ifdef _WIN32
#define	READTEXT_MODE "rt"
#else
#define	READTEXT_MODE "r"
#endif

lt_dlhandle
lt_dlopen (filename)
	const char *filename;
{
	lt_dlhandle handle, cur;
	FILE	*file;
	char	dir[MAX_FILENAME]; /* FIXME: unchecked buffer */
	const char *basename, *ext, *search_path;
	
	/* check whether the module was already opened */
	cur = handles;
	while (cur && strcmp(cur->filename, filename))
		cur = cur->next;
	if (cur) {
		cur->usage++;
		return cur;
	}

	handle = (lt_dlhandle) malloc(sizeof(lt_dlhandle_t));
	if (!handle)
		return 0;
	basename = strrchr(filename, '/');
	if (basename)
		basename++;
	else
		basename = filename;
	strncpy(dir, filename, basename - filename);
	dir[basename - filename] = '\0';
	search_path = getenv("LTDL_LIBRARY_PATH"); /* get the search path */
	/* check whether we open a libtool module (.la extension) */
	ext = strrchr(basename, '.');
	if (ext && strcmp(ext, ".la") == 0) {
		char	tmp[MAX_FILENAME]; /* FIXME: unchecked */
		char	dlname[MAX_FILENAME], old_name[MAX_FILENAME];
		char	libdir[MAX_FILENAME], deps[MAX_FILENAME];
		int	i;

		dlname[0] = libdir[0] = deps[0] = old_name[0] = '\0';
	
		file = fopen(filename, READTEXT_MODE);
		if (!file) {
			free(handle);
			return 0;
		}
		while (!feof(file)) {
			if (!fgets(tmp, MAX_FILENAME, file))
				break;
			if (strncmp(tmp, "libdir=", 7) == 0)
				trim(libdir, &tmp[7]);
			else
			if (strncmp(tmp, "dependency_libs=", 16) == 0)
				trim(deps, &tmp[16]);
			else
			if (strncmp(tmp, "dlname=", 7) == 0)
				trim(dlname, &tmp[7]);
			else
			if (strncmp(tmp, "old_library=", 12) == 0)
				trim(old_name, &tmp[12]);
		}
		fclose(file);
		if (find_module(handle, search_path, 
			dir, libdir, dlname, old_name)) {
			free(handle);
			return 0;
		}
		handle->filename = strdup(filename);
		/* extract the module name from the file name */
		strcpy(tmp, basename);
		tmp[ext - basename] = '\0';
		/* canonicalize the modul name */		
		for (i = 0; i < ext - basename; i++)
			if (!isalnum(tmp[i]))
				tmp[i] = '_';
		handle->name = strdup(tmp);
	} else {
		/* not a libtool module */
		if (tryall_dlopen(handle, filename)) {
			free(handle);
			return 0;
		}
		handle->filename = strdup(filename);
		handle->name = 0;
	}
	handle->usage = 1;
	handle->next = handles;
	handles = handle;
	return handle;
}

int
lt_dlclose (handle)
	lt_dlhandle handle;
{
	lt_dlhandle cur, last;
	
	/* check whether the handle is valid */
	last = cur = handles;
	while (cur && handle != cur) {
		last = cur;
		cur = cur->next;
	}
	if (!cur)	
		return 1; /* invalid handle */
	handle->usage--;
	if (!handle->usage) {
		int	error;
	
		if (handle != handles)
			last->next = handle->next;
		else
			handles = handle->next;
		error = handle->type->lib_close(handle);
		free(handle->filename);
		if (handle->name)
			free(handle->name);
		free(handle);
		return error;
	}
	return 0;
}

lt_ptr_t
lt_dlsym (handle, symbol)
	lt_dlhandle handle;
	const char *symbol;
{
	char	sym[128]; /* FIXME: unchecked */
	lt_ptr_t address;

	if (handle->name) { /* this is a libtool module */
#ifdef NEED_USCORE
		/* prefix symbol with leading underscore */
		strcpy(sym, "_");
		strcat(sym, handle->name);
#else
		strcpy(sym, handle->name);
#endif
		strcat(sym, "_LTX_");
		strcat(sym, symbol);
		/* try "modulename_LTX_symbol" */
		address = handle->type->find_sym(handle, sym);
		if (address)
			return address;
	}
	/* otherwise try "symbol" */
#ifdef NEED_USCORE
	/* prefix symbol with leading underscore */
	strcpy(sym, "_");
	strcat(sym, symbol);
	return handle->type->find_sym(handle, sym);
#else
	return handle->type->find_sym(handle, symbol);
#endif
}
