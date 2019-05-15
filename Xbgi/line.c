/*
 * $Id$
 * Draws a line between two specified points.
 *
 * $Log$
 */
#include "graphics.h"

void line(int x1, int y1, int x2, int y2)
{
        int X1;
        int Y1;
        int X2;
        int Y2;

        X1 = x1 + VPorigin.x;
        Y1 = y1 + VPorigin.y;
        X2 = x2 + VPorigin.x;
        Y2 = y2 + VPorigin.y;

        XDrawLine(dpy, drawable, gc, X1, Y1, X2, Y2);
	if (visual_page == active_page)
		XDrawLine(dpy, window, gc, X1, Y1, X2, Y2);

	XFlush(dpy);
}
