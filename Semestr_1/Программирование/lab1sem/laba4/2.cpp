#include<stdio.h>
#include<math.h>

int main(){ 

	float s;
	s=0;
	
	for(int item=1; item<26; item++){
		s+=sin(item);
	}
	printf("\n s=%7.3f",s);
	
	return 0;
}
