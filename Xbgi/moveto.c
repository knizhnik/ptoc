/*
 * $Id: moveto.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Moves the current position (CP) to (x, y).
 *
 * $Log: moveto.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void moveto(int x, int y)
{
        CP.x = x;
        CP.y = y;
}
