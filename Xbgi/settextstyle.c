/*
 * $Id: settextstyle.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Sets the current text characteristics for graphics output.
 *
 * $Log: settextstyle.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 * Revision 0.2  2012/12/20  12:30.00  GG
 *
 */
#include "graphics.h"

void settextstyle(int font, int direction, int charsize)
{
        XFontStruct *font_info;
        char *txtfont;

        txt_settings.font = font&7; /* GG - was 3 */
        txt_settings.direction = direction;
        txt_settings.charsize = charsize;

        txtfont = Fonts[txt_settings.font];
        if ((font_info = XLoadQueryFont(dpy, txtfont)) == NULL) {
                fprintf(stderr, "Error opening font %s.\n", txtfont);
                exit(-1);
        }
        XSetFont(dpy, gc, font_info->fid);
}
