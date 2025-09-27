#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LEN 15

int check(int x, int *arr);

int main() {
    int arr[LEN];

    srand(time(NULL));
    for (int i = 0; i < LEN; i++) {
        arr[i] = rand() % 11;
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    int buffer[LEN];
    int j = 0;
    for (int i = 0; i < LEN; i++) {
        if (!check(arr[i], buffer)) {
            printf("%d ", arr[i]);
            buffer[j] = arr[i];
            j++;
        }
    }

    return 0;
}

int check(int x, int *arr) {
    for (int i = 0; i < LEN; i++) {
        if (x == arr[i])
            return 1;
    }
    return 0;
}