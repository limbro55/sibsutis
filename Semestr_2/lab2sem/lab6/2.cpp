#include <stdio.h>
#include<math.h>

double fact(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * fact(n - 1);
    }
}

void Probability(int n, int m, double p, double* probabilityGirl, double* probabilityBoy) {
    if (n < 0 || m < 0 || m > n) {
        printf("uncorrect.\n");
        return;
    }

    double q = 1 - p;

    double cnm = fact(n) / (fact(m) * fact(n - m));

    *probabilityGirl = cnm * pow(p, m) * pow(q, n - m);
    *probabilityBoy = cnm * pow(q, m) * pow(p, n - m);
}

int main() {
    int n, m;
    double p = 0.45;

    printf("write children (n): ");
    scanf("%d", &n);
    printf("write gerl and boy (m): ");
    scanf("%d", &m);

    double probabilityGirl, probabilityBoy;
    Probability(n, m, p, &probabilityGirl, &probabilityBoy);

    printf("The probability that among %d children there will be %d girls: %lf\n", n, m, probabilityGirl);
    printf("The probability that among %d children there will be %d boys: %lf\n", n, m, probabilityBoy);

    return 0;
}
