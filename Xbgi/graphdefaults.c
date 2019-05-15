/*
 * $Id: graphdefaults.c,v 0.1 1993/12/10 00:37:39 king Exp king $
 * Resets all the graphics settings to their default values.
 *
 * $Log: graphdefaults.c,v $
 * Revision 0.1  1993/12/10  00:37:39  king
 * Initial version.
 *
 */
#include "graphics.h"

void graphdefaults(void)
{
        XGCValues values;
	XWindowAttributes xwindow_attributes_return;
        int screen_num;

        CP.x = 0;
        CP.y = 0;
        VPorigin.x = 0;
        VPorigin.y = 0;

        screen_num = DefaultScreen(dpy);
        values.foreground = WhitePixel(dpy, screen_num);
        values.background = BlackPixel(dpy, screen_num);

        active_page = 0;
        visual_page = 0;
        drawable = (Drawable) *(pages);

        txt_settings.font = 0;
        txt_settings.direction = HORIZ_DIR;
        txt_settings.charsize = 1;
        txt_settings.horiz = LEFT_TEXT;
        txt_settings.vert = TOP_TEXT;

	aspectratio_x = 10000;
	aspectratio_y = 10000;

        fill_settings.pattern = SOLID_FILL;
        fill_settings.color = WHITE;

	XGetWindowAttributes(dpy, window, &xwindow_attributes_return);

        region = XCreateRegion();
        xrectangle.x = 0;
        xrectangle.y = 0;
        xrectangle.width = xwindow_attributes_return.width;
        xrectangle.height = xwindow_attributes_return.height;
        XUnionRectWithRegion(&xrectangle, region, region);
}
