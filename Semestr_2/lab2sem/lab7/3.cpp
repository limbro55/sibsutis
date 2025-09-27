#include <stdio.h>
#include <stdlib.h>

// Функция сортировки элементов массива в порядке убывания
void sortDescending(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Функция поиска элемента в отсортированном массиве методом перебора
int linearSearch(int arr[], int size, int key, int *iterations) {
    for (int i = 0; i < size; i++) {
        (*iterations)++;
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

// Функция поиска элемента в отсортированном массиве методом бинарного поиска
int binarySearch(int arr[], int size, int key, int *iterations) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        (*iterations)++;
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int main() {
    
    int arr100[100];
    int arr1000[1000];
    
    
    for (int i = 0; i < 100; i++) {
        arr100[i] = rand() % 1000;
    }
    
    for (int i = 0; i < 1000; i++) {
        arr1000[i] = rand() % 10000;
    }
    
    
    sortDescending(arr100, 100);
    sortDescending(arr1000, 1000);
    
    // Поиск элементов в отсортированных массивах
    int key1 = arr100[50]; // Пример элемента для поиска
    int key2 = arr1000[500]; 
    
    int iterations_linear_100 = 0;
    int iterations_binary_100 = 0;
    
    int index_linear_100 = linearSearch(arr100, 100, key1, &iterations_linear_100);
    int index_binary_100 = binarySearch(arr100, 100, key1, &iterations_binary_100);
    
    printf("For array of 100 elements:\n");
    printf("Element %d was found by iteration method in %d iterations\n", key1, iterations_linear_100);
    printf("Element %d was found by binary search method in %d iterations\n", key1, iterations_binary_100);

    int iterations_linear_1000 = 0;
    int iterations_binary_1000 = 0;
    
    int index_linear_1000 = linearSearch(arr1000, 1000, key2, &iterations_linear_1000);
    int index_binary_1000 = binarySearch(arr1000, 1000, key2, &iterations_binary_1000);
    
    printf("\n for an array of 1000 elements:\n");
    printf("Element %d was found by iteration method in %d iterations\n", key2, iterations_linear_1000);
    printf("Element %d was found by binary search method in %d iterations\n", key2, iterations_binary_1000);
    return 0;
}
