#include<stdio.h>

int fact(int n){
    if (n<2){
        return 1;
    }
    return n * fact(n-1);
} 

int main(){

    int n;
    printf("Write Number");
    scanf("%d",&n);
    int c[n];

    for (int i = 0; i < n; i++){
         c[i] = fact(n) / (fact(i) * fact(n - i));                                                  
    }
    for (int i = 0; i < n; i++){
         printf("%d, ", c[i]);
    }

    return 0;
}