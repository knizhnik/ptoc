/*
 * $Id: setwritemode.c,v 0.1 1993/12/10 00:39:08 king Exp king $
 * Sets the writing mode for line drawing in graphics mode.
 *
 * $Log: setwritemode.c,v $
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

void setwritemode(int mode)
{
        XGCValues values;

        switch (mode) {
                case COPY_PUT:
                        values.function = GXcopy;
                        break;
                case XOR_PUT:
                        values.function = GXxor;
                        break;
                case OR_PUT:
                        values.function = GXor;
                        break;
                case AND_PUT:
                        values.function = GXand;
                        break;
                case NOT_PUT:
                        values.function = GXcopyInverted;
                        break;
                default:
                        break;
        }
        XChangeGC(dpy, gc, GCFunction, &values);
        XChangeGC(dpy, fill_gc, GCFunction, &values);
}
