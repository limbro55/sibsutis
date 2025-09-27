#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){

    srand(time(NULL));
    int size = 20;
    int arr[size];

    printf("[");
   	for (int i=0; i<size; ++i){
	    arr [i] =-10 + rand() % 21;
        printf("%d, ", arr[i]);
    }
    printf("]");

    printf(" \npolohz: ");
    printf(" [");
    for(int i = 0; i<size; ++i){
        if (arr[i]>0){
            
            printf("%d, ", arr[i]);
        }
    }
    printf("]");

    printf("\n otri: ");
    printf("[");
    for(int i = 0; i<size; ++i){
        if (arr[i]<0){
            printf("%d, ", arr[i]);
        }
    }
    printf("]");


    return 0;
}