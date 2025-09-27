#include<stdio.h>
#include<math.h>

int main(){
	
	int p=1;
	
	for(int item=1;item<=12;item++){
		printf("item=%3.2d",item);
		if(item %2==0){
			p*=item;
		}
	}
	printf("p=%7.2d\n",p);
	
	return 0;
}
