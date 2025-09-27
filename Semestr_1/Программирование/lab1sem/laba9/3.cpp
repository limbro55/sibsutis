#include <stdio.h>

void transposeMatrix(int matrix[3][3], int transposedMatrix[3][3]) {
    int i, j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }
}

void printMatrix(int matrix[3][3]) {
    int i, j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int transposedMatrix[3][3];

    printf("Original Matrix:\n");
    printMatrix(matrix);

    transposeMatrix(matrix, transposedMatrix);

    printf("\nTransposed Matrix:\n");
    printMatrix(transposedMatrix);

    return 0;
}