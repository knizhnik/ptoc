/*
 * $Id: getmaxy.c,v 0.1 1993/12/10 00:15:31 king Exp king $
 * Returns the maximum y window coordinate.
 *
 * $Log: getmaxy.c,v $
 * Revision 0.1  1993/12/10  00:15:31  king
 * Initial version.
 *
 */
#include "graphics.h"

int getmaxy(void)
{
/* returns the maximum y window coordinate */
        XWindowAttributes window_attributes_return;

        XGetWindowAttributes(dpy, window, &window_attributes_return);
        return window_attributes_return.height - 1;
}
