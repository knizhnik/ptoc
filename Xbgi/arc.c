/*
 * $Id: arc.c,v 0.11 1993/12/16 00:20:57 king Exp king $
 * Draws an arc.
 *
 * $Log: arc.c,v $
 * Revision 0.11  1993/12/16  00:20:57  king
 * Fixed bug with endstangle not being relative to stangle.  Thanks to Tero and
 * Juki for this one.
 *
 * Revision 0.1  1993/12/10  00:03:16  king
 * Initial version.
 *
 */
#include <math.h>

#include "graphics.h"

void arc(int x, int y, int stangle, int endangle, int radius)
{
        int X;
        int Y;
        int angle1;
        int angle2;
        float radian1;
        float radian2;
        int diameter;

        X = x - radius + VPorigin.x;
        Y = y - radius + VPorigin.y;
        angle1 = stangle * 64;          /* angles specified in 64-ths */
        angle2 = endangle * 64;         /* of a degree in X11 */
	angle2 -= angle1;
        radian1 = (float) stangle / 180.0 * M_PI;
        radian2 = (float) endangle / 180.0 * M_PI;
        diameter = 2 * radius;

        XDrawArc(dpy, drawable, gc, X, Y, diameter, diameter, angle1, angle2);

        last_arc.x = x;
        last_arc.y = y;
        last_arc.xstart = x + radius * cos(radian1);
        last_arc.ystart = y - radius * sin(radian1);
        last_arc.xend = x + radius * cos(radian2);
        last_arc.yend = y - radius * sin(radian2);

        CP.x = last_arc.xend;
        CP.y = last_arc.yend;

	if (visual_page == active_page)
		XDrawArc(dpy, window, gc, X, Y, diameter, diameter, angle1, 
			 angle2);

	XFlush(dpy);
}
