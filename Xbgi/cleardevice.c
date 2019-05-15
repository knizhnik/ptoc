/*
 * $Id: cleardevice.c,v 0.1 1993/12/10 00:10:02 king Exp king $
 * Clears the graphics screen.
 *
 * $Log: cleardevice.c,v $
 * Revision 0.1  1993/12/10  00:10:02  king
 * Initial version.
 *
 */
#include "graphics.h"

void cleardevice(void)
{
        XWindowAttributes window_attributes_return;
        int width;
        int height;
        GC temp_gc;
        XGCValues current_values;
        XGCValues temp_values;

        XGetWindowAttributes(dpy, window, &window_attributes_return);
        width = window_attributes_return.width;
        height = window_attributes_return.height;

        XGetGCValues(dpy, gc, GCBackground, &current_values);

        temp_values.fill_style = FillSolid;
        temp_values.foreground = current_values.background;
        temp_gc = XCreateGC(dpy, drawable, GCForeground, &temp_values);
        XFillRectangle(dpy, drawable, temp_gc, 0, 0, width, height);
	if (visual_page == active_page)
		XFillRectangle(dpy, window, temp_gc, 0, 0, width, height);

        XFreeGC(dpy, temp_gc);

        CP.x = 0;                 /* set the current drawing position to HOME */
        CP.y = 0;

	XFlush(dpy);
}
