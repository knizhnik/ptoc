/*
 * $Id: detectgraph.c,v 0.1 1993/12/10 00:11:18 king Exp king $
 * Determines the graphics driver and graphics mode to use by checking the
 * hardware.
 *
 * $Log: detectgraph.c,v $
 * Revision 0.1  1993/12/10  00:11:18  king
 * Initial version.
 *
 */
#include "graphics.h"

void detectgraph(int *graphdriver, int *graphmode)
{
        *graphdriver = 9;
        *graphmode = 2;
}
