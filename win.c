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
		refresh(w1);
	i=getEvent();
	onDraw(w1);
	while(i!=2){
		if(i==1){
			onDraw(w1);
		}
		i=getEvent();
	}
	closeWindows(w1);
	closeX();
	return 0;
}
