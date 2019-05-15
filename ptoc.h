#ifndef __PTOC_H__
#define __PTOC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#define items(x) (sizeof(x)/sizeof(*(x)))

typedef int           integer;
typedef unsigned      cardinal; /* unsigned integer */
typedef float         real;

#if defined(TURBO_PASCAL) || defined(HP_PASCAL)
typedef unsigned       word; /* It should have the same size as integer */ 
typedef unsigned char  byte; 
#endif

#ifdef TURBO_PASCAL
typedef long           longint;
typedef signed char    shortint; 
typedef void*          pointer;
typedef const char*    asciiz;
#endif               

typedef unsigned char boolean; 
#define true          (1)
#define false         (0)

#define nil           NULL

#define EXTERN        extern

/*
 * Pascal runtime library headers
 */

#include "io.h"
#include "array.h"
#include "paslib.h"
#include "set.h"

#endif


