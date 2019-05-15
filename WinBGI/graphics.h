#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#define far
#define huge
#define random(range) (rand() % (range))

enum colors { 
    BLACK, BLUE, GREEN, CYAN, RED, MAGENT, BROWN, LIGHTGRAY, DARKGRAY, 
    LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

enum write_modes { 
    COPY_PUT, XOR_PUT, OR_PUT, AND_PUT, NOT_PUT 
};
enum line_styles { 
    SOLID_LINE, DOTTED_LINE, CENTER_LINE, DASHED_LINE, USERBIT_LINE
};
enum fill_styles { 
    EMPTY_FILL, SOLID_FILL, LINE_FILL, LTSLASH_FILL, SLASH_FILL, BKSLASH_FILL,
    LTBKSLASH_FILL, HATCH_FILL, XHATCH_FILL, INTERLEAVE_FILL, WIDE_DOT_FILL, 
    CLOSE_DOT_FILL, USER_FILL
};
enum text_directions { 
    HORIZ_DIR, VERT_DIR
};
enum font_types { 
    DEFAULT_FONT, TRIPLEX_FONT, SMALL_FONT, SANSSERIF_FONT, GOTHIC_FONT 
};

#define LEFT_TEXT					0
#define CENTER_TEXT					1
#define RIGHT_TEXT					2
#define BOTTOM_TEXT					0
#define TOP_TEXT					2

#define NORM_WIDTH					1
#define THICK_WIDTH					3

#define DOTTEDLINE_LENGTH				2
#define CENTRELINE_LENGTH				4

#define USER_CHAR_SIZE					0
#define MAXCOLORS					15 

#define CLIP_ON						1
#define CLIP_OFF					0

#define TOP_ON						1
#define TOP_OFF					        0

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
#define VGAMAX                                          3

#define PC3270HI					0

#define IBM8514LO					0
#define IBM8514HI					1

typedef struct arccoordstype {
    int x;
    int y;
    int xstart;
    int ystart;
    int xend;
    int yend;
} arccoordstype;

typedef char fillpatterntype[8];

typedef struct fillsettingstype {
    int pattern;
    int color;
} fillsettingstype;

typedef struct linesettingstype {
    int linestyle;
    unsigned int upattern;
    int thickness;
} linesettingstype;

typedef struct palettetype {
    unsigned char size;
    signed char colors[16];
} palettetype;

typedef struct textsettingstype {
    int font;	
    int direction;  
    int charsize;
    int horiz;
    int vert;
} textsettingstype;

typedef struct viewporttype {
    int left;
    int top;
    int right;
    int bottom;
    int clip;
} viewporttype;


#ifndef NOT_USE_PROTOTYPES
#define PROTO(ARGS) ARGS
#else
#define PROTO(ARGS) ()
#endif

#if defined(__cplusplus) 
extern "C" {
#endif

//
// Setting this variable to 0 increase speed of drawing but
// correct redraw is not possible. By default this variable is initialized by 1
//
extern int bgiemu_handle_redraw;

//
// Default mode choosed by WinBGI if DETECT value is specified for 
// device parameter of initgraoh(). Default value is VGAMAX which
// cause creation of maximized window (resolution depends on display mode)
//
extern int bgiemu_default_mode;

void _graphfreemem PROTO((void *ptr, unsigned int size));
void* _graphgetmem PROTO((unsigned int size));
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
void getarccoords PROTO((arccoordstype *));
void getaspectratio PROTO((int *, int *));
int getbkcolor PROTO((void));
int getcolor PROTO((void));
palettetype* getdefaultpalette PROTO((void));
char* getdrivername PROTO((void));
void getfillpattern PROTO((char const *));
void getfillsettings PROTO((fillsettingstype *));
int getgraphmode PROTO((void));
void getimage PROTO((int, int, int, int, void *));
void getlinesettings PROTO((linesettingstype *));
int getmaxcolor PROTO((void));
int getmaxmode PROTO((void));
int getmaxx PROTO((void));
int getmaxy PROTO((void));
char* getmodename PROTO((int));
void getmoderange PROTO((int, int *, int *));
void getpalette PROTO((palettetype *));
int getpalettesize PROTO((void));
unsigned int getpixel PROTO((int, int));
void gettextsettings PROTO((textsettingstype *));
void getviewsettings PROTO((viewporttype *));
int getx PROTO((void));
int gety PROTO((void));
void graphdefaults PROTO((void));
char* grapherrormsg PROTO((int));
int graphresult PROTO((void));
unsigned int imagesize PROTO((int, int, int, int));
void initgraph PROTO((int *, int *, char const *));
int installuserdriver PROTO((char const *, int *));
int installuserfont PROTO((char const *));
void line PROTO((int, int, int, int));
void linerel PROTO((int, int));
void lineto PROTO((int, int));
void moverel PROTO((int, int));
void moveto PROTO((int, int));
void outtext PROTO((char const *));
void outtextxy PROTO((int, int, char const *));
void pieslice PROTO((int, int, int, int, int));
void putimage PROTO((int, int, void *, int));
void putpixel PROTO((int, int, int));
void rectangle PROTO((int, int, int, int));
int registerbgidriver PROTO((void *));
int registerbgifont PROTO((void *));
void restorecrtmode PROTO((void));
void sector PROTO((int, int, int, int, int, int));
void setactivepage PROTO((int));
void setallpalette PROTO((palettetype *));
void setaspectratio PROTO((int, int));
void setbkcolor PROTO((int));
void setcolor PROTO((int));
void setfillpattern PROTO((char const *, int));
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
int textheight PROTO((char const *));
int textwidth PROTO((char const *));
int getch PROTO((void));
int kbhit PROTO((void));		
void delay PROTO((unsigned msec));
void restorecrtmode PROTO((void));

#if defined(__cplusplus) 
};
#endif

#endif
