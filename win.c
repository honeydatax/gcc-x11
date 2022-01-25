#include <unistd.h>
#include "winx11.h"
//gcc -o win win.c -lX11
int main(){
	struct wins w;
	struct wins *w1;
	XEvent *events;
	w1=&w;
	w1->x=10;
	w1->y=10;
	w1->w=640;
	w1->h=250;
	w1->border=1;
	w1->bords=0x1010FF;
	w1->color=0xFF;
	w1->twins=-1;
	if (startxs()==-1)exit(1);
	newWindows(w1);
	events=getEvent();
	while(events->type!=KeyPress){
		events=getEvent();
	}
	closeWindows(w1);
	closeX();
	return 0;
}
