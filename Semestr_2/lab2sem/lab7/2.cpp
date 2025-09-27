#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Вычисление и вывод суммы элементов каждой строки
void sumOfRows(int arr[][10], int rows) {
    for (int i = 0; i < rows; i++) {
        int sum = 0;
        int length = arr[i][0];
        for (int j = 1; j <= length; j++) {
            sum += arr[i][j];
        }
        printf("Sum elementov lines %d: %d\n", i, sum);
    }
}

int main() {
    srand(time(NULL)); 
    int rows = 5; 
    int arr[5][10]; 

    // Заполнение массива случайными числами и длинами строк
    for (int i = 0; i < rows; i++) {
        int length = rand() % 9 + 2; 
        arr[i][0] = length; 
        for (int j = 1; j <= length; j++) {
            arr[i][j] = rand() % 100; 
        }
    }

    // Вывод массива на экран
    printf("Matrix array:\n");
    for (int i = 0; i < rows; i++) {
        int length = arr[i][0];
        printf("line length %d: %d, Element: ", i, length);
        for (int j = 1; j <= length; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    
    sumOfRows(arr, rows);

    return 0;
}
