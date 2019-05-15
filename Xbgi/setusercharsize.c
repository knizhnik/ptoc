/*
 * $Id: setusercharsize.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Varies character width and height for stroked fonts.
 *
 * $Log: setusercharsize.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void setusercharsize(int multx, int divx, int multy, int divy)
{
        float xmagnification;
        float ymagnification;

        xmagnification = (float) multx / (float) divx;
        ymagnification = (float) multy / (float) divy;
        XRotSetMagnification(xmagnification, ymagnification);
}
