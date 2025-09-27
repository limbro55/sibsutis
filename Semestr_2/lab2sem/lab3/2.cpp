#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    scanf("%d", &n);

    double* a = (double*)malloc(n * sizeof(double));
    double** b = (double**)malloc(n * sizeof(double*));

    
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = (double)rand() / RAND_MAX * 100.0; 
        b[i] = &a[i];
    }

    // баблсорт массива указателей b по возрастанию
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (*b[j] > *b[j + 1]) {
                double* temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }

    
    printf("original array a:\n");
    for (int i = 0; i < n; i++) {
        printf("%lf ", a[i]);
    }
    printf("\n");

    // Вывод отсортированного массива, используя массив указателей b
    printf("sorted array a:\n");
    for (int i = 0; i < n; i++) {
        printf("%lf ", *b[i]);
    }
    printf("\n");

    free(a);
    free(b);

    return 0;
}
