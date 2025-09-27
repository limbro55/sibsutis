#include <stdio.h>

void zeroBetweenMin(int arr[], int size) {
    if (size < 2) {
        return; 
    }

    int min1 = arr[0];
    int min2 = arr[1];
    int index1 = 0;
    int index2 = 1;

    // Находим два минимальных элемента и их индексы
    for (int i = 1; i < size; i++) {
        if (arr[i] < min1) {
            min2 = min1;
            index2 = index1;
            min1 = arr[i];
            index1 = i;
        } else if (arr[i] < min2) {
            min2 = arr[i];
            index2 = i;
        }
    }

    // Обнуляем элементы между двумя минимальными
    int start = (index1 < index2) ? index1 : index2;
    int end = (index1 > index2) ? index1 : index2;
    for (int i = start + 1; i < end; i++) {
        arr[i] = 0;
    }
}

int main() {
    int arr[] = {3, 5, 1, 9, 8, 4, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("First array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    zeroBetweenMin(arr, size);

    printf("\nArray procecced:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
