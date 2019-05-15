/*
 * $Id: getfillpattern.c,v 0.1 1993/12/10 00:15:31 king Exp king $
 * Copies a user-defined fill pattern into memory.
 *
 * $Log: getfillpattern.c,v $
 * Revision 0.1  1993/12/10  00:15:31  king
 * Initial version.
 *
 */
#include "graphics.h"

void getfillpattern(char *pattern)
{
        XGCValues values;

        XGetGCValues(dpy, gc, GCFillStyle, &values);
}
