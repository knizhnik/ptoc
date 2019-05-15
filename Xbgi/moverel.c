/*
 * $Id: moverel.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Moves the current position (CP) a relative distance.
 *
 * $Log: moverel.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void moverel(int dx, int dy)
{
        CP.x += dx;
        CP.y += dy;
}
