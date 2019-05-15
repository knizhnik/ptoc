/*
 * $Id: grapherrormsg.c,v 0.1 1993/12/10 00:37:39 king Exp king $
 * Returns a pointer to an error message string.
 *
 * $Log: grapherrormsg.c,v $
 * Revision 0.1  1993/12/10  00:37:39  king
 * Initial version.
 *
 */
#include <stdio.h>
#include <string.h>
#include "graphics.h"

char *grapherrormsg(int errorcode)
{
	enum graphics_errors gr_error;
	char *errormsg;

	gr_error = errorcode;
	switch (gr_error) {
		case grOk:
			strcpy(errormsg, "No error");
			break;
		case grNoInitGraph:
			strcpy(errormsg,
			      "XBGI graphics not installed (use initgraph()).");
			break;
		case grNotDetected:
			strcpy(errormsg, "Graphics hardware not detected.");
			break;
		case grFileNotFound:
			strcpy(errormsg, "Device driver file not found.");
			break;
		case grInvalidDriver:
			strcpy(errormsg, "Invalid device driver file.");
			break;
		case grNoLoadMem:
			strcpy(errormsg, "Not enough memory to load driver.");
			break;
		case grNoScanMem:
			strcpy(errormsg, "Out of memory in scan fill.");
			break;
		case grNoFloodMem:
			strcpy(errormsg, "Out of memory in flood fill.");
			break;
		case grFontNotFound:
			strcpy(errormsg, "Font file not found.");
			break;
		case grNoFontMem:
			strcpy(errormsg, "Not enough memory to load font.");
			break;
		case grInvalidMode:
			strcpy(errormsg, "Invalid graphics mode for"
				    "selected driver.");
			break;
		case grError:
			strcpy(errormsg, "Graphics error.");
			break;
		case grIOerror:
			strcpy(errormsg, "Graphics I/O error.");
			break;
		case grInvalidFont:
			strcpy(errormsg, "Invalid font file.");
			break;
		case grInvalidFontNum:
			strcpy(errormsg, "Invalid font number.");
			break;
		case grInvalidDeviceNum:
			strcpy(errormsg, "Invalid device number.");
			break;
		case grInvalidVersion:
			strcpy(errormsg, "Invalid version of file.");
			break;
		default:
			break;
	}

	return (errormsg);
}
