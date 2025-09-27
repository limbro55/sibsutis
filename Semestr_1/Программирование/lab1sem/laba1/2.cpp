#include <stdio.h>  

#include <math.h>    

int main()  

{

    float x,y,z,t;  
    t = 0.5;
    z = 6;
	y = t+2*(1/tan(z));    
    x = 3 * pow(y,2)/(4*tan(z)-2*pow(t,2));
    
	printf("\n Output: x=%7.2f ",x);    
	return 0;    

}
