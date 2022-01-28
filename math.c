#include <unistd.h>
#include "winx11.h"
//gcc -o win win.c -lX11
int closewin0=0;
int closewin1=0;
int closewin2=0;
int closewin3=0;
int buttonSize=120;
int cccs=0;
void exitslist(int index){
	closewin3=1;
	printf("%s\n",ccs.cs[index].strings);
}
void showreturn(char *argv){
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
	w1->twins=3;
	f1=fopen(argv,"r");
	if(f1==NULL)goto endexit;
	newWindows(w1);
	nn=0;
	for(n=0;n<20;n++){
		if(!feof(f1)){
			fgets(sss,80,f1);
			cc=newString(sss);
			ccs.cs[cccs+n].strings=cc;
			nn=n;
		}
	}
	fclose(f1);
	closewin3=0;
	while(closewin3!=1){
		events=getEvent(w1);
	}
	for(n=0;n<20;n++){
			if(n<nn)if(ccs.cs[cccs+n].strings[0]!=0)frees(ccs.cs[cccs+n].strings);
			ccs.cs[cccs+n].strings="";
	}
	closeWindows(w1);
	endexit:
	cc=NULL;
}
void closew(int index){
	closewin0=1;
	printf("you click control index: %d\n",index);
}
void Clicks(int index){
	struct wins w;
	struct wins *w1;
	char *c;
	char *cc;
	FILE *f1;
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
	setCaption(w1,"math","input X");
	c=inputbox(w1,"");
	cc=newString(c);
	cc=catString(cc,"\nquit");
	frees(c);
	f1=fopen("/tmp/in","w");
	if(f1==NULL)goto exitsfiler;
	fprintf(f1,"%s",cc);
	fclose(f1);
	print("hello");
	system ("bc < /tmp/in > /tmp/temp");
	showreturn("/tmp/temp");
	exitsfiler:
	frees(cc);
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
	setCaption(w1,"calc exemple","input X");
	addControl(0*(buttonSize+10)+10,10,buttonSize,20,100,100,255,1," close this window",-1,closew,0);
	addControl(1*(buttonSize+10)+10,10,buttonSize,20,100,100,255,1," input calc",-1,Clicks,0);
	cccs=ccs.count;
	for(n=0;n<20;n++){
			addControl(8,n*18+8,600,16,100,100,255,-1,"",-1,exitslist,3);
	}
	events=getEvent(w1);
	while(closewin0!=1){
		events=getEvent(w1);
	}
	closeWindows(w1);
	closeX();
	return 0;
}
