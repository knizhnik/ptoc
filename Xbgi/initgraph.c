/*
 * Revision 0.2  2012/12/06  12:30.00  GG
 * changed typedef struct {} name -> struct name + minor changes

 * $Id: initgraph.c,v 0.12 1994/04/07 00:48:00 king Exp king $
 * Initializes the graphics system.
 *
 * $Log: initgraph.c,v $
 * Revision 0.12  1994/04/07  00:48:00  king
 * Changed a few things to support the use of the backing store for X11R5
 * and higher.
 *
 * Revision 0.11  1993/12/13  23:46:03  king
 * Made changes for graphicsdriver and graphicsmode, which now also help
 * determine the window size.
 *
 * Revision 0.1  1993/12/10  00:39:08  king
 * Initial version.
 *
 */
#include "graphics.h"

Display *dpy;		/* the display */
char *display_name = NULL;
char *host;		/* the host */
GC gc;			/* main graphics context */
GC fill_gc;		/* graphics context for filling */
Window window;
Drawable drawable;
Pixmap *pages;		/* set of visual pages */
int active_page;
int visual_page;
Pixmap fill_pattern;    /* user defined fill patterns */
Region region;		/* used for clipping */
XRectangle xrectangle;
unsigned long background_pixel; 
Colormap cmap;

unsigned long plane_mask[4];
unsigned long plane_masks;

int bgiemu_handle_redraw;
int aspectratio_x;
int aspectratio_y;

XPoint CP;      	/* the current drawing position */
XPoint VPorigin;	/* the origin of the current viewport */

char *Colors[] = {
        "black", "blue", "green", "cyan", "red", "magenta", "brown",
        "light gray", "dark slate gray", "light blue", "light sea green",
        "light cyan", "light coral", "pale violet red", "yellow", "white"
};

char *Fonts[] = { /* GG */
        "fixed",     /* Default font */
        "12x24",     /* Triplex font */
        "6x12",      /* Small font */
        "12x24",     /* Sansserif font */
        "12x24"      /* Gothic font */
};

struct bgi_info *vga_palette;
struct textsettingstype txt_settings;
struct fillsettingstype fill_settings;
struct viewporttype view_settings;
struct arccoordstype last_arc;


void initgraph(int *graphdriver, int *graphmode, char *pathtodriver)
{
        Cursor x_hair;
        XColor color;
        XColor unused;
        XEvent report;
        XGCValues values;
        Screen *screen_ptr;
        int screen_num;
        int i;
        struct bgi_info *BGIptr;
        Pixmap *this_page;
	int gd;
	int gm;
	int width;
	int height;
	XSizeHints sizehints;
	XWMHints wmhints;
	XClassHint classhints;
	XTextProperty windowname;
	XTextProperty iconname;
	char *wname = "XBGI";
	unsigned long foreground_pixel;

#ifdef XlibSpecificationRelease
#define __XlibSpecificationRelease__
	XVisualInfo vTemplate;
	XVisualInfo *visualList;
	int visualsmatched;
	unsigned long valuemask;
	XSetWindowAttributes attributes;
#endif

/* create connection to display */
        if ((host = getenv("DISPLAY")) == NULL) {
                fprintf(stderr, "Cannot open display \n");
                exit(-1);
        }
/* open connection to display */
        if ((dpy = XOpenDisplay(host)) == NULL) {
                fprintf(stderr, "Cannot connect to X server \n");
                exit(-1);
        }

#ifdef __XDebug__
        XSynchronize(dpy, True);
#endif

        screen_num = DefaultScreen(dpy);
        screen_ptr = DefaultScreenOfDisplay(dpy);

#ifdef __XlibSpecificationRelease__
	if (XlibSpecificationRelease >= 5) {
		vTemplate.screen = screen_num;
		vTemplate.depth = DefaultDepth(dpy, screen_num);
		visualList = XGetVisualInfo(dpy, VisualScreenMask | 
					    VisualDepthMask, &vTemplate,
					    &visualsmatched);
	}
#endif

/* create a window based on the parameters passed to initgraph() */
	gd = *graphdriver;
	gm = *graphmode;
	switch (gd) {
		case CGA:
			height = 200;
			switch (gm) {
				case CGAC0:
				case CGAC1:
				case CGAC2:
				case CGAC3:
					width = 320;
					break;
				case CGAHI:
					width = 640;
					break;
				default:
					width = 320;
					break;
			}
			break;
		case MCGA:
			height = 200;
			switch (gm) {
				case MCGAC0:
				case MCGAC1:
				case MCGAC2:
				case MCGAC3:
					width = 320;
					break;
				case MCGAMED:
					width = 640;
					break;
				case MCGAHI:
					width = 640;
					height = 480;
					break;
				default:
					width = 320;
					break;
			}
			break;
		case EGA:
			width = 640;
			switch (gm) {
				case EGALO:
					height = 200;
					break;
				case EGAHI:
					height = 350;
					break;
				default:
					height = 350;
					break;
			}
			break;
		case EGA64:
			width = 640;
			switch (gm) {
				case EGA64LO:
					height = 200;
					break;
				case EGA64HI:
					height = 350;
					break;
				default:
					height = 350;
					break;
			}
			break;
		case EGAMONO:
			width = 640;
			height = 350;
			break;
		case HERCMONO:
			width = 720;
			height = 348;
			break;
		case ATT400:
			height = 200;
			switch (gm) {
				case ATT400C0:
				case ATT400C1:
				case ATT400C2:
				case ATT400C3:
					width = 320;
					break;
				case ATT400MED:
					width = 640;
					break;
				case ATT400HI:
					width = 640;
					height = 400;
					break;
				default:
					width = 320;
					break;
			}
			break;
		case VGA:
			width = 640;
			switch (gm) {
				case VGALO:
					height = 200;
					break;
				case VGAMED:
					height = 350;
					break;
				case VGAHI:
					height = 480;
					break;
				default:
					height = 480;
					break;
			}
			break;
		case PC3270:
			width = 720;
			height = 350;
			break;
		case IBM8514:
			switch (gm) {
				case IBM8514LO:
					width = 640;
					height = 480;
					break;
				case IBM8514HI:
					width = 1024;
					height = 768;
					break;
				default:
					width = 1024;
					height = 768;
					break;
			}
			break;	
	        case DETECT: 
		        gm = X11_VGA;
	        case X11:
		        switch (gm) {
				case X11_CGALO:
					width = 320;
					height = 200;
					break;
				case X11_CGAHI:
					width = 640;
					height = 200;
					break;
				case X11_EGA:
					width = 640;
					height = 350;
					break;
				case X11_VGA:
					width = 640;
					height = 480;
					break;
				case X11_HERC:
					width = 720;
					height = 348;
					break;
				case X11_PC3270:
					width = 720;
					height = 350;
					break;
				case X11_SVGALO:
					width = 800;
					height = 600;
					break;
				case X11_SVGAMED1:
					width = 1024;
					height = 768;
					break;
				case X11_SVGAMED2:
					width = 1152;
					height = 900;
					break;
				case X11_SVGAHI:
					width = 1280;
					height = 1024;
					break;
				case X11_USER:
				default:
					break;
			}
		default:
			break;
	}
				
/* do some internal stuff to track down the BGI particulars */
        vga_palette = (struct bgi_info *) malloc((MAXCOLORS + 1) * sizeof(struct bgi_info));
#ifdef ALLOCATE_COLOR_CELLS 
	{ 
#ifdef CREATE_NEW_COLORMAP
	    cmap = XCreateColormap(dpy, RootWindow(dpy, screen_num),  
				   DefaultVisual(dpy, screen_num), AllocNone);
	    XInstallColormap(dpy, cmap); 
#else
            cmap = DefaultColormap(dpy, screen_num);
#endif
	    XAllocColorCells(dpy, cmap, 0, plane_mask, 4, 
				  &background_pixel, 1);
	    plane_masks = plane_mask[0]|plane_mask[1]|plane_mask[2]|plane_mask[3];
	    for (i = 0, BGIptr = vga_palette; i <= MAXCOLORS; i++, BGIptr++) {
		unsigned long p = background_pixel 
		    | plane_mask[0] & (i << 31 >> 31)
		    | plane_mask[1] & (i << 30 >> 31)
		    | plane_mask[2] & (i << 29 >> 31)
		    | plane_mask[3] & (i << 28 >> 31);
                BGIptr->colour_index = i;
                BGIptr->colour_name = Colors[i];
                XStoreNamedColor(dpy, cmap, Colors[i], p,
				 (DoRed|DoGreen|DoBlue));
                BGIptr->pixel_value = p;
	    }
	    foreground_pixel = vga_palette[MAXCOLORS].pixel_value;
	}
#else
        cmap = DefaultColormap(dpy, screen_num);
        for (i = 0, BGIptr = vga_palette; i <= MAXCOLORS; i++, BGIptr++) {
                BGIptr->colour_index = i;
                BGIptr->colour_name = Colors[i];
                XAllocNamedColor(dpy, cmap, Colors[i], &color, &unused);
                BGIptr->pixel_value = color.pixel;
        }
	background_pixel = BlackPixel(dpy, screen_num);
	foreground_pixel = WhitePixel(dpy, screen_num);
#endif

#ifndef __XlibSpecificationRelease__
        window = XCreateSimpleWindow(dpy, RootWindow(dpy, screen_num), 0, 0,
                                     width, height, 1,
				     foreground_pixel,
                                     background_pixel);
#endif

/* set the hints used */
#ifdef __XlibSpecificationRelease__
	attributes.save_under = DoesSaveUnders(ScreenOfDisplay(dpy,
					       screen_num));
	attributes.backing_store = DoesBackingStore(ScreenOfDisplay(dpy,
						    screen_num));
	attributes.background_pixel = background_pixel;
	valuemask = CWBackingStore;
	window = XCreateWindow(dpy, RootWindow(dpy, screen_num), 0, 0, width,
			       height, 1, vTemplate.depth, InputOutput,
			       CopyFromParent, valuemask, &attributes);
#endif
	XSetWindowColormap(dpy, window, cmap);

	sizehints.flags = PMinSize | PMaxSize; /* GG */
	sizehints.min_width = width;
	sizehints.min_height = height;
	/* GG */
  	sizehints.max_width = width;
	sizehints.max_height = height;

	wmhints.initial_state = NormalState;
	wmhints.input = True;
	wmhints.flags = StateHint | InputHint;

	classhints.res_name = "";
	classhints.res_class = "";

	XStringListToTextProperty(&wname, 1, &windowname);
	XStringListToTextProperty(&wname, 1, &iconname);

	XSetWMProperties(dpy, window, &windowname, &iconname, NULL, 0,
			 &sizehints, &wmhints, &classhints);
        XSelectInput(dpy, window, ExposureMask | KeyPressMask |
                     ButtonPressMask | StructureNotifyMask);
/* display the window */
	XSetWindowBackground(dpy, window, background_pixel);
        XMapWindow(dpy, window);

#ifndef __XlibSpecificationRelease__
        for (;;) {
                XNextEvent(dpy, &report);
                if (report.type == Expose) {
                        while (XCheckMaskEvent(dpy, ExposureMask, &report));
                        break;
                }
        }
#endif

/* set the current drawing position to (0, 0) and the viewport origin */
        CP.x = 0;
        CP.y = 0;
        VPorigin.x = 0;
        VPorigin.y = 0;
/* initialise the graphics contexts */
        values.foreground = foreground_pixel;
        values.background = background_pixel;
        gc = XCreateGC(dpy, window, (GCForeground | GCBackground), &values);
        values.foreground = foreground_pixel;
        values.background = foreground_pixel;
        fill_gc = XCreateGC(dpy, window, (GCForeground | GCBackground), 
                            &values);
/* set cursor to X-hair */
        x_hair = XCreateFontCursor(dpy, XC_crosshair);
        XDefineCursor(dpy, window, x_hair);
/* allocate memory for the visual pages and fill them with black */
        pages = (Pixmap *) malloc(MAX_PAGES * sizeof(Pixmap));
        XSetForeground(dpy, gc, background_pixel);
        for (i = 0, this_page = pages; i < MAX_PAGES; i++, this_page++) {
                *this_page = XCreatePixmap(dpy, RootWindow(dpy, screen_num),
                                           width, height,
                                           XDefaultDepth(dpy, screen_num));
                XFillRectangle(dpy, *this_page, gc, 0, 0, width, height);
        }
        XSetForeground(dpy, gc, foreground_pixel);
/* set the default active and visual pages */
        active_page = 0;
        visual_page = 0;
        drawable = (Drawable) *(pages);
/* set the default text settings */
        txt_settings.font = 0;
        txt_settings.direction = HORIZ_DIR;
        txt_settings.charsize = 1;
        txt_settings.horiz = LEFT_TEXT;
        txt_settings.vert = TOP_TEXT;


	aspectratio_x = 10000;
	aspectratio_y = 10000;

/* set the default fill settings */
        fill_settings.pattern = SOLID_FILL;
        fill_settings.color = WHITE;

/* set the default viewport */
        region = XCreateRegion();
        xrectangle.x = 0;
        xrectangle.y = 0;
        xrectangle.width = width;
        xrectangle.height = height;
        XUnionRectWithRegion(&xrectangle, region, region);

        XFlush(dpy);
}
