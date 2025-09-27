#include "sorts.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

template <typename T>
float timer(void (*sort)(T* arr, int size), T* arr, int size)
{
    clock_t start = clock();
    sort(arr, size);
    clock_t end = clock();
    return (float)(end - start) / CLOCKS_PER_SEC;
}

void fill_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = rand() % size;
}

void fill_array(float arr[], int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = (float)rand() * 10 / RAND_MAX;
}

int main()
{
    int size = 1000;
    int int_arr[size];
    float float_arr[size];

    printf("Целочисленный массив\n");
    fill_array(int_arr, size);
    printf("Сортировка выбором: %.6f сек\n", timer(select_sort, int_arr, size));
    fill_array(int_arr, size);
    printf("Сортировка пузырьком: %.6f сек\n",
           timer(bubble_sort, int_arr, size));
    fill_array(int_arr, size);
    printf("Сортировка вставками: %.6f сек\n\n",
           timer(insert_sort, int_arr, size));

    printf("Вещественный массив\n");
    fill_array(float_arr, size);
    printf("Сортировка выбором: %.6f сек\n",
           timer(select_sort, float_arr, size));
    fill_array(float_arr, size);
    printf("Сортировка пузырьком: %.6f сек\n",
           timer(bubble_sort, float_arr, size));
    fill_array(float_arr, size);
    printf("Сортировка вставками: %.6f сек\n",
           timer(insert_sort, float_arr, size));

    return 0;
}
