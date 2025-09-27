#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,temp;
    float y,x;
    float a = 2.14,b = -4.21,c = 3.25,h = 0.5, xk= 33.5, x0;
    
    float arr[59];
    
    printf( " do obrabotki: ");
    for ( x0 = 4.5, i=0; x0 <= xk; x0 += 0.5,i++ ){
        
        x=  -x0;
        
        y= a * pow(x,2) * sin(x) + b * x +c;
        
        arr[i]=y;
        
        printf("%.2f, ",arr[i]);
    }
   
   printf("\n posle  : ");
   
   for (i=0; i < 59; i++){
       for (j = 0; j < 59; j++){
           if (arr[j]< arr[j+1]){
               temp=arr[j];
               arr[j]=arr[j+1];
               arr[j+1]=temp;
           }
       }
   }
   for (i=0; i<= 59; i++){
       printf("%.2f, ",arr[i]);
   }
    return 0;
}