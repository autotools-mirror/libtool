/* foo.h -- interface to the libfoo library
   Copyright (C) 1996 Free Software Foundation, Inc.
   This file is part of GNU Libtool.
   Gordon Matzigkeit <gord@gnu.ai.mit.edu>, 1996

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
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* Only include this header file once. */
#ifndef _FOO_H_
#define _FOO_H_ 1

/* __BEGIN_DECLS should be used at the beginning of your C declarations,
   so that C++ compilers don't mangle their names.  __END_DECLS is used
   at the end of C declarations. */
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

/* __P is a macro used to wrap function prototypes, so that compilers that
   don't understand ANSI C prototypes still work, and ANSI C compilers can
   issue warnings about type mismatches. */
#undef __P
#if defined (__STDC__) || defined (_AIX) || (defined (__mips) && defined (_SYSTYPE_SVR4)) || defined(WIN32) || defined(__cplusplus)
# define __P(protos) protos
#else
# define __P(protos) ()
#endif

/* Silly constants that the functions return. */
#define HELLO_RET 0xe110
#define FOO_RET 0xf00

/* Function declarations.  Note the wonderful use of the above macros. */
__BEGIN_DECLS
int foo __P((void));
int hello __P((void));
__END_DECLS

#endif /* !_FOO_H_ */
