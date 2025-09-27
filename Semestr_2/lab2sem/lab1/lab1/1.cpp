#include<stdio.h>
int f = 0;

void easter_data(int year){
    int a = year % 19;
    int b = year % 4;
    int c = year % 7;
    int d = (19*a+15)%30;
    int e = (2*b+4*c+6*d+6)%7;
    f = e+d;   
}

int main(){
    int year;
    printf("Write year: ");
    scanf("%d",&year);

    easter_data(year);

    if(f <= 26){
        int day = 4 + f;
        printf("Easter: %d april", day);
    }
    if(f > 26){
        int day = f - 26;
        printf("Easter: %d may", day);
    }
    return 0;
}
