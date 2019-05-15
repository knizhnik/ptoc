/*
 * $Id: restorecrtmode.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Restores the screen mode to its pre-initgraph() setting.
 *
 * $Log: restorecrtmode.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void restorecrtmode(void)
{
  cleardevice ();
}
