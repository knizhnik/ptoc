/*
 * $Id: pieslice.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Draws and fills in a pie slice.
 *
 * $Log: pieslice.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void pieslice(int x, int y, int stangle, int endangle, int radius)
{
        int X;
        int Y;
        int angle1;
        int angle2;
        int diameter;

        X = x - radius + VPorigin.x;
        Y = y - radius + VPorigin.y;
        angle1 = stangle * 64;
        angle2 = endangle * 64;
	angle2 -= angle1;
        diameter = 2 * radius;

        XFillArc(dpy, drawable, fill_gc, X, Y, diameter, diameter, angle1, 
                 angle2);
        XDrawArc(dpy, drawable, gc, X, Y, diameter, diameter, angle1, angle2);
	if (visual_page == active_page) {
		XFillArc(dpy, window, fill_gc, X, Y, diameter, diameter, angle1,
			 angle2);
		XDrawArc(dpy, window, gc, X, Y, diameter, diameter, angle1,
			 angle2);
	}

	XFlush(dpy);
}
