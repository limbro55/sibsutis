#include <stdio.h>
#include <math.h>

double calculate_sum(double x) {
    double s = 0;
    double term = 0.18 * x;
    for (int i = 2; i <= 10; i++) {
        term *= (0.02 * x);
        s += pow(term, i);
    }
    return s;
}

int main() {
    double x;
    printf("Введите значение x: ");
    scanf("%lf", &x);
    
    double result = calculate_sum(x);
    printf("Сумма ряда: %f\n", result);
    
    return 0;
}
