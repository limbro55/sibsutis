#include <iostream>
#include <cstring>
using namespace std;

struct Student {
    char *surname;
    int grades[4];
    Student *left;
    Student *right;
};

// Функция для создания новой структуры Student
Student *createStudent(const char *surname, int grade1, int grade2, int grade3, int grade4) {
    Student *newStudent = new Student;
    newStudent->surname = strdup(surname);
    newStudent->grades[0] = grade1;
    newStudent->grades[1] = grade2;
    newStudent->grades[2] = grade3;
    newStudent->grades[3] = grade4;
    newStudent->left = nullptr;
    newStudent->right = nullptr;
    return newStudent;
}

// добавление нового студента
void addStudent(Student *&root, const char *surname, int grade1, int grade2, int grade3, int grade4) {
    if (root == nullptr) {
        root = createStudent(surname, grade1, grade2, grade3, grade4);
    } else {
        if (strcmp(surname, root->surname) < 0) {
            addStudent(root->left, surname, grade1, grade2, grade3, grade4);
        } else {
            addStudent(root->right, surname, grade1, grade2, grade3, grade4);
        }
    }
}

// Вывод фамилий по возрастанию
void printInOrder(Student *root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << root->surname << endl;
        printInOrder(root->right);
    }
}

// Вывод фамилий по убыванию
void printReverseOrder(Student *root) {
    if (root != nullptr) {
        printReverseOrder(root->right);
        cout << root->surname << endl;
        printReverseOrder(root->left);
    }
}

// Поиск студента
Student *findStudent(Student *root, const char *surname) {
    while (root != nullptr) {
        if (strcmp(surname, root->surname) == 0) {
            return root;
        } else if (strcmp(surname, root->surname) < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return nullptr; // Студент не найден
}


int main() {
    Student *root = nullptr;

    // Добавляем студентов в дерево
    addStudent(root, "Ivanov", 5, 4, 3, 5);
    addStudent(root, "Petrov", 4, 5, 4, 4);
    addStudent(root, "Sidorov", 3, 2, 2, 5);
    addStudent(root, "Smirnov", 2, 4, 2, 3);
    addStudent(root, "Safonov", 5, 4, 5, 4);

    cout << "First name up:" << endl;
    printInOrder(root);

    cout << endl << "First name down:" << endl;
    printReverseOrder(root);

    // Поиск студента по фамилии
    cout << endl << "Enter First name for seach: ";
    char searchSurname[50];
    cin.getline(searchSurname, 50);

    Student *foundStudent = findStudent(root, searchSurname);
    if (foundStudent != nullptr) {
        cout << "Student with first name " << searchSurname << " found." << endl;
        cout << "Student grades " << searchSurname << ": ";
        for (int i = 0; i < 4; ++i) {
            cout << foundStudent->grades[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Student with first name " << searchSurname << " not found." << endl;
    }

    return 0;
}