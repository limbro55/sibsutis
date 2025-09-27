#include <stdio.h>  

#include <math.h>    

int main()  

{

    float x,y,z,t;  
    t = 2;
    z = 3;
    y = cos(t+z);
    x = 4 *log(pow(y,3))-z/t;
	printf("\n Output: x=%7.2f ",x);    
	return 0;    

}
