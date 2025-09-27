#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;
    printf("Write m: ");
    scanf("%d", &m);
    printf("Write n: ");
    scanf("%d", &n);

    
    int** A = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; ++i) {
        A[i] = (int*)malloc(n * sizeof(int));
    }

    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = rand() % 50; 
        }
    }

    // Выделение памяти под двумерный динамический массив D[m+1][n+1]
    int** D = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i < m + 1; ++i) {
        D[i] = (int*)malloc((n + 1) * sizeof(int));
    }

    // Заполнение массива D и вычисление сумм строк и столбцов
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            D[i][j] = A[i][j];
            D[i][n] += A[i][j]; // сумма элементов строки
            D[m][j] += A[i][j]; // сумма элементов столбца
            D[m][n] += A[i][j]; // сумма всех элементов
        }
    }

    printf("array D:\n");
    for (int i = 0; i < m + 1; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            printf("%d ", D[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < m; ++i) {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < m + 1; ++i) {
        free(D[i]);
    }
    free(D);

    return 0;
}
