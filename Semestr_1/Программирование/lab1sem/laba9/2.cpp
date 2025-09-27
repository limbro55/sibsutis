#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

int main() {
    srand(time(NULL));

    double arr[N][N];
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            arr[i][j] = rand() % 6;
            printf("%lf ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (size_t i = 0; i < N; i++) {
        double sum = 0;
        for (size_t j = 0; j < N; j++)
            sum += arr[i][j];
        for (size_t j = 0; j < N; j++) {
            arr[i][j] /= sum;
            printf("%lf ", arr[i][j]);
        }
        printf("\n");
    }
}