#include <stdio.h>
#include <stdlib.h>

// Структура для хранения информации о школе
typedef struct {
    int schoolNumber;
    int graduatesCount;
    int universityCount;
    float admissionPercentage;
} School;

// Функция для сравнения элементов при сортировке по проценту поступивших в ВУЗы
int compareByAdmissionPercentage(const void *a, const void *b) {
    School *schoolA = (School *)a;
    School *schoolB = (School *)b;
    
    if (schoolA->admissionPercentage < schoolB->admissionPercentage) {
        return 1;
    } else if (schoolA->admissionPercentage > schoolB->admissionPercentage) {
        return -1;
    } else {
        return 0;
    }
}

int main() {
    // Создание массива школ
    School schools[] = {
        {1, 100, 80, 80.0},
        {2, 120, 90, 75.0},
        {3, 150, 100, 66.7},
        {4, 80, 60, 75.0},
        {5, 200, 150, 75.0}
    };
    
    int schoolsCount = sizeof(schools) / sizeof(schools[0]);
    
    // Создание индексного массива
    int index[schoolsCount];
    for (int i = 0; i < schoolsCount; i++) {
        index[i] = i;
    }
    
    // Сортировка индексного массива по проценту поступивших в ВУЗы
    qsort(index, schoolsCount, sizeof(int), compareByAdmissionPercentage);
    
    // Вывод данных о количестве выпускников и проценте поступивших в ВУЗ для каждой школы
    printf("Data on schools:\n");
    printf("School  | Number of graduates | Enrolled in University | Percentage of applicants\n");
    for (int i = 0; i < schoolsCount; i++) {
        int idx = index[i];
        printf("%6d | %18d   | %15d        | %18.2f%%\n", schools[idx].schoolNumber, schools[idx].graduatesCount, schools[idx].universityCount, schools[idx].admissionPercentage);
    }
    
    return 0;
}
