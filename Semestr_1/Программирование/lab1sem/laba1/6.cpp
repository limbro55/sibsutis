#include<stdio.h>

#include<math.h>

int main()
{
	
	float t, z;
	t = 2;
	z = 1;
	double x,y;
	y = tan(t)+z;
	x = ( 8 * pow(z , 2) + 1) / ( y * exp(t) + pow(t , 2) );
	printf("x = %.2lf\n", x);
	return 0;
	
}
