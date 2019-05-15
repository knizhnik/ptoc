/*
 * $Id: fillellipse.c,v 0.1 1993/12/10 00:12:36 king Exp king $
 * Draws and fills an ellipse.
 *
 * $Log: fillellipse.c,v $
 * Revision 0.1  1993/12/10  00:12:36  king
 * Initial version.
 *
 */
#include "graphics.h"

void fillellipse(int x, int y, int xradius, int yradius)
{
        int X;
        int Y;
        int angle;
        int xdiameter;
        int ydiameter;
        
        X = x - xradius + VPorigin.x;
        Y = y - yradius + VPorigin.y;
        angle = 360 * 64;
        xdiameter = 2 * xradius;
        ydiameter = 2 * yradius;

        XFillArc(dpy, drawable, fill_gc,  X, Y, xdiameter, ydiameter, 0, angle);
        XDrawArc(dpy, drawable, gc,  X, Y, xdiameter, ydiameter, 0, angle);
	if (visual_page == active_page) {
		XFillArc(dpy, window, fill_gc, X, Y, xdiameter, ydiameter, 0,
			 angle);
		XDrawArc(dpy, window, gc, X, Y, xdiameter, ydiameter, 0, angle);
	}
	
	XFlush(dpy);
}
