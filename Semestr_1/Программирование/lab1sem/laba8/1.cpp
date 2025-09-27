#include <stdio.h>
#include <math.h>

double f(double x) {
    return pow(x, 2) / (10 + pow(x, 3));
}

double trapezoid(double a, double b, int N, double* arr) {
    double h = (b - a) / N;
    double sum = 0;
    for (int i = 1; i < N; i++) {
        double x = a + i * h;
        arr[i] = f(x);
        sum += arr[i];
    }
    double I = h * (arr[0]/2 + sum + arr[N]/2);
    return I;
}

double simpson(double a, double b, int N, double* arr) {
    double h = (b - a) / N;
    double sum1 = 0;
    double sum2 = 0;
    for (int i = 1; i < N; i += 2) {
        double x = a + i * h;
        arr[i] = f(x);
        sum1 += arr[i];
    }
    for (int i = 2; i < N; i += 2) {
        double x = a + i * h;
        arr[i] = f(x);
        sum2 += arr[i];
    }
    double I = h / 3 * (arr[0] + arr[N] + 4 * sum1 + 2 * sum2);
    return I;
}

int main() {
    double a = -2;
    double b = 5;
    int N_value[] = {10, 100, 1000};
    int num_N = sizeof(N_value) / sizeof(N_value[0]);

    for (int i = 0; i < num_N; i++) {
        int N = N_value[i];
        double arr[N+1];
        double I_trapezoid = trapezoid(a, b, N, arr);
        double I_simpson = simpson(a, b, N, arr);
        printf("N = %d\n", N);
        printf("Trapezoid : %f\n", I_trapezoid);
        printf("Simpson: %f\n", I_simpson);
        printf("Difference: %f\n", fabs(I_trapezoid - I_simpson));
        printf("\n");
    }
    return 0;
}