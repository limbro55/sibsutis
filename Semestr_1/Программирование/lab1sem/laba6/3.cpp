#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){
    int size=20;
    float arr[size];

    srand(time(0));

    for(int item=0; item < size; ++item ){
        arr[item] = (double)rand() / RAND_MAX * 10;
        printf("%lf, ", arr[item]);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            if (arr[i] > arr[i + 1] && arr[i] > arr[size - 1])
                printf("%lf, ", arr[i]);
        } else if (i == size - 1) {
            if (arr[i] > arr[i - 1] && arr[i] > arr[0])
                printf("%lf, ", arr[i]);
        } else {
            if (arr[i] > arr[i + 1] && arr[i] > arr[i - 1])
                printf("%lf, ", arr[i]);
        } 
    }

    return 0;
}