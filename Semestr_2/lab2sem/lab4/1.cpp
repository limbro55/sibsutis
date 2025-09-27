#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int m, n = 5;
    printf("Write m: ");
    scanf("%d", &m);

    // Выделение памяти под  массив B
    int** B = new int*[m];
    for (int i = 0; i < m; ++i)// Выделяем память для каждой строки 
    {
        B[i] = new int[n];
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            B[i][j] = rand() % 100;
        }
    }

    // Нахождение максимального элемента и его индексов
    int maxElement = B[0][0];
    int maxRowIndex = 0, maxColIndex = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (B[i][j] > maxElement) {
                maxElement = B[i][j];
                maxRowIndex = i;
                maxColIndex = j;
            }
        }
    }

    // Выделение памяти под новую динамическую матрицу C[m-1][n-1]
    int** C = (int**)malloc((m - 1) * sizeof(int*));
    for (int i = 0; i < m - 1; ++i) {
        C[i] = (int*)malloc((n - 1) * sizeof(int));
    }

    // Заполнение матрицы C путем удаления строки и столбца с макс эл
    int ci = 0;
    for (int i = 0; i < m; ++i) {
        if (i == maxRowIndex) continue;
        
        int cj = 0;
        for (int j = 0; j < n; ++j) {
            if (j == maxColIndex) continue;
            
            C[ci][cj] = B[i][j];
            cj++;
        }
        ci++;
    }

    // Вывод исходной матрицы B
    printf("Original array:\n");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    // Вывод новой матрицы C
    printf("New array:\n");
    for (int i = 0; i < m - 1; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Освобождение памяти
    for (int i = 0; i < m; ++i) {
        delete[] B[i];
    }
    delete[] B;

    for (int i = 0; i < m - 1; ++i) {
        free(C[i]);
    }
    free(C);

    return 0;
}
