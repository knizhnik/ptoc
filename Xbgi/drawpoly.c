/*
 * $Id: drawpoly.c,v 0.1 1993/12/10 00:11:48 king Exp king $
 * Draws the outline of a polygon.
 *
 * $Log: drawpoly.c,v $
 * Revision 0.1  1993/12/10  00:11:48  king
 * Initial version.
 *
 */
#include "graphics.h"

void drawpoly(int numpoints, int *polypoints)
{
        XPoint *points;
        XPoint *xptr;
        int i;

        points = (XPoint *) malloc(numpoints * sizeof(XPoint));

        for (i = 0, xptr = points; i < numpoints; i++, xptr++) {
                xptr->x = *(polypoints++) + VPorigin.x;
                xptr->y = *(polypoints++) + VPorigin.y;
        }
        XDrawLines(dpy, drawable, gc, points, numpoints, CoordModeOrigin);
	if (visual_page == active_page)
		XDrawLines(dpy, window, gc, points, numpoints, CoordModeOrigin);

        free(points);

	XFlush(dpy);
}
