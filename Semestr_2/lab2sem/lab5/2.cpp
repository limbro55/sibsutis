#include <stdio.h>
#include <stdlib.h>

int main() {

    int size;
    
    printf("Write number: ");
    scanf("%d", &size);
    
    // Создаем двумерный динамический массив
    int **table = (int **)malloc(size * sizeof(int *));
    
    for (int i = 0; i < size; i++) {
        table[i] = (int *)malloc((i + 1) * sizeof(int));
        
        for (int j = 0; j <= i; j++) {
            table[i][j] = (i + 1) * (j + 1); // Заполняем таблицу умножения
        }
    }
    
    // Выводим таблицу умножения
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    
    // Освобождаем память
    for (int i = 0; i < size; i++) {
        free(table[i]);
    }
    free(table);
    
    return 0;
}
