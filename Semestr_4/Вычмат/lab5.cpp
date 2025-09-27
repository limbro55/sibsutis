#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4  //кол-во узлов интерполяции

double fact(double n) {
    if(n < 0) return 0.;
    if(n == 0. || n == 1.) return 1.;
    return n * fact(n - 1.);
}

// Ньютона
void fill_T(double** T, double* y_arr) {
    for(int i = 0; i < N; i++)
        T[i][0] = y_arr[i];

    for(int i = 1; i < N; i++) {
        for(int j = 0; j < N - i; j++)
            T[j][i] = T[j + 1][i - 1] - T[j][i - 1];
    }
}
// для интерполирования вперед
double newt1(double** T, double* x_arr, double x, double h) {
    double q = (x - x_arr[0]) / h;  //нормированная разность
    double result = T[0][0] + (T[0][1] * q / fact(1));

    for(int i = 2; i < N; i++) { // с разности второго порядка
        double term = T[0][i] * q;
        for(int j = 1; j < i; j++) term *= (q - j);
        result += term / fact(i);
    }
    return result;
}
// для интерполирования назад
double newt2(double** T, double* x_arr, double x, double h) {
    int n = N - 1;
    double q = (x - x_arr[n]) / h;
    double result = T[n][0] + (T[n-1][1] * q / fact(1));

    for(int i = 2; i <= n; i++) {
        double term = T[n-i][i] * q;
        for(int j = 1; j < i; j++) term *= (q + j);
        result += term / fact(i);
    }
    return result;
}

// Лагранжа
double lag(double x, double* x_arr, double* y_arr) {
    double result = 0;
    //цикл по узлам 
    for(int i = 0; i < N; i++) {
        double up = 1, down = 1;
        for(int j = 0; j < N; j++) {
            if(j != i) {
                up *= x - x_arr[j];
                down *= x_arr[i] - x_arr[j];
            }
        }
        result += y_arr[i] * (up / down);
    }
    return result;
}

// Эйткена
double eit(double x, double* x_arr, double* y_arr) {
    double** P = (double**)malloc((N - 1) * sizeof(double*));

    for(int i = 0; i < N - 1; i++)
        P[i] = (double*)malloc((N - i - 1) * sizeof(double));
    //Заполнение первого уровня
    for(int i = 0; i < N - 1; i++)
        P[0][i] = (y_arr[i] * (x - x_arr[i + 1]) - y_arr[i + 1] * (x - x_arr[i])) / (x_arr[i] - x_arr[i + 1]);
    //вычисление последующих уровней
    for(int i = 1; i < N - 1; i++) {
        for(int j = 0; j < N - i - 1; j++) {
            P[i][j] = (P[i - 1][j] * (x - x_arr[j + i + 1]) - P[i - 1][j + 1] * (x - x_arr[j])) / (x_arr[j] - x_arr[j + i + 1]);
        }
    }

    double result = P[N - 2][0];

    for(int i = 0; i < N - 1; i++)
        free(P[i]);
    free(P);

    return result;
}

int main() {
    double x = 2.56;
    double h = 1.0;

    // инициализация данных
    double* x_arr = (double*)malloc(N * sizeof(double));
    double* y_arr = (double*)malloc(N * sizeof(double));

    for(int i = 0; i < N; i++)
        x_arr[i] = (double)(i + 1);
    
    y_arr[0] = 1.0000;
    y_arr[1] = 1.4142;
    y_arr[2] = 1.7321;
    y_arr[3] = 2.0000;

    // Ньютона
    double** T = (double**)malloc(N * sizeof(double*));
    for(int i = 0; i < N; i++)
        T[i] = (double*)malloc((N - i) * sizeof(double));
    
    fill_T(T, y_arr);
    
    printf("Newton interpolation:\n");
    printf("First formula: f(%.2f) = %.6f\n", x, newt1(T, x_arr, x, h));
    printf("Second formula: f(%.2f) = %.6f\n\n", x, newt2(T, x_arr, x, h));

    // Лагранжа
    printf("Lagrange interpolation:\n");
    printf("f(%.2f) = %.6f\n\n", x, lag(x, x_arr, y_arr));

    //  Эйткена
    printf("Aitken interpolation:\n");
    printf("f(%.2f) = %.6f\n\n", x, eit(x, x_arr, y_arr));

    // Сравнение в точке x=2.56
    printf("Comparison at x=2.56:\n");
    printf("Exact value: sqrt(2.56) = %.6f\n", sqrt(2.56));
    printf("Newton1: %.6f (error: %.6f)\n", newt1(T, x_arr, x, h), fabs(newt1(T, x_arr, x, h) - sqrt(2.56)));
    printf("Newton2: %.6f (error: %.6f)\n", newt2(T, x_arr, x, h), fabs(newt2(T, x_arr, x, h) - sqrt(2.56)));
    printf("Lagrange: %.6f (error: %.6f)\n", lag(x, x_arr, y_arr), fabs(lag(x, x_arr, y_arr) - sqrt(2.56)));
    printf("Aitken: %.6f (error: %.6f)\n", eit(x, x_arr, y_arr), fabs(eit(x, x_arr, y_arr) - sqrt(2.56)));

    // Освобождение памяти
    for(int i = 0; i < N; i++)
        free(T[i]);
    free(T);
    free(x_arr);
    free(y_arr);

    return 0;
}