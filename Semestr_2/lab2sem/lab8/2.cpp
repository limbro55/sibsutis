#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для хранения информации о комнатах
typedef struct {
    int roomNumber;
    float roomArea;
    char faculty[50];
    int residentsCount;
} Room;

int main() {
    // Создание массива комнат
    Room rooms[] = {
        {101, 20.5, "Engineering", 3},
        {102, 18.7, "Science", 2},
        {103, 25.0, "Engineering", 4},
        {104, 22.3, "Arts", 3},
        {105, 19.8, "Science", 2}
    };
    
    int roomsCount = sizeof(rooms) / sizeof(rooms[0]);
    
    // Создание массива для хранения факультетов (справочника)
    char faculties[roomsCount][50];
    int facultiesCount = 0;
    
    // Заполнение массива факультетов
    for (int i = 0; i < roomsCount; i++) {
        int isNewFaculty = 1;
        for (int j = 0; j < facultiesCount; j++) {
            if (strcmp(rooms[i].faculty, faculties[j]) == 0) {
                isNewFaculty = 0;
                break;
            }
        }
        
        if (isNewFaculty) {
            strcpy(faculties[facultiesCount], rooms[i].faculty);
            facultiesCount++;
        }
    }
    
    // Вывод количества различных факультетов
    printf("Number of different faculties: %d\n", facultiesCount);
    
    // Вывод данных о количестве комнат, студентов и средней площади на одного студента по каждому факультету
    printf("Data on faculties:\n");
    for (int i = 0; i < facultiesCount; i++) {
        int roomsTotal = 0;
        int residentsTotal = 0;
        float areaPerStudentTotal = 0.0;
        
        for (int j = 0; j < roomsCount; j++) {
            if (strcmp(rooms[j].faculty, faculties[i]) == 0) {
                roomsTotal++;
                residentsTotal += rooms[j].residentsCount;
                areaPerStudentTotal += rooms[j].roomArea / rooms[j].residentsCount;
            }
        }
        
        printf("faculties: %s\n", faculties[i]);
        printf("Number of rooms: %d\n", roomsTotal);
        printf("Number of students: %d\n", residentsTotal);
        printf("Average area per student: %.2f\n", areaPerStudentTotal);
        printf("\n");
    }
    
    return 0;
}
