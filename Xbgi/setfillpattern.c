/*
 * $Id: setfillpattern.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Selects a user-defined fill pattern.
 *
 * $Log: setfillpattern.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void setfillpattern(char *upattern, int color)
{
/* only support 8x8 bitmap patterns for now */
#if 0
        fill_pattern = XCreateBitmapFromData(dpy, window, upattern, 8, 8);
        XSetTSOrigin(dpy, fill_gc, 0, 0);
        XSetTile(dpy, fill_gc, fill_pattern);
#endif        
        fill_settings.pattern = USER_FILL;
        fill_settings.color = color;
}
