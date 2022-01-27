#include <unistd.h>
#include "winx11.h"
//gcc -o win win.c -lX11
int closewin0=0;
void Clicks(int index){
	closewin0=1;
	printf("you click control index: %d\n",index);
}
int main(){
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
	w1->h=250;
	w1->border=1;
	w1->bords=0x1010FF;
	w1->color=RGB(0,0,255);
	w1->twins=0;
	if (startxs()==-1)exit(1);
	newWindows(w1);
	nnn=0;
	for (nn=0;nn<5;nn++){
		for(n=0;n<15;n++){
			t=-1;
			if(nnn==55)t=0;
			sprintf(sss,"!%d",nnn);
			cc=newString(sss);
			addControl(n*40+10,nn*40+10,30,30,100,100,255,t,cc,-1,Clicks,0);
			nnn++;
		}	
	}
	while(closewin0!=1){
		events=getEvent(w1);
	}
	freeLabel(w1);
	closeWindows(w1);
	closeX();
	return 0;
}
