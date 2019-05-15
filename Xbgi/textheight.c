/*
 * $Id: textheight.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Returns the height of a string in pixels.
 *
 * $Log: textheight.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"
#include "rotated.h"

int textheight(char *textstring)
{
        XFontStruct *font_info;
        char *txtfont;

        txtfont = Fonts[txt_settings.font];
        font_info = XLoadQueryFont(dpy, txtfont);

        return (int) (font_info->ascent + font_info->descent);
}
