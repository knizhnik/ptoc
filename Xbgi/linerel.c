/*
 * $Id: linerel.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Draws a line a relative distance from the current position, CP.
 *
 * $Log: linerel.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void linerel(int dx, int dy)
{
        XDrawLine(dpy, drawable, gc, VPorigin.x + CP.x, VPorigin.y + CP.y, 
                  VPorigin.x + CP.x + dx, VPorigin.y + CP.y + dy);
	if (visual_page == active_page)
		XDrawLine(dpy, window, gc, VPorigin.x + CP.x, VPorigin.y + CP.y,
			  VPorigin.x + CP.x + dx, VPorigin.y + CP.y + dy);

        CP.x += dx;
        CP.y += dy;

	XFlush(dpy);
}
