/*
 * $Id: clearviewport.c,v 0.1 1993/12/10 00:10:23 king Exp king $
 * Clears the current viewport.
 *
 * $Log: clearviewport.c,v $
 * Revision 0.1  1993/12/10  00:10:23  king
 * Initial version.
 *
 */
#include "graphics.h"

void clearviewport(void)
{
        GC temp_gc;
        XGCValues current_values;
        XGCValues temp_values;

        XGetGCValues(dpy, gc, GCBackground, &current_values);

        temp_values.fill_style = FillSolid;
        temp_values.foreground = current_values.background;
        temp_gc = XCreateGC(dpy, drawable, GCForeground, &temp_values);
        XFillRectangle(dpy, drawable, temp_gc, xrectangle.x, xrectangle.y,
                       xrectangle.width, xrectangle.height);
	if (visual_page == active_page)
		XFillRectangle(dpy, window, temp_gc, xrectangle.x, xrectangle.y,
			       xrectangle.width, xrectangle.height);

        XFreeGC(dpy, temp_gc);

        CP.x = 0;
        CP.y = 0;
	
	XFlush(dpy);
}
