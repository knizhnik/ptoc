/*
 * $Id: getmaxcolor.c,v 0.1 1993/12/10 00:15:31 king Exp king $
 * Returns the maximum colour value that can be passed to the setcolor()
 * function.
 *
 * $Log: getmaxcolor.c,v $
 * Revision 0.1  1993/12/10  00:15:31  king
 * Initial version.
 *
 */
#include "graphics.h"

int getmaxcolor(void)
{
/* currently supports the colours used by EGAVGA.BGI */
        return (int) WHITE;
}
