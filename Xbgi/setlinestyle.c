/*
 * $Id: setlinestyle.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Sets the current line width and style.
 *
 * $Log: setlinestyle.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

int dash_list_length[] = {
        DOTTEDLINE_LENGTH, CENTRELINE_LENGTH, DASHEDLINE_LENGTH
};
unsigned char dottedline[DOTTEDLINE_LENGTH] =
        {1, 1};
unsigned char centreline[CENTRELINE_LENGTH] =
        {5, 1, 1, 1};
unsigned char dashedline[DASHEDLINE_LENGTH] =
        {2, 2};
unsigned char *dash_list[] = {
        dottedline, centreline, dashedline
};


void setlinestyle(int linestyle, unsigned upattern, int thickness)
{
        XGCValues values;
        int dash_offset;
        
        dash_offset = 0;
        switch (linestyle) {
                case SOLID_LINE:
                        values.line_style = LineSolid;
                        break;
                case DOTTED_LINE:
                        values.line_style = LineOnOffDash;
                        XSetDashes(dpy, gc, dash_offset, dash_list[0],
                                   dash_list_length[0]);
                        break;
                case CENTER_LINE:
                        values.line_style = LineOnOffDash;
                        XSetDashes(dpy, gc, dash_offset, dash_list[1],
                                   dash_list_length[1]);
                        break;
                case DASHED_LINE:
                        values.line_style = LineOnOffDash;
                        XSetDashes(dpy, gc, dash_offset, dash_list[2],
                                   dash_list_length[2]);
                        break;
                default:
                        return;
        }
        values.line_width = thickness;
        XChangeGC(dpy, gc, GCLineWidth | GCLineStyle, &values);
}
