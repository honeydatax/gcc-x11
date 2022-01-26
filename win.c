#include <unistd.h>
#include "winx11.h"
//gcc -o win win.c -lX11
void onDraw(struct wins *w1){
	rects(w1,50,50,150,150,100,100,255);
}
int main(){
	struct wins w;
	struct wins *w1;
	XEvent *events;
	int i;
	int n;
	int nn;
	w1=&w;
	w1->x=10;
	w1->y=10;
	w1->w=640;
	w1->h=250;
	w1->border=1;
	w1->bords=0x1010FF;
	w1->color=RGB(0,0,255);
	w1->twins=0;
	if (startxs()==-1)exit(1);
	newWindows(w1);
	for (nn=0;nn<5;nn++){
		for(n=0;n<15;n++)addControl(n*40+10,nn*40+10,30,30,100,100,255,-1,NULL,-1);
	}
	events=getEvent(w1);
	while(events->type!=KeyPress){
		events=getEvent(w1);
	}
	closeWindows(w1);
	closeX();
	return 0;
}
