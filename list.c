#include <unistd.h>
#include "winx11.h"
//gcc -o win win.c -lX11
void Clicks(int index){
	printf("%s\n",ccs.cs[index].strings);
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
	FILE *f1;
	w1=&w;
	w1->x=10;
	w1->y=10;
	w1->w=640;
	w1->h=400;
	w1->border=1;
	w1->bords=0x1010FF;
	w1->color=RGB(0,0,255);
	w1->twins=0;
	if(argc<2)exit(1);
	f1=fopen(argv[1],"r");
	if(f1==NULL)exit(1);
	if (startxs()==-1)exit(1);
	newWindows(w1);
	ccs.click=Clicks;
	for(n=0;n<20;n++){
		if(!feof(f1)){
			fgets(sss,80,f1);
			cc=newString(sss);
			addControl(8,n*18+8,600,16,100,100,255,-1,cc,-1);
		}
	}
	fclose(f1);
	events=getEvent(w1);
	while(events->type!=KeyPress){
		events=getEvent(w1);
	}
	freeLabel(w1);
	closeWindows(w1);
	closeX();
	return 0;
}
