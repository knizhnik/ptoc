/*
 * $Id: getimage.c,v 0.11 1993/12/16 00:06:58 king Exp king $
 * Saves a bit image of the specified region into memory.
 *
 * $Log: getimage.c,v $
 * Revision 0.11  1993/12/16  00:06:58  king
 * getimage() provided by Tero and Juki.
 *
 * Revision 0.1  1993/12/10  00:15:31  king
 * Initial version.
 *
 */
#include "graphics.h"

void getimage(int left, int top, int right, int bottom, void *bitmap)
{
	int X;
	int Y;
	int width;
	int height;
	bgi_image *bm = (bgi_image*)bitmap;
	Pixmap pixmap;
	XGCValues op_gcv;
	GC op_gc;

	X = left + VPorigin.x;
	Y = top + VPorigin.y;
	width = right - left + 1;
	height = bottom - top + 1;
	
	pixmap = XCreatePixmap(dpy, window, width, height,
			       XDefaultDepth(dpy, DefaultScreen(dpy)));
	op_gc = XCreateGC(dpy, drawable, 0, NULL);
	XCopyGC(dpy, gc, (GCBackground | GCForeground | GCPlaneMask),
		op_gc);
	op_gcv.function = GXcopy;
	XChangeGC(dpy, op_gc, GCFunction, &op_gcv);
	
	XCopyArea(dpy, drawable, pixmap, op_gc, X, Y, width, height, 0, 0);
	bm->width = width;
	bm->height  = height;
	bm->pixmap = pixmap;
	XFreeGC(dpy, op_gc);
}
