/*
 * $Id: lineto.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Draws a line from the current position (CP) to (x, y).
 *
 * $Log: lineto.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void lineto(int x, int y)
{
        XDrawLine(dpy, drawable, gc, VPorigin.x + CP.x, VPorigin.y + CP.y,
                  VPorigin.x + x, VPorigin.y + y);
	if (visual_page == active_page)
		XDrawLine(dpy, window, gc, VPorigin.x + CP.x, VPorigin.y + CP.y,
			  VPorigin.x + x, VPorigin.y + y);

        CP.x = x;
        CP.y = y;

	XFlush(dpy);
}
