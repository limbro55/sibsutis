#include<stdio.h>
#include<math.h>

int main(){
	
	int m,p;
	
	p=1;
	
	printf("write m");
	scanf("%d",&m);
	
	for(int item=1;item<=m;item++){
		p*=item;
	}
	printf("p=%7.2d",p);
	
	return 0;
}
