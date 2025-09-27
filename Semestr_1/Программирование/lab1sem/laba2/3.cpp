#include<stdio.h>

int main(){
	printf("vvedite 4 chisla");
	int a,b,c,d;
	scanf("%d %d %d %d",&a,&b,&c,&d);
	if (a<0){
	a =a* 0;
	}
	if (b<0){
	b =b* 0;
	}
	if (c<0){
	c =c* 0;
	}
	if (d<0){
	d =d* 0;
	}
	printf("a=%7.2d, b=%7.2d, c=%7.2d, d=%7.2d",a,b,c,d);
	return 0;
}
