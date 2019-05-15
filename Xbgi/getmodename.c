/*
 * $Id: getmodename.c,v 0.1 1993/12/10 00:15:31 king Exp king $
 * Returns a pointer to a string containing the name of a specified graphics 
 * mode.
 *
 * $Log: getmodename.c,v $
 * Revision 0.1  1993/12/10  00:15:31  king
 * Initial version.
 *
 */
#include "graphics.h"

char *getmodename(int mode_number)
{
        char *dpyname;
        static char modename[256];

        dpyname = getenv("DISPLAY");
        sprintf(modename, "%d x %d %s", getmaxx(), getmaxy(), 
		dpyname ? dpyname : "EGAVGA");
	return modename;
}
