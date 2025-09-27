#include<stdio.h>
#include<math.h>

int main(){

    double Pi = 0, e = 0.00001,    n = 1, i = 0;

    while(1/n>=e){
        Pi += ((int) i++ %2 == 0)?4.0/n: -4.0/n;
        n+=2;
    }

    printf("%lf\n", Pi);

    return 0;
}