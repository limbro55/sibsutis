#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    scanf("%d", &n);

    int *b = (int*)malloc(n * sizeof(int));
    if (b == NULL) {
        printf("ERROR!!!\n");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        b[i] = rand() % 101 - 50;
    }

    int m = 0, k = 0;
    for (int i = 0; i < n; i++) {
        if (b[i] > 0) {
            m++;
        } else if (b[i] < 0) {
            k++;
        }
    }

    int *c = (int*)malloc(m * sizeof(int));
    int *d = (int*)malloc(k * sizeof(int));
    if (c == NULL || d == NULL) {
        printf("Error!!!\n");
        free(b);
        free(c);
        free(d);
        return 1;
    }

    m = 0;
    k = 0;
    for (int i = 0; i < n; i++) {
        if (b[i] > 0) {
            c[m] = b[i];
            m++;
        } else if (b[i] < 0) {
            d[k] = b[i];
            k++;
        }
    }

    printf("original array b:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    printf("positive array c:\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    printf("negative array d:\n");
    for (int i = 0; i < k; i++) {
        printf("%d ", d[i]);
    }
    printf("\n");

    
    free(b);
    free(c);
    free(d);

    return 0;
}
