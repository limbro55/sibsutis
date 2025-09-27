#include <stdio.h>

void printNegativeThenPositive(int arr[], int n, int index) {
    if (index == n) {
        return;
    }

    if (arr[index] < 0) {
        printf("%d ", arr[index]);
    }

    printNegativeThenPositive(arr, n, index + 1);

    if (arr[index] > 0) {
        printf("%d ", arr[index]);
    }
}

int main() {
    int n;
    printf("Write array: ");
    scanf("%d", &n);

    int arr[n];
    printf("write number array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Result:\n");
    printNegativeThenPositive(arr, n, 0);

    return 0;
}
