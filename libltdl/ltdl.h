/* ltdl.h -- generic dlopen functions
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

/* Only include this header file once. */
#ifndef _LTDL_H_
#define _LTDL_H_ 1

/* __BEGIN_DECLS should be used at the beginning of your declarations,
   so that C++ compilers don't mangle their names.  Use __END_DECLS at
   the end of C declarations. */
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

/* __P is a macro used to wrap function prototypes, so that compilers
   that don't understand ANSI C prototypes still work, and ANSI C
   compilers can issue warnings about type mismatches. */
#undef __P
#undef lt_ptr_t
#if defined (__STDC__) || defined (_AIX) || (defined (__mips) && defined (_SYSTYPE_SVR4)) || defined(WIN32) || defined(__cplusplus)
# define __P(protos) protos
# define lt_ptr_t     void*
#else
# define __P(protos) ()
# define lt_ptr_t     char*
#endif

#ifdef _LTDL_COMPILE_
typedef	struct lt_dlhandle_t *lt_dlhandle;
#else
typedef	lt_ptr_t lt_dlhandle;
#endif

__BEGIN_DECLS
int		lt_dlinit __P((void));
int		lt_dlexit __P((void));
lt_dlhandle	lt_dlopen __P((const char *filename));
int		lt_dlclose __P((lt_dlhandle handle));
lt_ptr_t	lt_dlsym __P((lt_dlhandle handle, const char *name));
__END_DECLS

#endif /* !_LTDL_H_ */
