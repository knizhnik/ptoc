/* 
 * $Id: getarccoords.c,v 0.1 1993/12/10 00:13:38 king Exp king $
 * Gets coordinates of the last call to arc().
 *
 * $Log: getarccoords.c,v $
 * Revision 0.1  1993/12/10  00:13:38  king
 * Initial version.
 * Revision 0.2  2012/12/06  12:30.00  GG
 * changed typedef struct {} name -> struct name
 *
 */
#include "graphics.h"

void getarccoords(struct arccoordstype *arccoords)
{
        memcpy(arccoords, &last_arc, sizeof(struct arccoordstype));
}
