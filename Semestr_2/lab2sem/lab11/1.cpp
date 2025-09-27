#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define FILENAME "passengers.txt"

// Структура для хранения информации о пассажирах
typedef struct {
    char name[MAX_NAME_LENGTH];
    int seats;
    float weight;
} Passenger;

// Функция для создания файла из N записей
void createFile(int n) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("ERROR open file.\n");
        exit(1);
    }

    Passenger passenger;
    for (int i = 0; i < n; i++) {
        printf("Enter info passenger %d:\n", i + 1);
        printf("FIO: ");
        getchar(); // Очищаем входной поток от символа новой строки
        fgets(passenger.name, MAX_NAME_LENGTH, stdin);
        passenger.name[strcspn(passenger.name, "\n")] = '\0'; // Убираем символ новой строки
        printf("Number of seats occupied: ");
        scanf("%d", &passenger.seats);
        printf("The total weight of things: ");
        scanf("%f", &passenger.weight);
        getchar(); // Считываем лишний символ новой строки после веса

        fprintf(file, "%s %d %.2f\n", passenger.name, passenger.seats, passenger.weight);
    }

    fclose(file);
}


// Функция для просмотра файла
void viewFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("ERROR open file.\n");
        exit(1);
    }

    printf("Info for passenger:\n");
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

// Функция для добавления записи в конец файла
void appendToFile() {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("ERROR open file.\n");
        exit(1);
    }

    Passenger passenger;
    printf("Enter info for new passenger:\n");
    printf("FIO: ");
    fgets(passenger.name, MAX_NAME_LENGTH, stdin);
    passenger.name[strcspn(passenger.name, "\n")] = '\0'; // Убираем символ новой строки
    printf("Number of seats occupied: ");
    scanf("%d", &passenger.seats);
    printf("The total weight of things: ");
    scanf("%f", &passenger.weight);
    getchar(); // Считываем лишний символ новой строки после веса

    fprintf(file, "%s %d %.2f\n", passenger.name, passenger.seats, passenger.weight);

    fclose(file);
}

// Функция для удаления записей с общим весом вещей менее 10 кг
void deleteLessThan10kg() {
    FILE *file = fopen(FILENAME, "r+");
    if (file == NULL) {
        printf("ERROR open file.\n");
        exit(1);
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("ERROR open temp file.\n");
        exit(1);
    }

    Passenger passenger;
    while (fscanf(file, "%s %d %f", passenger.name, &passenger.seats, &passenger.weight) != EOF) {
        if (passenger.weight >= 10) {
            fprintf(tempFile, "%s %d %.2f\n", passenger.name, passenger.seats, passenger.weight);
        }
    }

    fclose(file);
    fclose(tempFile);
    
    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

// Функция для изменения веса вещей пассажира по заданной фамилии
void changeWeightByName(char *name) {
    FILE *file = fopen(FILENAME, "r+");
    if (file == NULL) {
        printf("ERROR open file.\n");
        exit(1);
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("ERROR open temp file.\n");
        exit(1);
    }

    Passenger passenger;
    int found = 0;
    while (fscanf(file, "%s %d %f", passenger.name, &passenger.seats, &passenger.weight) != EOF) {
        if (strcmp(passenger.name, name) == 0) {
            printf("Enter a new weight of items for the passenger %s: ", name);
            scanf("%f", &passenger.weight);
            found = 1;
        }
        fprintf(tempFile, "%s %d %.2f\n", passenger.name, passenger.seats, passenger.weight);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("The passenger with the last name %s was not found.\n", name);
        remove("temp.txt");
        return;
    }

    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

// Функция для вывода меню
void printMenu() {
    printf("\n Menu:\n");
    printf("1. Create a file from N records\n");
    printf("2. View the file \n");//Просмотреть файл
    printf("3. Add a new entry  to the end of the file\n");//Добавьте новую запись в конец файла
    printf("4. Find and delete passenger records from the file, the total weight of which is less than 10 kg\n");//Найдите и удалите из файла записи о пассажирах, общий вес которых составляет менее 10 кг
    printf("5. Change the weight of the passenger's belongings according to the specified surname \n");//Измените вес вещей пассажира в соответствии с указанной фамилией
    printf("6. Exit \n");
    printf("Select an action: ");
}

int main() {
    int choice;
    int n;
    char name[MAX_NAME_LENGTH];

    do {
        printMenu();
        scanf("%d", &choice);
        getchar(); // Считываем лишний символ новой строки

        switch (choice) {
            case 1:
                printf("Enter the number of entries: ");
                scanf("%d", &n);
                createFile(n);
                break;
            case 2:
                viewFile();
                break;
            case 3:
                appendToFile();
                break;
            case 4:
                deleteLessThan10kg();
                break;
            case 5:
                printf("Enter the last name of the passenger whose weight needs to be changed: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // Убираем символ новой строки
                changeWeightByName(name);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Wrong choice.\n");
        }
    } while (choice != 6);

    return 0;
}
