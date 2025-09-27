#include <stdio.h>  

#include <math.h>    

int main()  

{

    float x,y,z,t;  

	y = 2;
	
	z = 4;

    t= 5/(1+pow (y, 2));    

    x=2*y+ 3* sinh(t)-z;    

    printf("\n Output: x=%.2f ",x);    

   return 0;    

}

