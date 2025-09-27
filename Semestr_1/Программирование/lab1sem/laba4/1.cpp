#include<stdio.h>

int main(){
	int s;
	
	s = 0;
	
	for(int i=1; i<118; i++){
		s+=i;
	}
	printf("s=%7.2d",s);
	return 0;
}
