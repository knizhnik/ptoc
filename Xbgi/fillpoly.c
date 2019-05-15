/*
 * $Id: fillpoly.c,v 0.1 1993/12/10 00:13:00 king Exp king $
 * Draws and fills a polygon.
 *
 * $Log: fillpoly.c,v $
 * Revision 0.1  1993/12/10  00:13:00  king
 * Initial version.
 *
 */
#include "graphics.h"

void fillpoly(int numpoints, int *polypoints)
{
        XPoint *points;
        XPoint *xptr;
        int *iptr;
        int i;
        
        points = (XPoint *) malloc(numpoints * sizeof(XPoint));

        for (i = 0, xptr = points, iptr = polypoints; i < numpoints; 
             i++, xptr++) {
                xptr->x = *(iptr++) + VPorigin.x;
                xptr->y = *(iptr++) + VPorigin.y;
        }
        XFillPolygon(dpy, drawable, fill_gc, points, numpoints, Complex,
                     CoordModeOrigin);
	if (visual_page == active_page)
		XFillPolygon(dpy, window, fill_gc, points, numpoints, Complex,
			     CoordModeOrigin);

        free(points);
/* draw the outline of the polygon */
        points = (XPoint *) malloc((numpoints + 1) * sizeof(XPoint));

        for (i = 0, xptr = points, iptr = polypoints; i < numpoints;
             i++, xptr++) {
                xptr->x = *(iptr++) + VPorigin.x;
                xptr->y = *(iptr++) + VPorigin.y;
        }
        iptr = polypoints;
        xptr->x = *(iptr++) + VPorigin.x;
        xptr->y = *(iptr) + VPorigin.y;
        XDrawLines(dpy, drawable, gc, points, numpoints + 1, CoordModeOrigin);
	if (visual_page == active_page)
		XDrawLines(dpy, window, gc, points, numpoints + 1,
			   CoordModeOrigin);

        free(points);

	XFlush(dpy);
}
