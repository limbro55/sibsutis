#include<stdio.h>

int main(){
	printf("vvedite 5 chisel \n");
	int a,b,c,d,e,s;
	s = 0;
	scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
	if (a>0){
		s = s+a;
	} 
	if (b>0){
	s = s+b;
	}
	if (c>0){
		s = s+c;
	}
	if (d>0){
	s = s+d;
	}
	if (e>0){
	s = s+e;
	}
	printf("s=%7.2d",s);
	return 0;
	
}
