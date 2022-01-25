#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "fileList.h"

Display *display;
int dsp;
XEvent events;
struct wins{
	int x;
	int y;
	int w;
	int h;
	int border;
	long bords;
	int color;
	Window twins;
};
int startxs(void) {

	//Window w;
	//XEvent e;
  
	display=XOpenDisplay(NULL);
	if(display==NULL){
		return -1;
	}
 
   dsp=DefaultScreen(display);
   return dsp;
 }

void newWindows(struct wins *twins){
	twins->twins=XCreateSimpleWindow(display,RootWindow(display,dsp),twins->x,twins->y,twins->w,twins->h, twins->border,twins->bords,twins->color);
	XSelectInput(display, twins->twins, ExposureMask | KeyPressMask | ButtonPressMask);
	XMapWindow(display, twins->twins);
	Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
	XSetWMProtocols(display, twins->twins, &WM_DELETE_WINDOW, 1);  
}
XEvent *getEvent(){
	XNextEvent(display,&events);
	return &events;
}
void closeWindows(struct wins *twins){
	XDestroyWindow(display, twins->twins); 
}
void closeX(){
   XCloseDisplay(display);
}



