/*
 * $Id: closegraph.c,v 0.1 1993/12/10 00:10:55 king Exp king $
 * Shuts down the graphics system.
 *
 * $Log: closegraph.c,v $
 * Revision 0.1  1993/12/10  00:10:55  king
 * Initial version.
 *
 */
#include "graphics.h"

void closegraph(void)
{
    if (vga_palette != NULL) { 
        free(vga_palette);
	vga_palette = NULL;
    }
    if (pages != NULL) { 
        free(pages);	/* check this for memory leaks */
	pages = NULL;
    }
    if (dpy != NULL) { 
	if (gc != NULL) { 
	    XFreeGC(dpy, gc);
	}
	if (fill_gc != NULL) { 
	    XFreeGC(dpy, fill_gc);
	}
	if (window != 0) { 
	    XDestroyWindow(dpy, window);
	}
	XCloseDisplay(dpy);
	dpy = NULL;
    }
}





