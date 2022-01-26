#include <unistd.h>
#include "winx11.h"
//gcc -o win win.c -lX11
void Clicks(int index){
	struct wins w;
	struct wins *w1;
	XEvent *events;
	ccs.click=NULL;
	w1=&w;
	w1->x=100;
	w1->y=50;
	w1->w=400;
	w1->h=100;
	w1->border=5;
	w1->bords=0x1010FF;
	w1->color=RGB(150,150,255);
	w1->twins=1;
	newWindows(w1);
	events=msgbox(w1,"hello world");
	sleep(1);
	closeWindows(w1);	
	ccs.click=Clicks;
}
int main(int argc,char *argv[]){
	struct wins w;
	struct wins *w1;
	XEvent *events;
	char sss[2080];
	char *cc;
	int i;
	int t;
	int n;
	int nn;
	int nnn;
	w1=&w;
	w1->x=10;
	w1->y=10;
	w1->w=640;
	w1->h=400;
	w1->border=1;
	w1->bords=0x1010FF;
	w1->color=RGB(0,0,255);
	w1->twins=0;
	if (startxs()==-1)exit(1);
	newWindows(w1);
	ccs.click=Clicks;
	cc=newString("       msgbox...");
	addControl(8,8,600,16,100,100,255,-1,cc,-1);
	events=getEvent(w1);
	while(events->type!=KeyPress){
		events=getEvent(w1);
	}
	freeLabel(w1);
	closeWindows(w1);
	closeX();
	return 0;
}
