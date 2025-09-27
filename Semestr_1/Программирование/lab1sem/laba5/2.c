#include<stdio.h>
#include<math.h>
#define a   2.14
#define b  -4.21
#define c   3.25
#define x0 -4.5
#define x1 -13.5
#define h   0.5

int main(){

    double max = 0, min = 0, x = x0;

    while(x>=x1){
        double y = (a*x*x+b*x+c)*sin(x);
        if (y<min){
            min = y;
        }
        else if (y>max){
            max=y;
        }
        x-=h;
    }

    printf("min=%.3lf, max=%.3lf, \n" , min, max);

    return 0;

}