#include <time.h>
#include "ptoc.h"

void timestamp(integer* day,  integer* month, integer* year, 
	       integer* hour, integer* min,   integer* sec)
{
    time_t ctime; 
    struct tm* tmp;

    time(&ctime);
    tmp = localtime(&ctime);

    *day = tmp->tm_mday; 
    *month = tmp->tm_mon + 1;
    *year = 1900 + tmp->tm_year; 
    *hour = tmp->tm_hour;
    *min = tmp->tm_min;
    *sec = tmp->tm_sec;
}

real get_realtime() 
{
    time_t ctime; 
    struct tm* tmp;

    time(&ctime);
    tmp = localtime(&ctime);

    return (real)(tmp->tm_hour + tmp->tm_min / 60.0); 
}

integer round(real x) 
{
    return x >= 0 ? trunc(x + 0.5) : trunc(x - 0.5); 
}

#define CIRCULAR_BUFFER_SIZE  4096

char* lpsz(int low, int high, const char* str) 
{ 
    static char buffer[CIRCULAR_BUFFER_SIZE];
    static int pos = 0;
    int size;
    char* ptr;

    while (high >= low && str[high-low] == ' ') {
	high -= 1;
    }
    size = high - low + 1;
    if (pos + size >= sizeof(buffer)) { 
	pos = 0;
    }
    ptr = &buffer[pos];
    pos += size + 1;
    memcpy(ptr, str, size);
    ptr[size] = '\0';
    return ptr;
}


unsigned randseed;
const unsigned modulus = 2147483647; 
const unsigned factor = 397204094; 

void Randomize()
{
    randseed = time(NULL);
}

unsigned randint(unsigned range)
{
    randseed = randseed * factor % modulus;
    return range ? randseed % range : 0; 
}

double randreal()
{
    randseed = randseed * factor % modulus;
    return (double)randseed / modulus;  
}

char* get_date()
{
    static char buf[16];

    time_t ctime; 
    struct tm* tmp;

    time(&ctime);
    tmp = localtime(&ctime);

    sprintf(buf, "%02d.%02d.%4d", tmp->tm_mday, tmp->tm_mon + 1, 1900 + tmp->tm_year);
    return buf;
}

char* get_time()
{
    static char buf[8];

    time_t ctime; 
    struct tm* tmp;

    time(&ctime);
    tmp = localtime(&ctime);
    
    sprintf(buf, "%d:%d", tmp->tm_hour, tmp->tm_min);
    return buf;
}

