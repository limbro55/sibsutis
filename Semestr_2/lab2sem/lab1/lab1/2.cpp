#include <stdio.h>

double power(double x, int n) {
    if (n == 0) {
        return 1;
    } else if (n > 0) {
        double result = 1;
        for (int i = 0; i < n; i++) {
            result *= x;
        }
        return result;
    } else {
        double result = 1;
        for (int i = 0; i < -n; i++) {
            result /= x;
        }
        return result;
    }
}

int main() {
    double x;
    int n;

    printf("Write x: ");
    scanf("%lf", &x);

    printf("Write n: ");
    scanf("%d", &n);

    double result = power(x, n);
    printf("%.2f\n",result);

    return 0;
}
