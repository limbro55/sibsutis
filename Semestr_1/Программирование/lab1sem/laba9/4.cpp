#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int check(int matrix[N][N]);

int main() {
    srand(time(NULL));

    int matrix[N][N];
    size_t n = 0;
    do {
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < N; j++)
                matrix[i][j] = rand() % 10;
        n++;
    } while (check(matrix));
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    printf("%zu\n", n);
}

int check(int matrix[N][N]) {
    int sum_str[3] = {
        matrix[0][0] + matrix[0][1] + matrix[0][2],
        matrix[1][0] + matrix[1][1] + matrix[1][2],
        matrix[2][0] + matrix[2][1] + matrix[2][2],
    };
    int sum_col[3] = {
        matrix[0][0] + matrix[1][0] + matrix[2][0],
        matrix[0][1] + matrix[1][1] + matrix[2][1],
        matrix[0][2] + matrix[1][2] + matrix[2][2],
    };
    
    if (sum_str[0] == sum_str[1] && sum_str[1] == sum_str[2] &&
        sum_col[0] == sum_col[1] && sum_col[1] == sum_col[2] &&
        sum_col[0] == sum_str[0]) 
        return 0;
    return 1;
} 