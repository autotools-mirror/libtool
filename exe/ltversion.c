
/*
 *  $Id$
 *
 *  This module implements the default usage procedure for
 *  Automated Options.  It may be overridden, of course.
 */

/*
 *  Automated Options copyright 1992-2000 Bruce Korb
 *
 *  Automated Options is free software.
 *  You may redistribute it and/or modify it under the terms of the
 *  GNU General Public License, as published by the Free Software
 *  Foundation; either version 2, or (at your option) any later version.
 *
 *  Automated Options is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Automated Options.  See the file "COPYING".  If not,
 *  write to:  The Free Software Foundation, Inc.,
 *             59 Temple Place - Suite 330,
 *             Boston,  MA  02111-1307, USA.
 *
 * As a special exception, Bruce Korb gives permission for additional
 * uses of the text contained in his release of AutoOpts.
 *
 * The exception is that, if you link the AutoOpts library with other
 * files to produce an executable, this does not by itself cause the
 * resulting executable to be covered by the GNU General Public License.
 * Your use of that executable is in no way restricted on account of
 * linking the AutoOpts library code into it.
 *
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 *
 * This exception applies only to the code released by Bruce Korb under
 * the name AutoOpts.  If you copy code from other sources under the
 * General Public License into a copy of AutoOpts, as the General Public
 * License permits, the exception does not apply to the code that you add
 * in this way.  To avoid misleading anyone as to the status of such
 * modified files, you must delete this exception notice from them.
 *
 * If you write modifications of your own for AutoOpts, it is your choice
 * whether to permit this exception to apply to your modifications.
 * If you do not wish that, delete this exception notice.
 */

#include <stdio.h>
#include <stdlib.h>

#include "options.h"
#include "ltopts.h"

tSCC zAO[] =
    "Automated Options version %s, copyright (c) 1999-2001 Bruce Korb\n";

tSCC zBadArg[] =
"ERROR: version option argument '%c' invalid.  Use:\n\
\t'v' - version only\n\
\t'c' - version and copyright\n\
\t'n' - version and copyright notice\n";


    void
doVersion( pOpts, pOD )
    tOptions*  pOpts;
    tOptDesc*  pOD;
{
    char swCh;

    if (pOD->pzLastArg == (char*)NULL)
         swCh = 'v';
    else swCh = pOD->pzLastArg[0];

    printf( "%s: (GNU %s) %s%s\n", pOpts->pzProgName, pz_package, pz_vers,
            pz_timestamp );

    switch (swCh) {
    case '\0':
    case 'v':
    case 'V':
        break;

    case 'c':
    case 'C':
        if (pOpts->pzCopyright != (char*)NULL) {
            fputs( pOpts->pzCopyright, stdout );
            fputc( '\n', stdout );
        }
        printf( zAO, optionVersion() );
        break;

    case 'n':
    case 'N':
        if (pOpts->pzCopyright != (char*)NULL) {
            fputs( pOpts->pzCopyright, stdout );
            fputc( '\n', stdout );
            fputc( '\n', stdout );
        }

        if (pOpts->pzCopyNotice != (char*)NULL) {
            fputs( pOpts->pzCopyNotice, stdout );
            fputc( '\n', stdout );
        }

        printf( zAO, optionVersion() );
        break;

    default:
        fprintf( stderr, zBadArg, swCh );
        exit( EXIT_FAILURE );
    }

    exit( EXIT_SUCCESS );
}
/*
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 * version.c ends here */
