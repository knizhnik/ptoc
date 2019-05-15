#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "graphics.h"


void main(int argc, char **argv)
{
	int graphdriver, graphmode;

	graphdriver = X11;
	graphmode = X11_EGA;
	initgraph(&graphdriver, &graphmode, "");
	setviewport(0, 0, getmaxx() / 2, getmaxy() / 2, 0);
	rectangle(0, 0, getmaxx() / 2, getmaxy() / 2);
        outtextxy(275, 10, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	setusercharsize(5, 2, 7, 3);
	setviewport(0, 0, getmaxx() / 2, getmaxy() / 2, 0);
	line(0, 0, getmaxx(), getmaxy());
	getch();
	setviewport(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy(), 1);
	setlinestyle(DASHED_LINE, 0, THICK_WIDTH);
	line(0, 0, getmaxx(), getmaxy());
	setviewport(0, 0, getmaxx(), getmaxy(), 1);
	circle(150, 150, 200);
	setviewport(0, 0, 300, 300, 1);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	line(0, getmaxy(), getmaxx(), 0);
	setviewport(0, 0, getmaxx(), getmaxy(), 1);
	bar(0, 0, getmaxx(), getmaxy() / 10);
	setcolor(RED);
	outtextxy(10, 10, "HELLO WORLD");
	cleardevice();
	bar(0, 0, getmaxx(), getmaxy() / 10);
	setcolor(BLUE);
	outtextxy(50, 20, "HELLO WORLD");
	graphdefaults();
	circle(320, 240, 100);
	bar3d(10, 50, 30, 100, 20, 1);
	setviewport(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy(), 0);
	circle(0, 0, 20);
	setviewport(0, 0, 160, 120, 1);
	setcolor(GREEN);
	outtextxy(50, 100, "ABCDEFGHIJKLMONPQRSTUVWXYZ");
	getch();
}
