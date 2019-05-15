/*
 * $Id: setviewport.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Sets the current viewport for graphics output.
 *
 * $Log: setviewport.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void setviewport(int left, int top, int right, int bottom, int clip)
{
        XCopyArea(dpy, window, window, gc, 0, 0, getmaxx(), getmaxy(), 0, 0);
        XDestroyRegion(region);
        region = XCreateRegion();
        xrectangle.x = (short) left;
        xrectangle.y = (short) top;
        xrectangle.width = (unsigned short) (right - left) + 1;
        xrectangle.height = (unsigned short) (bottom - top) + 1;
        XUnionRectWithRegion(&xrectangle, region, region);
        if (clip) {
                XSetClipOrigin(dpy, gc, left, top);
                XSetClipOrigin(dpy, fill_gc, left, top);
                XSetRegion(dpy, gc, region);
                XSetRegion(dpy, fill_gc, region);
        } else {
                xrectangle.x = 0;
                xrectangle.y = 0;
                xrectangle.width = getmaxx();
                xrectangle.height = getmaxy();
                XUnionRectWithRegion(&xrectangle, region, region);
                XSetClipOrigin(dpy, gc, 0, 0);
                XSetClipOrigin(dpy, fill_gc, 0, 0);
                XSetRegion(dpy, gc, region);
                XSetRegion(dpy, fill_gc, region);
        }
        
        view_settings.left = left;
        view_settings.top = top;
        view_settings.right = right;
        view_settings.bottom = bottom;
        view_settings.clip = clip;
        VPorigin.x = left;
        VPorigin.y = top;
        CP.x = 0;
        CP.y = 0;
}
