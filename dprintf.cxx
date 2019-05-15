#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dprintf.h"

char *dprintf (const char *fmt, ...) {
    static char tmp[65536];
    va_list args;
    size_t  len;

    va_start (args, fmt);
    len = vsprintf (tmp, fmt, args); 
    va_end (args);
    assert (len < sizeof (tmp));
    return strdup(tmp);
}
