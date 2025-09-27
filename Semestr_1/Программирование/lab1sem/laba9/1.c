#include<stdio.h>
#include<time.h>
#include<stdlib.h>
void swapmatr(int a[10][20], int row1, int row2){
    for (int i=0; i<20; i++){
        int temp = a[row1][i];
        a[row1][i]=a[row2][i];
        a[row2][i]=temp;
    }
    
}


int main(){

    srand(time(NULL));

    int a[10][20];

    for(int i=0; i<10; i++){
        for(int j =0; j<20; j++){
            a[i][j] =rand() % 6;
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }



    for (int i = 0; i < 10; i += 2) {
        swapmatr(a, i, i + 1);
    }
    printf("\n");
        
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    
    
    

    return 0;
}