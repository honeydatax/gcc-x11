#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "fileList.h"
#define maxControls 100
struct control{
	int x;
	int y;
	int w;
	int h;
	char red;
	char green;
	char blue;
	int visible;
	char *strings;
	int pic; 
};
struct controls{
	int bmouses;
	int count;
	struct control cs[maxControls];
};
struct controls ccs;
Display *display;
int dsp;
XEvent events;
Colormap cmap;
XColor xcolour;
Window winss[35];
struct wins{
	int x;
	int y;
	int w;
	int h;
	int border;
	long bords;
	int color;
	int twins;
};
void rects(struct wins *twins,int x,int y, int w, int h,char r,int g,int b){
	xcolour.red =0x0100*((int)r);
	xcolour.green =0x0100*((int) g);
	xcolour.blue = 0x0100*((int)b);
	xcolour.flags = DoRed | DoGreen | DoBlue;
	Colormap cmap=XDefaultColormap(display,dsp);
	XAllocColor(display, cmap, &xcolour);
	XSetForeground(display, DefaultGC(display,dsp), xcolour.pixel);
	XFillRectangle(display,winss[twins->twins], DefaultGC(display,dsp),x, y, w, h);
}
void refresh(struct wins *twins){
	int n=0;
	for(n=0;n<ccs.count;n++)rects(twins,ccs.cs[n].x,ccs.cs[n].y,ccs.cs[n].w,ccs.cs[n].h,ccs.cs[n].red,ccs.cs[n].green,ccs.cs[n].blue);
}
int startxs(void) {
	ccs.count=0;
	display=XOpenDisplay(NULL);
	if(display==NULL){
		return -1;
	}
 
	dsp=DefaultScreen(display);
	Colormap cmap=XDefaultColormap(display,dsp);
	return dsp;
 }

void newWindows(struct wins *twins){
	winss[twins->twins]=XCreateSimpleWindow(display,RootWindow(display,dsp),twins->x,twins->y,twins->w,twins->h, twins->border,twins->bords,twins->color);
	XSelectInput(display, winss[twins->twins], ExposureMask | KeyPressMask | ButtonPressMask);
	XMapWindow(display, winss[twins->twins]);
	Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
	XSetWMProtocols(display, winss[twins->twins], &WM_DELETE_WINDOW, 1);  
}
XEvent *getEvent(struct wins *twins){
	int i=0;
	XNextEvent(display,&events);
	if(events.type==Expose){
		refresh(twins);
	}

	return &events;
}
void closeWindows(struct wins *twins){
	XDestroyWindow(display, winss[twins->twins]); 
}
void closeX(){
   XCloseDisplay(display);
}
int RGB(char red,char green , char blue){
	int rgbs=0x010000*((int)red)+0x0100*((int)green)+((int)blue);
	return rgbs;
}
int addControl(int x,int y,int w,int h,char red,char green,char blue,int visible,char *s,int pic){
	if (ccs.count>maxControls-2){
		return -1;
	}else{
		ccs.cs[ccs.count].x=x;
		ccs.cs[ccs.count].y=y;
		ccs.cs[ccs.count].w=w;
		ccs.cs[ccs.count].h=h;
		ccs.cs[ccs.count].red=red;
		ccs.cs[ccs.count].green=green;
		ccs.cs[ccs.count].blue=blue;
		ccs.cs[ccs.count].visible=visible;
		ccs.cs[ccs.count].strings=s;
		ccs.cs[ccs.count].pic=pic;
		ccs.count++;
	}
	return ccs.count-1;
}
