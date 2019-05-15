/*
 * $Id: textwidth.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Returns the width of a string in pixels.
 *
 * $Log: textwidth.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"
#include "rotated.h"

int textwidth(char *textstring)
{
        XFontStruct *font_info;
        char *txtfont;
        
        txtfont = Fonts[txt_settings.font];
        font_info = XLoadQueryFont(dpy, txtfont);
        
        return (int) XTextWidth(font_info, textstring, strlen(textstring));
}
