#include<stdio.h>

#include<math.h>

int main()
{
	
	float x,y,z,t;
	y = 2;
	z = 4;
	t = sin(2+z);
	x = 6*pow(t,2)-(1/tan(z)+1)/pow(y,2);
	printf("\n output: x=%20.4f",x);
	return 0;
	
}
