#ifndef __GRAPH_H__
#define __GRAPH_H__ 

enum Colors { 
    black, blue, green, cyan, red, magent, brown, lightgray, darkgray, 
    lightblue, lightgreen, lightcyan, lightred, lightmagenta, yellow, white
};

enum WriteModes { 
    copyput, xorput, orput, andput, notput };
enum LineStyles { 
    solidln, dottedln, centerln, dashedln, userbitln
};
enum FillStyles { 
    emptyfill, solidfill, linefill, ltslashfill, slashfill, bkslashfill,
    ltbkslashfill, hatchfill, xhatchfill, interleavefill, widedotfill, 
    closedotfill, userfill
};
enum TextDirections { 
    horizdir, vertdir 
};
enum FontTypes { 
    defaultfont, triplexfont, smallfont, sansseriffont, gothicfont 
};

#define normwidth					1
#define thickwidth					3

#define dottedlinelength				2
#define centrelinelength				4

#define usercharsize					0
#define maxcolors					15

#define lefttext					0
#define centertext					1
#define righttext					2
#define bottomtext					0
#define toptext						2

#define clipon                                          1
#define clipoff                                         0

#define topon                                           1
#define topoff                                          0

enum GraphicsErrors {
	grok = 0,
	grnoinitgraph = -1,
	grnotdetected = -2,
	grfilenotfound = -3,
	grinvaliddriver	= -4,
	grnoloadmem = -5,
	grnoscanmem = -6,
	grnofloodmem = -7,
	grfontnotfound = -8,
	grnofontmem = -9,
	grinvalidmode =	-10,
	grerror = -11,
	grioerror = -12,
	grinvalidfont = -13,
	grinvalidfontnum = -14,
	grinvaliddevicenum = -15,
	grinvalidversion = -18
};


/* graphics drivers constants, includes x11 which is particular to xbgi. */
#define detect						0
#define cga						1
#define mcga						2
#define ega						3
#define ega64						4
#define egamono						5
#define ibm8514						6
#define hercmono					7
#define att400						8
#define vga						9
#define pc3270						10

/* graphics modes constants. */
#define cgac0						0
#define cgac1						1
#define cgac2						2
#define cgac3						3
#define cgahi						4

#define mcgac0						0
#define mcgac1						1
#define mcgac2						2
#define mcgac3						3
#define mcgamed						4
#define mcgahi						5

#define egalo						0
#define egahi						1

#define ega64lo						0
#define ega64hi						1

#define egamonohi					3

#define hercmonohi					0

#define att400c0					0
#define att400c1					1
#define att400c2					2
#define att400c3					3
#define att400med					4
#define att400hi					5

#define vgalo						0
#define vgamed						1
#define vgahi						2
#define vgamax						3

#define pc3270hi   				        0
#define ibm8514lo  					0
#define ibm8514hi  					1

typedef struct {
    int x;
    int y;
    int xstart;
    int ystart;
    int xend;
    int yend;
} arccoordstype;

struct fillpatterntype { 
    char pattern[8];
};

struct pointtype { 
    int x;
    int y;
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
    signed char colors[16];
};

struct textsettingstype {
    int font;	
    int direction;  
    int charsize;
    int horiz;
    int vert;
};

struct viewporttype {
    int x1;
    int y1;
    int x2;
    int y2;
    int clip;
};

extern "C" {

extern int bgiemu_handle_redraw;

void arc(int, int, int, int, int);
void bar(int, int, int, int);
void bar3d(int, int, int, int, int, int);
void circle(int, int, int);
void cleardevice(void);
void clearviewport(void);
void closegraph(void);
void detectgraph(int&, int&);
void drawpoly(int, pointtype*);
void ellipse(int, int, int, int, int, int);
void fillellipse(int, int, int, int);
void fillpoly(int, pointtype*);
void floodfill(int, int, int);
void getarccoords(arccoordstype&);
void getaspectratio(word&, word&);
int getbkcolor(void);
int getcolor(void);
palettetype* getdefaultpalette();
char* getdrivername(void);
void getfillpattern(fillpatterntype&);
void getlinesettings(linesettingstype&);
void getfillsettings(fillsettingstype&);
int getgraphmode(void);
void getimage(int, int, int, int, void*);
int getmaxcolor(void);
int getmaxmode(void);
int getmaxx(void);
int getmaxy(void);
char* getmodename(int);
void getpalette(palettetype&);
int getpalettesize(void);
unsigned int getpixel(int, int);
void gettextsettings(textsettingstype&);
void getviewsettings(viewporttype&);
int getx(void);
int gety(void);
void graphdefaults(void);
char* grapherrormsg(int);
int graphresult(void);
unsigned int imagesize(int, int, int, int);
void initgraph(int* device, int* mode, char const*);
void line(int, int, int, int);
void linerel(int, int);
void lineto(int, int);
void moverel(int, int);
void moveto(int, int);
void outtext(char const*);
void outtextxy(int, int, char const*);
void pieslice(int, int, int, int, int);
void putimage(int, int, void*, int);
void putpixel(int, int, int);
void rectangle(int, int, int, int);
void restorecrtmode(void);
void sector(int, int, int, int, int, int);
void setactivepage(int);
void setallpalette(palettetype const&);
void setaspectratio(int, int);
void setbkcolor(int);
void setcolor(int);
void setfillpattern(fillpatterntype const&, int);
void setfillstyle(int, int);
void setgraphmode(int);
void setlinestyle(int, unsigned int, int);
void setpalette(int, int);
void setrgbpalette(int, int, int, int);
void settextjustify(int, int);
void settextstyle(int, int, int);
void setusercharsize(int, int, int, int);
void setviewport(int, int, int, int, int);
void setvisualpage(int);
void setwritemode(int);
int textheight(char const*);
int textwidth(char const*);
int getch(void);
int kbhit(void);		
void delay(int msec);

};

inline void getdefaultpalette(palettetype& pal) { 
    pal = *getdefaultpalette(); 
}
inline int  readkey() { 
    return getch(); 
}
inline int  keypressed() { 
    return kbhit(); 
}
inline void outtext(char ch) { 
    char str[2] = {ch, '\0'}; 
    outtext(str); 
}
inline void outtextxy(int x, int y, char ch) { 
    char str[2] = {ch, '\0'}; 
    outtextxy(x, y, str); 
}
inline int textheight(char ch) { 
    char str[2] = {ch, '\0'}; 
    return textheight(str);
}
inline int textwidth(char ch) {
    char str[2] = {ch, '\0'}; 
    return textwidth(str);
}

inline void initgraph(int& device, int& mode, char const* driver, 
		      bool handle_redraw = true)
{
    bgiemu_handle_redraw = handle_redraw;
    initgraph(&device, &mode, driver);
}

/* Definitions for case preserve conversion mode */
#define Black black
#define Blue blue
#define Green green
#define Cyan cyan
#define Red red
#define Magent magent
#define Brown brown
#define LightGray lightgray
#define DarkGray  darkgray 
#define LightBlue lightblue
#define LightGreen lightgreen
#define LightCyan lightcyan
#define LightRed lightred
#define LightMagenta lightmagenta
#define Yellow yellow
#define White white

#define CopyPut copyput
#define XORPut xorput 
#define ORPut orput
#define ANTPut andput
#define NOTPut notput
 
#define SolidLn solidln
#define DottedLn dottedln
#define CenterLn centerln
#define DashedLn dashedln
#define UserBitLn userbitln

#define EmptyFill emptyfill
#define SolidFill solidfill
#define LineFill linefill
#define LtSlashFill ltslashfill
#define SlashFill slashfill
#define BkSlashFill bkslashfill
#define LtBkSlashFill ltbkslashfill
#define HatchFill hatchfill
#define XHatchFill xhatchfill
#define InterleaveFill interleavefill
#define WideDotFill  widedotfill
#define CloseDotFill closedotfill
#define UserFill userfill

#define HorizDir horizdir
#define VertDir  vertdir 

#define DefaultFont defaultfont
#define TriplexFont triplexfont
#define SmallFont smallfont
#define SansSerifFont sansseriffont
#define GothicFont  gothicfont 

#define NormWidth normwidth
#define ThickWidth thickwidth

#define UserCharSize usercharsize
#define MaxColors maxcolors 

#define LeftText lefttext
#define CenterText centertext
#define RightText righttext
#define BottomText bottomtext
#define TopText toptext

#define ClipOn clipon
#define ClipOff clipoff

#define TopOn topon
#define TopOff topoff

#define ArcCoordsType arccoordstype
#define FillPatternType fillpatterntype
#define PointType pointtype

#define FillSettingsType fillsettingstype
#define LineSettingsType linesettingstype
#define PaletteType palettetype 
#define TextSettingsType textsettingstype
#define ViewPortType viewporttype

#define Arc(_1,_2,_3,_4,_5) arc(_1,_2,_3,_4,_5)
#define Bar(_1,_2,_3,_4) bar(_1,_2,_3,_4)
#define Bar3D(_1,_2,_3,_4,_5,_6) bar3d(_1,_2,_3,_4,_5,_6)
#define Circle(_1,_2,_3) circle(_1,_2,_3)
#define ClearDevice() cleardevice()
#define ClearViewPort() clearviewport()
#define CloseGraph() closegraph()
#define DetectGraph(_1,_2) detectgraph(_1,_2)
#define DrawPoly(_1,_2) drawpoly(_1,_2)
#define Ellipse(_1,_2,_3,_4,_5,_6) ellipse(_1,_2,_3,_4,_5,_6)
#define FillEllipse(_1,_2,_3,_4) fillellipse(_1,_2,_3,_4)
#define FillPoly(_1,_2) fillpoly(_1,_2)
#define FloodFill(_1,_2,_3) floodfill(_1,_2,_3)
#define GetArcCoords(_1) getarccoords(_1)
#define GetAspectRatio(_1,_2) getaspectratio(_1,_2)
#define GetBkColor() getbkcolor()
#define GetColor() getcolor()
#define GetDefaultPalette(_1) getdefaultpalette(_1)
#define GetDriverName() getdrivername()
#define GetFillPattern(_1) getfillpattern(_1)
#define GetLineSettings(_1) getlinesettings(_1)
#define GetFillSettings(_1) getfillsettings(_1)
#define GetGraphMode() getgraphmode()
#define GetImage(_1,_2,_3,_4,_5) getimage(_1,_2,_3,_4,_5)
#define GetMaxColor() getmaxcolor()
#define GetMaxMode() getmaxmode()
#define GetMaxX() getmaxx()
#define GetMaxY() getmaxy()
#define GetModeName(_1) getmodename(_1)
#define GetPalette(_1) getpalette(_1)
#define GetPaletteSize() getpalettesize()
#define GetPixel(_1,_2) getpixel(_1,_2)
#define GetTextSettings(_1) gettextsettings(_1)
#define GetViewSettings(_1) getviewsettings(_1)
#define GetX() getx()
#define GetY() gety()
#define GraphDefaults() graphdefaults()
#define GraphErrorMsg(_1) grapherrormsg(_1)
#define GraphResult() graphresult()
#define ImageSize(_1,_2,_3,_4) imagesize(_1,_2,_3,_4)
#define InitGraph(_1,_2,_3) initgraph(_1,_2,_3)
#define Line(_1,_2,_3,_4) line(_1,_2,_3,_4)
#define LineRel(_1,_2) linerel(_1,_2)
#define LineTo(_1,_2) lineto(_1,_2)
#define MoveRel(_1,_2) moverel(_1,_2)
#define MoveTo(_1,_2) moveto(_1,_2)
#define OutText(_1) outtext(_1)
#define OutTextXY(_1,_2,_3) outtextxy(_1,_2,_3)
#define PieSlice(_1,_2,_3,_4,_5) pieslice(_1,_2,_3,_4,_5)
#define PutImage(_1,_2,_3,_4) putimage(_1,_2,_3,_4)
#define PutPixel(_1,_2,_3) putpixel(_1,_2,_3)
#define Rectangle(_1,_2,_3,_4) rectangle(_1,_2,_3,_4)
#define RestoreCrtMode() restorecrtmode()
#define Sector(_1,_2,_3,_4,_5,_6) sector(_1,_2,_3,_4,_5,_6)
#define SetActivePage(_1) setactivepage(_1)
#define SetAllPalette(_1) setallpalette(_1)
#define SetAspectRatio(_1,_2) setaspectratio(_1,_2)
#define SetBkColor(_1) setbkcolor(_1)
#define SetColor(_1) setcolor(_1)
#define SetFillPattern(_1,_2) setfillpattern(_1,_2)
#define SetFillStyle(_1,_2) setfillstyle(_1,_2)
#define SetGraphMode(_1) setgraphmode(_1)
#define SetLineStyle(_1,_2,_3) setlinestyle(_1,_2,_3)
#define SetPalette(_1,_2) setpalette(_1,_2)
#define SetRgbPalette(_1,_2,_3,_4) setrgbpalette(_1,_2,_3,_4)
#define SetTextJustify(_1,_2) settextjustify(_1,_2)
#define SetTextStyle(_1,_2,_3) settextstyle(_1,_2,_3)
#define SetUserCharSize(_1,_2,_3,_4) setusercharsize(_1,_2,_3,_4)
#define SetViewPort(_1,_2,_3,_4,_5) setviewport(_1,_2,_3,_4,_5)
#define SetVisualPage(_1) setvisualpage(_1)
#define SetWriteMode(_1) setwritemode(_1)
#define TextHeight(_1) textheight(_1)
#define TextWidth(_1) textwidth(_1)
#define Delay(_1) delay(_1)
#define ReadKey() readkey()
#define KeyPressed() keypressed()

#endif
