/*
 * $Id: circle.c,v 0.1 1993/12/10 00:04:25 king Exp king $
 * Draws a circle of the given radius with its centre at (x, y).
 *
 * $Log: circle.c,v $
 * Revision 0.1  1993/12/10  00:04:25  king
 * Initial version.
 *
 */
#include "graphics.h"

void circle(int x, int y, int radius)
{
        int X;
        int Y;
        int angle;
        int diameter;
	unsigned rx = radius;
	unsigned ry = rx*aspectratio_x/aspectratio_y;

        X = x - rx + VPorigin.x;
        Y = y - ry + VPorigin.y;
        angle = 360 * 64;

        XDrawArc(dpy, drawable, gc, X, Y, 2*rx, 2*ry, 0, angle);
	if (visual_page == active_page)
		XDrawArc(dpy, window, gc, X, Y, 2*rx, 2*ry, 0, angle);        

        CP.x = x + rx;
        CP.y = y;

	XFlush(dpy);
}
