#include <stdio.h>
#include <math.h>

double factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

double cosine(double x) {
    double result = 0;
    double term = 1;
    int n = 0;
    double eps = 0.0001;

    while (fabs(term) >= eps) {
        term = pow(-1, n) * pow(x, 2 * n) / factorial(2 * n);
        result += term;
        n++;
    }

    return result;
}

int main() {
    double x;

    printf("write cos: ");
    scanf("%lf", &x);

    double cos_x = cosine(x);
    printf("cos(%.2f) = %.6f\n", x, cos_x);

    double cos_lib = cos(x);
    
    printf("cos in math.h:%f",cos_lib);
    
    if (fabs(cos_x - cos_lib) < 0.0001) {
        printf("correct.\n");
    } else {
        printf("not correct.\n");
    }
    return 0;
}
