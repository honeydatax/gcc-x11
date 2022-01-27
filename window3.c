#include <unistd.h>
#include "winx11.h"
//gcc -o win win.c -lX11
int closewin0=0;
int closewin1=0;
int buttonSize=120;
void Clicks(int index){
	struct wins w;
	struct wins *w1;
	XEvent *events;
	w1=&w;
	w1->x=100;
	w1->y=50;
	w1->w=400;
	w1->h=100;
	w1->border=5;
	w1->bords=0x1010FF;
	w1->color=RGB(150,150,255);
	w1->twins=2;
	newWindows(w1);
	events=msgbox(w1,"hello world");
	closeWindows(w1);	
}
void closew(int index){
	closewin0=1;
	printf("you click control index: %d\n",index);
}
void closew1(int index){
	closewin1=1;
	printf("you click control index: %d\n",index);
}
void showw1(int index){
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
	printf("you click control index: %d\n",index);
	w1=&w;
	w1->x=10;
	w1->y=10;
	w1->w=640;
	w1->h=250;
	w1->border=5;
	w1->bords=0x1010FF;
	w1->color=RGB(0,0,255);
	w1->twins=1;
	newWindows(w1);
	nnn=0;
	closewin1=0;
	while(closewin1!=1){
		events=getEvent(w1);
	}	
	closeWindows(w1);
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
	//control windows0
	addControl(0*(buttonSize+10)+10,10,buttonSize,20,100,100,255,1,"close this window",-1,closew,0);
	addControl(1*(buttonSize+10)+10,10,buttonSize,20,100,100,255,1,"show other window",-1,showw1,0);
	//control windows1
	addControl(0*(buttonSize+10)+10,10,buttonSize,20,100,100,255,1,"close this window",-1,closew1,1);
	addControl(1*(buttonSize+10)+10,10,buttonSize,20,100,100,255,1,"show msgbox",-1,Clicks,1);
	while(closewin0!=1){
		closewin1=0;
		events=getEvent(w1);
	}	
	closeWindows(w1);
	closeX();
	return 0;
}
