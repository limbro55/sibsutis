#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LEN 20

int main() {
    srand(time(NULL));

    double A[LEN];
    for (int i = 0; i < LEN; i++) {
        A[i] = -10 + (double)rand() / (double)(RAND_MAX / 20.0);
        printf("%lf ", A[i]);
    }
    printf("\n");

    double B[LEN];
    int j = 0;
    for (int i = 0; i < LEN; i++) {
        if (A[i] > 0) {
            B[j] = A[i];
            printf("%lf ", B[j++]);
        }
    }
    printf("\n");

    return 0;
}