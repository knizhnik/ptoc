/*
 * $Id: setactivepage.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Sets the active page for graphics output.
 *
 * $Log: setactivepage.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void setactivepage(int page)
{
        active_page = page;
        drawable = (Drawable) *(pages + page);
}
