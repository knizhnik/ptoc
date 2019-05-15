/*
 * $Id: putpixel.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Plots a pixel at a specified point.
 *
 * $Log: putpixel.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void putpixel(int x, int y, int color)
{
        XGCValues values;
        XGetGCValues(dpy, gc, GCForeground, &values);
        XSetForeground(dpy, gc, vga_palette[color].pixel_value);	
        XDrawPoint(dpy, drawable, gc, VPorigin.x + x, VPorigin.y + y);
	if (visual_page == active_page)
		XDrawPoint(dpy, window, gc, VPorigin.x + x, VPorigin.y + y);        
        XSetForeground(dpy, gc, values.foreground);	
        CP.x = x;
        CP.y = y;

	XFlush(dpy);
}
