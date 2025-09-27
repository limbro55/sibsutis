#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-4

// Функция для вывода матрицы
void printMatrix(double** A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.4f ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Функция для вычисления нормы матрицы C (‖𝐶‖∞)
double calcMaxC(double** C, int n) {
    double norm = 0.0; // хранение нормы
    for (int i = 0; i < n; i++) {
        double rowSum = 0.0;
        for (int j = 0; j < n; j++) {
            rowSum += fabs(C[i][j]);
        }
        if (rowSum > norm) {
            norm = rowSum;
        }
    }
    return norm;
}

// Функция для вычисления нормы вектора B (‖𝐵‖∞)
double calcMaxB(double* B, int n) {
    double norm = 0.0;
    for (int i = 0; i < n; i++) {
        if (fabs(B[i]) > norm) {
            norm = fabs(B[i]);
        }
    }
    return norm;
}

// Метод простых итераций
void simpleIterationMethod(double** A, double* B, double* x, int n) {
    double** C = (double**)malloc(n * sizeof(double*));
    double* D = (double*)malloc(n * sizeof(double));

    // Проверка на нулевые элементы на диагонали
    for (int i = 0; i < n; i++) {
        if (fabs(A[i][i]) < EPSILON) {
            printf("Ошибка: элемент на диагонали A[%d][%d] близок к нулю.\n", i, i);
            for (int j = 0; j < n; j++) free(C[j]);
            free(C);
            free(D);
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        C[i] = (double*)malloc(n * sizeof(double));
        D[i] = B[i] / A[i][i]; // вычисляем элементы D
        for (int j = 0; j < n; j++) {
            if (i == j) {
                C[i][j] = 0; // диагональ нуль
            } else {
                C[i][j] = -A[i][j] / A[i][i]; // для недиагонали
            }
        }
    }

    printf("Матрица C:\n");
    printMatrix(C, n);

    double maxC = calcMaxC(C, n);
    printf("Норма матрицы C (‖𝐶‖∞): %.4f\n", maxC);

    // Проверка на сходимость
    if (maxC >= 1.0) {
        printf("Внимание: норма матрицы C (‖𝐶‖∞) >= 1. Метод может не сходиться.\n");
    }

    double normD = calcMaxB(D, n);
    printf("Норма вектора D (‖𝐷‖∞): %.4f\n", normD);

    double ch = log((EPSILON * (1 - maxC)) / normD);
    double zn = log(maxC);
    int N_calc = abs((int)(ch / zn) + 1);

    printf("Вычисленное количество итераций N: %d\n", N_calc);

    double* x_new = (double*)malloc(n * sizeof(double));
    int iteration = 0;
    printf("Шаги метода простых итераций:\n");
    for (int k = 0; k < N_calc; k++) { // цикл по итерациям
        for (int i = 0; i < n; i++) {
            x_new[i] = D[i];
            for (int j = 0; j < n; j++) {
                x_new[i] += C[i][j] * x[j];
            }
        }
        for (int i = 0; i < n; i++) {
            x[i] = x_new[i];
        }
        printf("Шаг %d: ", ++iteration);
        for (int i = 0; i < n; i++) {
            printf("%.4f ", x[i]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(C[i]);
    }
    free(C);
    free(D);
    free(x_new);
}

// Метод Зейделя
void seidelMethod(double** A, double* B, double* x, int n) {
    double** C = (double**)malloc(n * sizeof(double*));
    double* D = (double*)malloc(n * sizeof(double));

    // Проверка на нулевые элементы на диагонали
    for (int i = 0; i < n; i++) {
        if (fabs(A[i][i]) < EPSILON) {
            printf("Ошибка: элемент на диагонали A[%d][%d] близок к нулю.\n", i, i);
            for (int j = 0; j < n; j++) free(C[j]);
            free(C);
            free(D);
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        C[i] = (double*)malloc(n * sizeof(double));
        D[i] = B[i] / A[i][i]; // вычисляем элементы D
        for (int j = 0; j < n; j++) {
            if (i == j) {
                C[i][j] = 0; // диагональ нуль
            } else {
                C[i][j] = -A[i][j] / A[i][i]; // для недиагонали
            }
        }
    }

    double maxC = calcMaxC(C, n);
    printf("Норма матрицы C (‖𝐶‖∞): %.4f\n", maxC);

    // Проверка на сходимость
    if (maxC >= 1.0) {
        printf("Внимание: норма матрицы C (‖𝐶‖∞) >= 1. Метод может не сходиться.\n");
    }

    double normB = calcMaxB(D, n);
    double ch = log((EPSILON * (1 - maxC)) / normB);
    double zn = log(maxC);
    int N_calc = (int)(ch / zn) + 1;

    int iteration = 0;
    printf("\nШаги метода Зейделя:\n");
    for (int k = 0; k < N_calc; k++) { // цикл по итерациям
        for (int i = 0; i < n; i++) {
            double sum = D[i];
            for (int j = 0; j < i; j++) { // по необновленным значениям
                sum += C[i][j] * x[j];
            }
            for (int j = i + 1; j < n; j++) { // по обновленным значениям
                sum += C[i][j] * x[j];
            }
            x[i] = sum;
        }
        printf("Шаг %d: ", ++iteration);
        for (int i = 0; i < n; i++) {
            printf("%.4f ", x[i]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(C[i]);
    }
    free(C);
    free(D);
}

int main() {
    const int n = 3;
    double A[3][3] = {
        {5, -1, 2},
        {-2, -10, 3},
        {1, 2, 5}
    };

    double B[3] = {9, -13, 20};

    double x_simple[3] = {0.0, 0.0, 0.0};
    double x_seidel[3] = {0.0, 0.0, 0.0};

    double** A_dynamic = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        A_dynamic[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            A_dynamic[i][j] = A[i][j];
        }
    }

    simpleIterationMethod(A_dynamic, B, x_simple, n);
    seidelMethod(A_dynamic, B, x_seidel, n);

    for (int i = 0; i < n; i++) {
        free(A_dynamic[i]);
    }
    free(A_dynamic);

    return 0;
}