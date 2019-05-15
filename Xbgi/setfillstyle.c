/*
 * $Id: setfillstyle.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Sets the fill pattern and colour.
 *
 * $Log: setfillstyle.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void setfillstyle(int pattern, int color)
{
        XColor foreground;
        XColor unused;
        char *fill_color;
        int screen_num;
        
        screen_num = DefaultScreen(dpy);
        fill_color = Colors[color];
        XSetForeground(dpy, fill_gc, vga_palette[color].pixel_value);

        fill_settings.pattern = pattern;
        fill_settings.color = color;
}

