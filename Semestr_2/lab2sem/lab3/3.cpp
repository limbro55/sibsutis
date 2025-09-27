#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Write n: ");
    scanf("%d", &n);

    char* is_prime = (char*)malloc((n + 1) * sizeof(char)); // массив для хранения информации о простых числах
    for (int i = 2; i <= n; i++) {
        is_prime[i] = 1; // инициализация: считаем все числа от 2 до n простыми
    }

    for (int p = 2; p * p <= n; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p) {
                is_prime[i] = 0; // вычеркиваем все кратные p
            }
        }
    }

    printf("numbers 2 to n  %d:\n", n);
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    free(is_prime);

    return 0;
}
