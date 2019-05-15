/*
 * $Id: outtextxy.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Displays a string at a specified position.
 *
 * $Log: outtextxy.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"
#include "rotated.h"

void outtextxy(int x, int y, char *textstring)
{
        int alignment;
        float angle;
        XFontStruct *font_info;
        char *txtfont;
        int X;
        int Y;

        X = x + VPorigin.x;
        Y = y + VPorigin.y;

        txtfont = Fonts[txt_settings.font];
        font_info = XLoadQueryFont(dpy, txtfont);

        if (!txt_settings.direction)
                angle = 0.0;
        else
                angle = 90.0;
        switch (txt_settings.horiz) {
                case LEFT_TEXT:
                        switch (txt_settings.vert) {
                                case BOTTOM_TEXT:
                                        alignment = BLEFT;
                                        break;
                                case CENTER_TEXT:
                                        alignment = MLEFT;
                                        break;
                                case TOP_TEXT:
                                        alignment = TLEFT;
                                        break;
                                default:
                                        break;
                        }
                        break;
                case CENTER_TEXT:
                        switch (txt_settings.vert) {
                                case BOTTOM_TEXT:
                                        alignment = BCENTRE;
                                        break;
                                case CENTER_TEXT:
                                        alignment = MCENTRE;
                                        break;
                                case TOP_TEXT:
                                        alignment = TCENTRE;
                                        break;
                                default:
                                        break;
                        }
                        break;
                case RIGHT_TEXT:
                        switch (txt_settings.vert) {
                                case BOTTOM_TEXT:
                                        alignment = BRIGHT;
                                        break;
                                case CENTER_TEXT:
                                        alignment = MRIGHT;
                                        break;
                                case TOP_TEXT:
                                        alignment = TRIGHT;
                                        break;
                                default:
                                        break;
                        }
                        break;
                default:
                        break;
        }

        XRotDrawAlignedString(dpy, font_info, angle, drawable, gc, X, Y, 
                              textstring, alignment);
	if (visual_page == active_page)
		XRotDrawAlignedString(dpy, font_info, angle, window, gc, X, Y,
				      textstring, alignment);

	XFlush(dpy);
}
