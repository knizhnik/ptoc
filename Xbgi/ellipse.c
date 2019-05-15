/*
 * $Id: ellipse.c,v 0.1 1993/12/10 00:12:23 king Exp king $
 * Draws an elliptical arc.
 *
 * $Log: ellipse.c,v $
 * Revision 0.1  1993/12/10  00:12:23  king
 * Initial version.
 *
 */
#include <math.h>

#include "graphics.h"

void ellipse(int x, int y, int stangle, int endangle, int xradius, int yradius)
{
        int X;
        int Y;
        int angle1;
        int angle2;
        float radian1;
        float radian2;
        int minor;
	int major;

        X = x - xradius + VPorigin.x;
        Y = y - yradius + VPorigin.y;
        angle1 = stangle * 64;          /* angles specified in 64-ths */
        angle2 = endangle * 64;         /* of a degree in X11 */
	angle2 -= angle1;
        radian1 = (float) stangle / 180.0 * M_PI;
        radian2 = (float) endangle / 180.0 * M_PI;
        minor = 2 * yradius;
	major = 2 * xradius;

        XDrawArc(dpy, drawable, gc, X, Y, major, minor, angle1, angle2);
	if (visual_page == active_page)
		XDrawArc(dpy, window, gc, X, Y, major, minor, angle1, angle2);

        last_arc.x = x;
        last_arc.y = y;
        last_arc.xstart = x + xradius * cos(radian1);
        last_arc.ystart = y - yradius * sin(radian1);
        last_arc.xend = x + xradius * cos(radian2);
        last_arc.ystart = y - yradius * sin(radian2);

        CP.x = last_arc.xend;
        CP.y = last_arc.yend;

	XFlush(dpy);
}
