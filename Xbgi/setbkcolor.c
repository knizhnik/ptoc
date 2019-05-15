/*
 * $Id: setbkcolor.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Sets the current background colour using the palette.
 *
 * $Log: setbkcolor.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void setbkcolor(int color)
{
        XColor background;
        XColor unused;
        char *bg;
        int screen_number;
	int rc;

#ifdef ALLOCATE_COLOR_CELLS
	XStoreNamedColor(dpy, cmap, Colors[color], background_pixel,
			 (DoRed|DoGreen|DoBlue));
#else
        rc = XSetBackground(dpy, gc, vga_palette[color].pixel_value);

	if (visual_page == active_page) { 
	    XSetWindowBackground(dpy, window, vga_palette[color].pixel_value);
	} 
#endif
}


