/*
 * $Id: getaspectratio.c,v 0.1 1993/12/10 00:13:38 king Exp king $
 * Retrieves the current graphics mode's aspect ratio.
 *
 * $Log: getaspectratio.c,v $
 * Revision 0.1  1993/12/10  00:13:38  king
 * Initial version.
 *
 */
#include "graphics.h"

void getaspectratio(int *xasp, int *yasp)
{
    *xasp = aspectratio_x;
    *yasp = aspectratio_y;       
}
