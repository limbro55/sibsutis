#include <stdio.h>
#include <math.h>

int main() {
    int N;
    double S = 0;

    printf("Enter the value of N: ");
    scanf("%d", &N);

    for (int j = 1; j <= N; j++) {
        S += tan(j * 2);
    }

    printf("S = %lf\n", S);

    return 0;
}
