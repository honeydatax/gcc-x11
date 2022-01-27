#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "fileList.h"
#define maxControls 100
XEvent events;
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
	void (*click)();
	int form;
};
struct controls{
	int bmouses;
	int count;
	struct control cs[maxControls];
};
struct controls ccs;
Display *display;
int dsp;
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
int inside(int x,int y,int w,int h,int xx, int yy){
	int rets=0;
	if(xx>x && yy>y && xx<x+w && yy<y+h)return -1;
	return rets;
}
int scaner(struct wins *twins,int xx,int yy){
	int rets=-1;
	int n=0;
	for(n=0;n<ccs.count;n++){
		rets=inside(ccs.cs[n].x,ccs.cs[n].y,ccs.cs[n].w,ccs.cs[n].h,xx,yy);
		if(rets!=0 && ccs.cs[n].visible!=0 && ccs.cs[n].form==twins->twins)return n;
	}
	return -1;

}
void labels(struct wins *twins,int x,int y,char *msg){
	xcolour.red =0;//0xff00;
	xcolour.green =0;//0xff00;
	xcolour.blue =0; //0xff00;
	xcolour.flags = DoRed | DoGreen | DoBlue;
	Colormap cmap=XDefaultColormap(display,dsp);
	XAllocColor(display, cmap, &xcolour);
	XSetForeground(display, DefaultGC(display,dsp), xcolour.pixel);
	if(msg!=NULL)XDrawString(display,winss[twins->twins], DefaultGC(display,dsp), x, y+12, msg, strlen(msg));
}
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
	for(n=0;n<ccs.count;n++){
		if(ccs.cs[n].visible!=0 && ccs.cs[n].form==twins->twins){
			rects(twins,ccs.cs[n].x,ccs.cs[n].y,ccs.cs[n].w,ccs.cs[n].h,ccs.cs[n].red,ccs.cs[n].green,ccs.cs[n].blue);
			labels(twins,ccs.cs[n].x,ccs.cs[n].y,ccs.cs[n].strings);
		}
	}
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
	int ii=0;
	XNextEvent(display,&events);
	if(events.type==Expose){
		refresh(twins);
	}
	ii=(events.xbutton.button & 1);
	if(ii==1 && ccs.bmouses==0){
		ccs.bmouses=0;
		i=scaner(twins,events.xbutton.x,events.xbutton.y);
		if (i!=-1){
			if(ccs.cs[i].click!=NULL)(*ccs.cs[i].click)(i);
		}
	}
	if(ii==0) {
		ccs.bmouses=0;
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
int addControl(int x,int y,int w,int h,char red,char green,char blue,int visible,char *s,int pic,void (*click)(),int form){
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
		ccs.cs[ccs.count].click=click;
		ccs.cs[ccs.count].form=form;
		ccs.count++;
	}
	return ccs.count-1;
}
void freeLabel(struct wins *twins){
	int n=0;
	for(n=0;n<ccs.count;n++){
			frees(ccs.cs[n].strings);

	}
}
XEvent *msgbox(struct wins *twins,char *s){
	XEvent event;
	int i=0;
	int ii;
	event.type=0;
	ii=0;
	while(ii!=1){
		XNextEvent(display,&event);
		if(event.type==Expose){
			labels(twins,10,10,s);
		}
		if((event.xbutton.button)!=0 && (inside(0,0,twins->w,twins->h,event.xbutton.x,event.xbutton.y))!=0)ii=1;
	}
}
