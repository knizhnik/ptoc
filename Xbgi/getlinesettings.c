/*
 * $Id: getlinesettings.c,v 0.1 1993/12/10 00:15:31 king Exp king $
 * Gets the current line style, pattern and thickness.
 *
 * $Log: getlinesettings.c,v $
 * Revision 0.1  1993/12/10  00:15:31  king
 * Initial version.
 * Revision 0.2  2012/12/06  12:30.00  GG
 * changed typedef struct {} name -> struct name
 *
 */
#include "graphics.h"

void getlinesettings(struct linesettingstype *lineinfo)
{
        XGCValues values;

        XGetGCValues(dpy, gc, GCLineStyle | GCLineWidth, &values);
        
        switch (values.line_style) {
                case LineSolid:
                        lineinfo->linestyle = SOLID_LINE;
                        break;
                case LineOnOffDash:
                        lineinfo->linestyle = DASHED_LINE;
                        break;
                default:
                        break;
        }
        switch (values.line_width) {
                case 0: case 1:
                        lineinfo->thickness = NORM_WIDTH;
                        break;
                case 3:
                        lineinfo->thickness = THICK_WIDTH;
                        break;
                default:
                        lineinfo->thickness = values.line_width;
                        break;
        }
}
