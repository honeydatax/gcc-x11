#include <unistd.h>
#include "winx11.h"
//gcc -o win win.c -lX11
char *arraysp[]={"exit","mousepad","ls -l","cal"};
int closewin0=0;
int buttonSize=80;
void Clicks(int index){
	if(index==0){
		closewin0=1;
	}else{
		system(arraysp[index]);
	}
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
	setCaption(w1,"shell system exemple","input X");
	for(n=0;n<4;n++)addControl(n*(buttonSize+10)+10,10,buttonSize,20,100,100,255,1,arraysp[n],-1,Clicks,0);
	events=getEvent(w1);
	while(closewin0!=1){
		events=getEvent(w1);
	}
	closeWindows(w1);
	closeX();
	return 0;
}
