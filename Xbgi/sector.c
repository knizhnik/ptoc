/*
 * $Id: sector.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Draws and fills an elliptical pie slice.
 *
 * $Log: sector.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void sector(int x, int y, int stangle, int endangle, int xradius, int yradius)
{
        int X;
        int Y;
        int angle1;
        int angle2;
        int xdiameter;
        int ydiameter;

        X = x - xradius + VPorigin.x;
        Y = y - yradius + VPorigin.y;
        angle1 = stangle * 64;
        angle2 = endangle * 64;
	angle2 -= angle1;
        xdiameter = 2 * xradius;
        ydiameter = 2 * yradius;

        XFillArc(dpy, drawable, fill_gc, X, Y, xdiameter, ydiameter, angle1, 
                 angle2);
	if (visual_page == active_page)
		XFillArc(dpy, window, fill_gc, X, Y, xdiameter, ydiameter,
			 angle1, angle2);

	XFlush(dpy);
}
