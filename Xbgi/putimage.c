/*
 * $Id: putimage.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Outputs a bit image to the screen.
 *
 * $Log: putimage.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "graphics.h"

void putimage(int left, int top, void *bitmap, int op)
{
	int X;
	int Y;
	int width;
	int height;
	bgi_image *bm = (bgi_image*)bitmap;
	XGCValues op_gcv;
	GC op_gc;
	Pixmap pixmap;

	width = bm->width;
	height = bm->height;
	pixmap = bm->pixmap;
	
	X = left + VPorigin.x;
	Y = top + VPorigin.y;

	op_gc = XCreateGC(dpy, drawable, 0, NULL);
	XCopyGC(dpy, gc, (GCBackground | GCForeground | GCPlaneMask), op_gc);
	
	switch (op) {
		case COPY_PUT:
			op_gcv.function = GXcopy;
			break;
		case XOR_PUT:
			op_gcv.function = GXxor;
			break;
		case OR_PUT:
			op_gcv.function = GXor;
			break;
		case AND_PUT:
			op_gcv.function = GXand;
			break;
		case NOT_PUT:
			op_gcv.function = GXcopyInverted;
			break;
		default:
			break;
	}
	op_gcv.tile = pixmap;
	op_gcv.fill_style = FillTiled;
	op_gcv.ts_x_origin = X;
	op_gcv.ts_y_origin = Y;

	XChangeGC(dpy, op_gc, (GCFunction | GCTile | GCFillStyle | GCTileStipXOrigin |
		  GCTileStipYOrigin), &op_gcv);
#ifdef ALLOCATE_COLOR_CELLS
	XSetPlaneMask(dpy, op_gc, plane_masks);
#endif
	XFillRectangle(dpy, drawable, op_gc, X, Y, width, height);
	if (visual_page == active_page)
		XFillRectangle(dpy, window, op_gc, X, Y, width, height);
	XFreeGC(dpy, op_gc);
	XFlush(dpy); /* GG - added */
}



