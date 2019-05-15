/*
 * $Id: setaspectratio.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Changes the default aspect ratio correction factor.
 *
 * $Log: setaspectratio.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void setaspectratio(int xasp, int yasp)
{
    aspectratio_x = xasp;
    aspectratio_y = yasp;
}

