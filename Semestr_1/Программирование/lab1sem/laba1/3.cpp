#include <stdio.h>  

#include <math.h>    

int main()  

{

    float x,y,z,t;  
    t = 1;
    z = 3;
    y = sin(t);
    x = 4*y*y/(4*y*pow(2.71,z)-2*pow(t,3));
    
	printf("\n Output: x=%7.2f ",x);    
	return 0;    

}
