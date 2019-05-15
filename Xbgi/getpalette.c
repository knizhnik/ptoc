/*
 * $Id: getpalette.c,v 0.1 1993/12/10 00:15:31 king Exp king $
 * Gets information about the current palette.
 *
 * $Log: getpalette.c,v $
 * Revision 0.1  1993/12/10  00:15:31  king
 * Initial version.
 * Revision 0.2  2012/12/06  12:30.00  GG
 * changed typedef struct {} name -> struct name
 */
#include "graphics.h"

void getpalette(struct palettetype *palette)
{
  int i;
  palette->size = 16;
  for (i = 0; i < MAXCOLORS + 1; i++)
    palette->colors[i] = i;
}
