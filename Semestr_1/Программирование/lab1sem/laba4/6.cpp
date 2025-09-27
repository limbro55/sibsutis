#include<stdio.h>
#include<math.h>

int main()
{
	int s,n;
	s=0;
	
	printf("write n");
	scanf("%d",&n);
	
	for(int item=0; item<n;item++){
		
		if(item % 2==1){
			s+=item;
		}else{
			s-=item;
		}
		
	}
	printf("\n s=%3.2d",s);
	return 0;
}
