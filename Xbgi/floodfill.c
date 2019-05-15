/*
 * $Id: floodfill.c,v 0.1 1993/12/10 00:13:14 king Exp king $
 * Flood-fills a bounded region.
 *
 * $Log: floodfill.c,v $
 * Revision 0.1  1993/12/10  00:13:14  king
 * Initial version.
 * 
 */

/*
 * A Seed Fill Algorithm
 * by Paul Heckbert
 * from "Graphics Gems", Academic Press, 1990
 *
 * user provides getpixel() and putpixel() routines
 * http://tog.acm.org/resources/GraphicsGems/gems/SeedFill.c
 * 
 * adapted by GG
 * 
 */

#include "graphics.h"

typedef struct {
  short y, xl, xr, dy;
} Segment;

/*
 * Filled horizontal segment of scanline y for xl<=x<=xr.
 * Parent segment was on line y-dy.  dy=1 or -1
 */

#define MAX 10000               /* max depth of stack */

#define PUSH(Y, XL, XR, DY)     /* push new segment on stack */ \
    if (sp < stack+MAX && Y+(DY) >= 0 && Y+(DY) <= getmaxy ()) \
    {sp->y = Y; sp->xl = XL; sp->xr = XR; sp->dy = DY; sp++;}

#define POP(Y, XL, XR, DY)      /* pop segment off stack */ \
    {sp--; Y = sp->y+(DY = sp->dy); XL = sp->xl; XR = sp->xr;}

/*
 * fill: set the pixel at (x,y) and all of its 4-connected neighbors
 * with the same pixel value to the new pixel value nv.
 * A 4-connected neighbor is a pixel above, below, left, or right of a pixel.
 */

void floodfill (int x, int y, int border)
{
  int l, x1, x2, dy;
  int nv, ov;   /* new and old pixel value */
  Segment stack[MAX], *sp = stack;      /* stack of filled segments */

  nv = getcolor ();
  ov = getpixel (x, y);          /* read pv at seed point */
  /* if (ov == nv || x < 0 || x > getmaxx () ||  */
  /*     y < 0 || y > getmaxy ()) */
  if (ov == nv)
    return;
  PUSH(y, x, x, 1);             /* needed in some cases */
  PUSH(y+1, x, x, -1);          /* seed segment (popped 1st) */
  
  while (sp > stack) {
    /* pop segment off stack and fill a neighboring scan line */
    POP(y, x1, x2, dy);
    /*
     * segment of scan line y-dy for x1<=x<=x2 was previously filled,
     * now explore adjacent pixels in scan line y
     */
    for (x = x1; x >= 0 && getpixel(x, y) != border; x--)
      putpixel (x, y, nv);
    if (x >= x1)
      goto skip;
    l = x+1;
    if (l < x1)
      PUSH(y, l, x1-1, -dy);    /* leak on left? */
    x = x1+1;
    do {
      for (; x <= getmaxx () && getpixel(x, y) == ov; x++)
        putpixel(x, y, nv);
      PUSH(y, l, x-1, dy);
      if (x > x2+1)
        PUSH(y, x2+1, x-1, -dy);        /* leak on right? */
skip:
      for (x++; x <= x2 && getpixel(x, y) != ov; x++);
      l = x;
    } while (x <= x2);
  }
}
