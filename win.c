#include <unistd.h>
#include "winx11.h"
//gcc -o win win.c -lX11
void Clicks(int index){
	printf("you click control index: %d\n",index);
}
int main(){
	struct wins w;
	struct wins *w1;
	XEvent *events;
	char sss[2080];
	char *cc;
	int i;
	int n;
	int nn;
	int nnn;
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
	ccs.click=Clicks;
	nnn=0;
	for (nn=0;nn<5;nn++){
		for(n=0;n<15;n++){
			sprintf(sss,"!%d",nnn);
			cc=newString(sss);
			addControl(n*40+10,nn*40+10,30,30,100,100,255,-1,cc,-1);
			nnn++;
		}	
	}
	events=getEvent(w1);
	while(events->type!=KeyPress){
		events=getEvent(w1);
	}
	freeLabel(w1);
	closeWindows(w1);
	closeX();
	return 0;
}
