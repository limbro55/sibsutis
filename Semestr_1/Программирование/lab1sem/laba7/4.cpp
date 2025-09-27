#include <stdio.h>
#include <stdlib.h>
#include<time.h>


int main() {
    int size = 20;
    int C[size];
    int D[size];
    srand(time(NULL));

    for (int i = 0; i < 20; i++) {
        C[i] = (rand()%21); 
        D[i] = (rand()%21);
    }
    printf("arr C: ");
    for (int i = 0; i < 20; i++) {
        printf("%i ", C[i]);
    }
    printf("\n");
    printf("arr D: " );
    for (int i = 0; i < 20; i++) {
        printf("%i ", D[i]);
    }
    printf("\n");

    int temp;
    for (int i = 0; i < size - 1; i++){
        for (int j = 0; j < size - 1; j++){
            if (C[j] > C[j + 1]){
                temp = C[j];
                C[j] = C[j + 1];
                C[j + 1] = temp;
                temp = 0;
            }
        }
    }

    for (int i = 0; i < size - 1; i++){
        for (int j = 0; j < size - 1; j++){
            if (D[j] > D[j + 1]){
                temp = D[j];
                D[j] = D[j + 1];
                D[j + 1] = temp;
                temp = 0;
            }
        }
    }
    printf("\n");
    printf("obr arr C: ");
    for (int i = 0; i < 20; i++) {
        printf("%i ", C[i]);
    }
    printf("\n");
    printf("obr arr D: " );
    for (int i = 0; i < 20; i++) {
        printf("%i ", D[i]);
    }
    printf("\n");
    

    int E[size*2];
    int size2 = size*2;
    
    int i = 0, j = 0, k = 0;
    while (i < 20 && j < 20) {
        if (C[i] < D[j]) {
            E[k++] = C[i++];
        } else {
            E[k++] = D[j++];
        }
    }
    while (i < 20) {
        E[k++] = C[i++];
    }
    while (j < 20) {
        E[k++] = D[j++];
    }

    printf("\n");
    printf("arr E: ");
    for (int i = 0; i < 40; i++) {
        printf("%d ", E[i]);
    }
}