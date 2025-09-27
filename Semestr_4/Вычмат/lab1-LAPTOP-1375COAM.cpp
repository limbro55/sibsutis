#include <stdio.h>
#include <stdlib.h>

void print_matrix(double **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void gauss(double **matrix, int N) {
    for (int i = 0; i < N; i++) {
        // поиск макс элемента в столбце
        int max_row = i;
        for (int k = i + 1; k < N; k++) {
            if (matrix[k][i] > matrix[max_row][i]) {
                max_row = k;
            }
        }

        // перестановка строк
        for (int k = i; k < N + 1; k++) {
            double temp = matrix[i][k];
            matrix[i][k] = matrix[max_row][k];
            matrix[max_row][k] = temp;
        }

        // вывод матрицы после перестановки строк
        printf("После перестановки строк (итерация %d):\n", i + 1);
        print_matrix(matrix, N);

        // приведение матрицы к ступенчатому виду
        for (int k = i + 1; k < N; k++) {
            double factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j < N + 1; j++) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }

        printf("После приведения к ступенчатому виду (итерация %d):\n", i + 1);
        print_matrix(matrix, N);
    }
}

void back(double **matrix, double *solution, int N) {
    for (int i = N - 1; i >= 0; i--) {
        solution[i] = matrix[i][N];
        for (int j = i + 1; j < N; j++) {
            solution[i] -= matrix[i][j] * solution[j];
        }
        solution[i] /= matrix[i][i];
    }
}

int main() {
    FILE *file = fopen("./matrix.txt", "r");
    if (!file) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

    int N;
    fscanf(file, "%d", &N);

    double **matrix = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (double *)malloc((N + 1) * sizeof(double));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }
    fclose(file);

    printf("Исходная матрица:\n");
    print_matrix(matrix, N);

    // прямой ход
    gauss(matrix, N);

    // обратный ход
    double *solution = (double *)malloc(N * sizeof(double));
    back(matrix, solution, N);

    printf("Решение системы:\n");
    for (int i = 0; i < N; i++) {
        printf("x%d = %.2f\n", i + 1, solution[i]);
    }

    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(solution);

    return 0;
}