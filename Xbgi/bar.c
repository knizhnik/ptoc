/*
 * $Id: bar.c,v 0.1 1993/12/10 00:03:42 king Exp king $
 * Draws a two-dimensional bar.
 *
 * $Log: bar.c,v $
 * Revision 0.1  1993/12/10  00:03:42  king
 * Initial version.
 *
 */
#include "graphics.h"

void bar(int left, int top, int right, int bottom)
{
        int X;
        int Y;
	int temp;
        int width;
        int height;

	if (left > right) {	/* Turbo C corrects for badly ordered corners */
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

        XFillRectangle(dpy, drawable, fill_gc, X, Y, width, height);

	if (visual_page == active_page)
		XFillRectangle(dpy, window, fill_gc, X, Y, width, height);

	XFlush(dpy);
}
