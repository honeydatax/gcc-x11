#include <unistd.h>
#include "winx11.h"
//gcc -o win win.c -lX11
int closewin0=0;
int buttonSize=120;
void closew(int index){
	closewin0=1;
	printf("you click control index: %d\n",index);
}
void Clicks(int index){
	struct wins w;
	struct wins *w1;
	char *c;
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
	setCaption(w1,"get a string","input X");
	c=inputbox(w1,"");
	print(c);
	frees(c);
	closeWindows(w1);	
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
	setCaption(w1,"inputbox string exemple","input X");
	addControl(0*(buttonSize+10)+10,10,buttonSize,20,100,100,255,1," close this window",-1,closew,0);
	addControl(1*(buttonSize+10)+10,10,buttonSize,20,100,100,255,1," show inputbox",-1,Clicks,0);
	events=getEvent(w1);
	while(closewin0!=1){
		events=getEvent(w1);
	}
	closeWindows(w1);
	closeX();
	return 0;
}
