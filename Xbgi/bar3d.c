/*
 * $Id: bar3d.c,v 0.1 1993/12/10 00:04:05 king Exp king $
 * Draws a three-dimensional bar.
 *
 * $Log: bar3d.c,v $
 * Revision 0.1  1993/12/10  00:04:05  king
 * Initial version.
 *
 */
#include "graphics.h"

void bar3d(int left, int top, int right, int bottom, int depth, int topflag)
{
        int X;
        int Y;
	int temp;
        int width;
        int height;
        XPoint *points;
        XPoint *xptr;
        int i;

	if (left > right) {     /* Turbo C corrects for badly ordered corners */
		temp = left;
		left = right;
		right = temp;
	}
	if (bottom < top) {
		temp = bottom;
		bottom = top;
		top = temp;
	}

        X = left + VPorigin.x;
        Y = top + VPorigin.y;
        width = right - left + 1;
        height = bottom - top + 1;

        XFillRectangle(dpy, drawable, fill_gc, X, Y, width + 1, height + 1);

	if (visual_page == active_page)
		XFillRectangle(dpy, window, fill_gc, X, Y, width + 1,
			       height + 1);

        XDrawRectangle(dpy, drawable, gc, X, Y, width, height);
	if (visual_page == active_page)
		XDrawRectangle(dpy, window, gc, X, Y, width, height);

        points = (XPoint *) malloc(4 * sizeof(XPoint));    /* 4 per lozenge */
        for (i = 0, xptr = points; i < 4; i++, xptr++) {
                switch (i) {
                        case 0:
                                xptr->x = right + VPorigin.x;
                                xptr->y = bottom + VPorigin.y;
                                break;
                        case 1:
                                xptr->x = depth;
                                xptr->y = -depth;
                                break;
                        case 2:
                                xptr->x = 0;
                                xptr->y = -height;
                                break;
                        case 3:
                                xptr->x = -depth;
                                xptr->y = depth;
                                break;
                        default:
                                break;
                }
        }
        XDrawLines(dpy, drawable, gc, points, 4, CoordModePrevious);
	if (visual_page == active_page)
		XDrawLines(dpy, window, gc, points, 4, CoordModePrevious);
        free(points);

        if (topflag) {
                points = (XPoint *) malloc(3 * sizeof(XPoint));
                for (i = 0, xptr = points; i < 3; i++, xptr++) {
                        switch (i) {
                                case 0:
                                        xptr->x = left + VPorigin.x;
                                        xptr->y = top + VPorigin.y;
                                        break;
                                case 1:
                                        xptr->x = depth;
                                        xptr->y = -depth;
                                        break;
                                case 2:
                                        xptr->x = width;
                                        xptr->y = 0;
                                        break;
                                default:
                                        break;
                        }
                }
                XDrawLines(dpy, drawable, gc, points, 3, CoordModePrevious);
		if (visual_page == active_page)
			XDrawLines(dpy, window, gc, points, 3,
				   CoordModePrevious);

                free(points);
        }

	XFlush(dpy);
}
