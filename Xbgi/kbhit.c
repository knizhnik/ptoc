#include "graphics.h"

int kbhit(void)
{
        XEvent report;

        if (XCheckTypedWindowEvent(dpy, window, KeyPress, &report)) {
	    XPutBackEvent(dpy, &report);
	    return 1;
        } else { 
	    return 0;
	} 
}
