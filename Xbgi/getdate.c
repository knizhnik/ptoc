#include <unistd.h>
#include <time.h>
#include "graphics.h"

void get_date(struct date *datep)
{
        struct tm *thedate;
        time_t clock;

        time(&clock);
        thedate = localtime(&clock);
        datep->da_year = thedate->tm_year;
        datep->da_day = thedate->tm_mday;
        datep->da_mon = thedate->tm_mon + 1;
}
