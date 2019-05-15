/*
 * $Id: getviewsettings.c,v 0.1 1993/12/10 00:15:31 king Exp king $
 * Gets information about the current viewport.
 *
 * $Log: getviewsettings.c,v $
 * Revision 0.1  1993/12/10  00:15:31  king
 * Initial version.
 * Revision 0.2  2012/12/06  12:30.00  GG
 * changed typedef struct {} name -> struct name
 *
 */
#include "graphics.h"

void getviewsettings(struct viewporttype *viewport)
{
        memcpy(viewport, &view_settings, sizeof(struct viewporttype));
}
