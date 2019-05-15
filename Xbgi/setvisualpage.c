/*
 * $Id: setvisualpage.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Sets the visual graphics page number.
 *
 * $Log: setvisualpage.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void setvisualpage(int page)
{
        visual_page = page;
        XCopyArea(dpy, *(pages + page), window, gc, 0, 0, getmaxx(), 
                  getmaxy(), 0, 0);
}
