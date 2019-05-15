/*
 * $Id: settextjustify.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Sets the text justification for the graphics functions.
 *
 * $Log: settextjustify.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void settextjustify(int horiz, int vert)
{
        txt_settings.horiz = horiz;
        txt_settings.vert = vert;
}
