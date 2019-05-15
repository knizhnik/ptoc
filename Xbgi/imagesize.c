/*
 * $Id: imagesize.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Returns the number of bytes required to store a bit image.
 *
 * $Log: imagesize.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

unsigned int imagesize(int left, int top, int right, int bottom)
{
    return sizeof(bgi_image);
}
