#include <stdio.h>
#include <stdlib.h>
#include<time.h>6

int main() {
    int m, k;
    srand(time(NULL));
    
    printf("write m: ");
    scanf("%d", &m);
    
    int *A = (int *)malloc(m * sizeof(int)); // Создаем одномерный динамический массив A
    
    printf("write k (k < m): ");
    scanf("%d", &k);
    
    for (int i = 0; i < m; i++) {
        A[i] = rand() % 100;
    }
    
    // Создаем матрицу B
    int rows = m / k + (m % k != 0); // Определяем количество строк в матрице B
    int **B = (int **)malloc(rows * sizeof(int *));
    
    for (int i = 0; i < rows; i++) {
        B[i] = (int *)calloc(k, sizeof(int)); // Выделяем память под строки матрицы и заполняем нулями
        
        for (int j = 0; j < k; j++) {
            if (i * k + j < m) {
                B[i][j] = A[i * k + j]; // Заполняем матрицу B значениями из массива A
            }
        }
    }

    printf("Array B:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < k; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    
    // Освобождаем память
    for (int i = 0; i < rows; i++) {
        free(B[i]);
    }
    free(B);
    free(A);
    
    return 0;
}
