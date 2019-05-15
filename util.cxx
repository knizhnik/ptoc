#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#include "nmtbl.h"
#include "token.h"
#include "trnod.h"
#include "util.h"


memory_allocator heap;


char* token_tag_name[] = {
#define DEF_TOKEN(mnem, cat, tag, lex) #tag,
#include "token.dpp"
#undef DEF_TOKEN
    NULL
};

void error(const char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    putc('\n',stderr);
    exit (EXIT_FAILURE);
}

void error(int line, int pos, const char* file, const char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "%s:%d %d error: ", file, line, pos);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    putc('\n',stderr);
    exit (EXIT_FAILURE);
}

void error(token* tkn, const char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);

    while(tkn->tag == TKN_GEN) tkn = tkn->next;

    fprintf(stderr, "%s:%d %d (token %s) error: ", 
	    tkn->fname, tkn->line, tkn->pos, token_tag_name[tkn->tag]);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    putc('\n',stderr);
    exit (EXIT_FAILURE);
}

void warning(const char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "warning: ");
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    putc('\n',stderr);
}

void warning(int line, int pos, const char* file, const char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "%s:%d %d warning: ", file, line, pos);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    putc('\n',stderr);
}

void warning(token* tkn, const char* fmt, ...)
{
    va_list ap;

    while(tkn->tag == TKN_GEN) tkn = tkn->next;

    va_start(ap, fmt);
    fprintf(stderr, "%s:%d %d warning: ", tkn->fname, tkn->line, tkn->pos );
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    putc('\n',stderr);
}

extern "C" char* strdup(const char* s) 
{
    return strcpy((char*)heap.alloc(strlen(s)+1), s);
}

extern "C" char* strupper(const char* s) 
{
    char* new_s = (char*)heap.alloc(strlen(s)+1);
    char* dst = new_s;
    unsigned char* src = (unsigned char*)s;
    do { 
	*dst++ = toupper(*src);
    } while (*src++ != 0);
    return new_s;
}

extern "C" int strincmp(char const* s1, char const* s2, int n) 
{ 
    unsigned char* p = (unsigned char*)s1;    
    unsigned char* q = (unsigned char*)s2;
    while (--n >= 0) { 
	if (tolower(*p) != tolower(*q)) { 
	    return tolower(*p) - tolower(*q);
	}
	if (*p == '\0') { 
	    return 0;
	}
	p += 1;
	q += 1;
    }
    return 0;
}

