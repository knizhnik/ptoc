/*
 * $Id: graphics.h,v 0.1 1993/12/12 22:18:54 king Exp king $
 *	Reconstructed version of Borland's graphics.h file.
 *
 * $Log: graphics.h,v $
 * Revision 0.1  1993/12/12  22:18:54  king
 * Initial version.
 * Revision 0.2  2012/12/06  12:30.00  GG
 * changed typedef struct {} name -> struct name
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef __EMX__
#include <float.h>
#define usleep(t) _sleep2( ((t)+500) / 1000 )
#endif
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>

#ifndef __BGI_INCLUDED_
#define __BGI_INCLUDED_

/* 2012-11-27: fix */
/* #define ALLOCATE_COLOR_CELLS 1 */
#define CREATE_NEW_COLORMAP

#define MAXLINELENGTH					256
/* GG - added */
#define random(range) (rand() % (range))
void delay (int);

/* -------------------------------------------------------------------------- */

/* BORLAND MIMICS */


#define BLACK                                           0
#define BLUE                                            1
#define GREEN                                           2
#define CYAN                                            3
#define RED                                             4
#define MAGENTA                                         5
#define BROWN                                           6
#define LIGHTGRAY                                       7
#define DARKGRAY                                        8
#define LIGHTBLUE                                       9
#define LIGHTGREEN                                      10
#define LIGHTCYAN                                       11
#define LIGHTRED                                        12
#define LIGHTMAGENTA                                    13
#define YELLOW                                          14
#define WHITE                                           15

#define CGA_LIGHTGREEN					1
#define CGA_LIGHTRED					2
#define CGA_YELLOW					3

#define CGA_LIGHTCYAN					1
#define CGA_LIGHTMAGENTA				2
#define CGA_WHITE					3

#define CGA_GREEN					1
#define CGA_RED						2
#define CGA_BROWN					3

#define CGA_CYAN					1
#define CGA_MAGENTA					2
#define CGA_LIGHTGRAY					3

#define EGA_BLACK					0
#define EGA_BLUE					1
#define EGA_GREEN					2
#define EGA_CYAN					3
#define EGA_RED						4
#define EGA_MAGENTA					5
#define EGA_LIGHTGRAY					7
#define EGA_BROWN					20
#define EGA_DARKGRAY					56
#define EGA_LIGHTBLUE					57
#define EGA_LIGHTGREEN					58
#define EGA_LIGHTCYAN					59
#define EGA_LIGHTRED					60
#define EGA_LIGHTMAGENTA				61
#define EGA_YELLOW					62
#define EGA_WHITE					63

#define MAXCOLORS					15

#define EMPTY_FILL					0
#define SOLID_FILL					1
#define LINE_FILL					2
#define LTSLASH_FILL					3
#define SLASH_FILL					4
#define BKSLASH_FILL					5
#define LTBKSLASH_FILL					6
#define HATCH_FILL					7
#define XHATCH_FILL					8
#define INTERLEAVE_FILL					9
#define WIDE_DOT_FILL					10
#define CLOSE_DOT_FILL					11
#define USER_FILL					12

#define SOLID_LINE					0
#define DOTTED_LINE					1
#define CENTER_LINE					2
#define DASHED_LINE					3
#define USERBIT_LINE					4

#define NORM_WIDTH					1
#define THICK_WIDTH					3

#define DOTTEDLINE_LENGTH				2
#define CENTRELINE_LENGTH				4
#define DASHEDLINE_LENGTH				2

#define DEFAULT_FONT					0
#define TRIPLEX_FONT					1
#define SMALL_FONT					2
#define SANSSERIF_FONT					3
#define GOTHIC_FONT					4

#define HORIZ_DIR					0
#define VERT_DIR					1

#define LEFT_TEXT					0
#define CENTER_TEXT					1
#define RIGHT_TEXT					2
#define BOTTOM_TEXT					0
#define TOP_TEXT					2

#define COPY_PUT					0
#define XOR_PUT						1
#define OR_PUT						2
#define AND_PUT						3
#define NOT_PUT						4

#define MAX_PAGES					4

struct arccoordstype {
	int x;
	int y;
	int xstart;
	int ystart;
	int xend;
	int yend;
};

struct date {
	int da_year;
	int da_day;
	int da_mon;
};

struct fillsettingstype {
	int pattern;
	int color;
};

struct linesettingstype {
	int linestyle;
	unsigned int upattern;
	int thickness;
};

struct palettetype {
	unsigned char size;
	signed char colors[MAXCOLORS + 1];
};

struct textsettingstype {
	int font;
	int direction;
	int charsize;
	int horiz;
	int vert;
};

struct viewporttype {
	int left;
	int top;
	int right;
	int bottom;
	int clip;
};

struct bgi_info {
	int colour_index;
	char *colour_name;
	unsigned long pixel_value;
};


extern unsigned long background_pixel; 
extern Display *dpy;
extern char *display_name;
extern GC gc;
extern GC fill_gc;
extern Window window;
extern Drawable drawable;
extern Pixmap *pages;
extern int active_page;
extern int visual_page;
extern Pixmap fill_pattern;
extern Region region;
extern XRectangle xrectangle;
extern Colormap cmap;
extern int aspectratio_x, aspectratio_y; 
extern XPoint CP;
extern XPoint VPorigin;

extern char *Colors[];

extern char *Fonts[];

extern int dash_list_length[];
extern unsigned char dottedline[DOTTEDLINE_LENGTH];
extern unsigned char centreline[CENTRELINE_LENGTH];
extern unsigned char dashedline[DASHEDLINE_LENGTH];
extern unsigned char *dash_list[];

extern unsigned long plane_mask[4];
extern unsigned long plane_masks;

extern struct bgi_info *vga_palette;
extern struct textsettingstype txt_settings;
extern struct fillsettingstype fill_settings;
extern struct viewporttype view_settings;
extern struct arccoordstype last_arc;

typedef struct {
    int    width;
    int    height;
    Pixmap pixmap;
} bgi_image; 


/* The following prototype processing was suggested by Juki Virtanen, 
 * jtv@hut.fi
 */
#ifndef PROTO
#if defined(USE_PROTOTYPES) ? USE_PROTOTYPES : defined(__STDC__)
#define PROTO(ARGS)					ARGS
#else
#define PROTO(ARGS)					()
#endif
#endif

#if defined(__cplusplus) || defined(c_plusplus)

#ifndef PROTO
#define PROTO(ARGS)					ARGS
#endif

	extern "C" {
#endif
		void _graphfreemem PROTO((void *ptr, unsigned int size));
		void *_graphgetmem PROTO((unsigned int size));
		void arc PROTO((int, int, int, int, int));
		void bar PROTO((int, int, int, int));
		void bar3d PROTO((int, int, int, int, int, int));
		void circle PROTO((int, int, int));
		void cleardevice PROTO((void));
		void clearviewport PROTO((void));
		void closegraph PROTO((void));
		void detectgraph PROTO((int *, int *));
		void drawpoly PROTO((int, int *));
		void ellipse PROTO((int, int, int, int, int, int));
		void fillellipse PROTO((int, int, int, int));
		void fillpoly PROTO((int, int *));
		void floodfill PROTO((int, int, int));
		void getarccoords PROTO((struct arccoordstype *));
		void getaspectratio PROTO((int *, int *));
		int getbkcolor PROTO((void));
		int getcolor PROTO((void));
		struct palettetype *getdefaultpalette PROTO((void));
		char *getdrivername PROTO((void));
		void getfillpattern PROTO((char *));
		void getfillsettings PROTO((struct fillsettingstype *));
		int getgraphmode PROTO((void));
		void getimage PROTO((int, int, int, int, void *));
		void getlinesettings PROTO((struct linesettingstype *));
		int getmaxcolor PROTO((void));
		int getmaxmode PROTO((void));
		int getmaxx PROTO((void));
		int getmaxy PROTO((void));
		char *getmodename PROTO((int));
		void getmoderange PROTO((int, int *, int *));
		void getpalette PROTO((struct palettetype *));
		int getpalettesize PROTO((void));
		unsigned int getpixel PROTO((int, int));
		void gettextsettings PROTO((struct textsettingstype *));
		void getviewsettings PROTO((struct viewporttype *));
		int getx PROTO((void));
		int gety PROTO((void));
		void graphdefaults PROTO((void));
		char *grapherrormsg PROTO((int));
		int graphresult PROTO((void));
		unsigned int imagesize PROTO((int, int, int, int));
		void initgraph PROTO((int *, int *, char *));
		int installuserdriver PROTO((char *, int *));
		int installuserfont PROTO((char *));
		void line PROTO((int, int, int, int));
		void linerel PROTO((int, int));
		void lineto PROTO((int, int));
		void moverel PROTO((int, int));
		void moveto PROTO((int, int));
		void outtext PROTO((char *));
		void outtextxy PROTO((int, int, char *));
		void pieslice PROTO((int, int, int, int, int));
		void putimage PROTO((int, int, void *, int));
		void putpixel PROTO((int, int, int));
		void rectangle PROTO((int, int, int, int));
		int registerbgidriver PROTO((void *));
		int registerbgifont PROTO((void *));
		void restorecrtmode PROTO((void));
		void sector PROTO((int, int, int, int, int, int));
		void setactivepage PROTO((int));
		void setallpalette PROTO((struct palettetype *));
		void setaspectratio PROTO((int, int));
		void setbkcolor PROTO((int));
		void setcolor PROTO((int));
		void setfillpattern PROTO((char *, int));
		void setfillstyle PROTO((int, int));
		unsigned int setgraphbufsize PROTO((unsigned int));
		void setgraphmode PROTO((int));
		void setlinestyle PROTO((int, unsigned int, int));
		void setpalette PROTO((int, int));
		void setrgbpalette PROTO((int, int, int, int));
		void settextjustify PROTO((int, int));
		void settextstyle PROTO((int, int, int));
		void setusercharsize PROTO((int, int, int, int));
		void setviewport PROTO((int, int, int, int, int));
		void setvisualpage PROTO((int));
		void setwritemode PROTO((int));
		int textheight PROTO((char *));
		int textwidth PROTO((char *));
/* -------------------------------------------------------------------------- */
		int getch PROTO((void));
		void get_date PROTO((struct date *));
		int kbhit PROTO((void));

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

/* -------------------------------------------------------------------------- */

enum graphics_errors {
	grOk = 0,
	grNoInitGraph = -1,
	grNotDetected = -2,
	grFileNotFound = -3,
	grInvalidDriver	= -4,
	grNoLoadMem = -5,
	grNoScanMem = -6,
	grNoFloodMem = -7,
	grFontNotFound = -8,
	grNoFontMem = -9,
	grInvalidMode =	-10,
	grError = -11,
	grIOerror = -12,
	grInvalidFont = -13,
	grInvalidFontNum = -14,
	grInvalidDeviceNum = -15,
	grInvalidVersion = -18
};


/* Graphics drivers constants, includes X11 which is particular to XBGI. */
#define DETECT						0
#define CGA						1
#define MCGA						2
#define EGA						3
#define EGA64						4
#define EGAMONO						5
#define IBM8514						6
#define HERCMONO					7
#define ATT400						8
#define VGA						9
#define PC3270						10
#define X11						11


/* Graphics modes constants. */
#define CGAC0						0
#define CGAC1						1
#define CGAC2						2
#define CGAC3						3
#define CGAHI						4

#define MCGAC0						0
#define MCGAC1						1
#define MCGAC2						2
#define MCGAC3						3
#define MCGAMED						4
#define MCGAHI						5

#define EGALO						0
#define EGAHI						1

#define EGA64LO						0
#define EGA64HI						1

#define EGAMONOHI					3

#define HERCMONOHI					0

#define ATT400C0					0
#define ATT400C1					1
#define ATT400C2					2
#define ATT400C3					3
#define ATT400MED					4
#define ATT400HI					5

#define VGALO						0
#define VGAMED						1
#define VGAHI						2

#define PC3270HI					0

#define IBM8514LO					0
#define IBM8514HI					1

#define X11_CGALO					0
#define X11_CGAHI					1
#define X11_EGA						2
#define X11_VGA						3
#define X11_HERC					4
#define X11_PC3270					5
#define X11_SVGALO					6
#define X11_SVGAMED1					7
#define X11_SVGAMED2					8
#define X11_SVGAHI					9
#define X11_USER					10

/* added, GG */
#define KEY_HOME	80
#define KEY_LEFT	81
#define KEY_UP		82
#define KEY_RIGHT	83
#define KEY_DOWN	84
#define KEY_PGUP	85
#define KEY_PGDN	86
#define KEY_END		87
#define KEY_INSERT	99
#define KEY_DELETE	-1
#define KEY_F1		-66
#define KEY_F2		-65
#define KEY_F3		-64
#define KEY_F4		-63
#define KEY_F5		-62
#define KEY_F6		-61
#define KEY_F7		-60
#define KEY_F8		-59
#define KEY_F9		-58
#define KEY_F10		-57
#define KEY_F11		-56
#define KEY_F12		-57
#define KEY_LEFT_CTRL	-29
#define KEY_RIGHT_CTRL	-28
#define KEY_LEFT_SHIFT	-31
#define KEY_RIGHT_SHIFT	-30
#define KEY_LEFT_ALT	-23
#define KEY_LEFT_WIN	-21
#define KEY_RIGHT_WIN	-20
#define KEY_ALT_GR	3
#define KEY_PAUSE	19
#define KEY_SCR_LOCK	20

#endif	/* __BGI_INCLUDED */
