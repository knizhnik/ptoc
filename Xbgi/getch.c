#include "graphics.h"

int getch (void)
{
  XEvent event;
  char c;
  
  while(1) {
    XNextEvent(dpy, &event);
    if (event.type == KeyPress) {
      c = (char) XLookupKeysym(&event.xkey, 0);
      return (int) c;
    }
  }
  
}
