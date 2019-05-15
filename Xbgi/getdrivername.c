/*
 * $Id: getdrivername.c,v 0.1 1993/12/10 00:15:31 king Exp king $
 * Returns a pointer to a string containing the name of the current graphics
 * driver.
 *
 * $Log: getdrivername.c,v $
 * Revision 0.1  1993/12/10  00:15:31  king
 * Initial version.
 *
 */
#include "graphics.h"

char *getdrivername(void)
{
    return "EGAVGA";
}

