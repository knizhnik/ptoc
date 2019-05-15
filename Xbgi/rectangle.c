/*
 * $Id: rectangle.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Draws a rectangle.
 *
 * $Log: rectangle.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void rectangle(int left, int top, int right, int bottom)
{
        unsigned int width;
        unsigned int height;

        width = right - left + 1;
        height = bottom - top + 1;

        XDrawRectangle(dpy, drawable, gc, VPorigin.x + left, VPorigin.y + top, 
                       width, height);
	if (visual_page == active_page)
		XDrawRectangle(dpy, window, gc, VPorigin.x + left, VPorigin.y +
			       top, width, height);

	XFlush(dpy);
}
