#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;


struct Student {
    char *surname;
    int grades[4];
    Student *prev;
    Student *next;
};


Student *createStudent(const char *surname, int grade1, int grade2, int grade3, int grade4) {
    Student *newStudent = new Student;
    newStudent->surname = strdup(surname);
    newStudent->grades[0] = grade1;
    newStudent->grades[1] = grade2;
    newStudent->grades[2] = grade3;
    newStudent->grades[3] = grade4;
    newStudent->prev = nullptr;
    newStudent->next = nullptr;
    return newStudent;
}


void new_stud(Student *&head, const char *surname, int grade1, int grade2, int grade3, int grade4) {
    Student *newStudent = createStudent(surname, grade1, grade2, grade3, grade4);
    if (head == nullptr) {
        head = newStudent;
    } else {
        Student *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newStudent;
        newStudent->prev = current;
    }
}


void delete_st(Student *&head, Student *studentToDelete) {
    if (studentToDelete == nullptr) {
        return;
    }
    if (studentToDelete == head) {
        head = head->next;
    }
    if (studentToDelete->prev != nullptr) {
        studentToDelete->prev->next = studentToDelete->next;
    }
    if (studentToDelete->next != nullptr) {
        studentToDelete->next->prev = studentToDelete->prev;
    }
    delete studentToDelete;
}

// Функция для проверки оценок студента
bool hasFailingGrade(Student *student) {
    for (int i = 0; i < 4; ++i) {
        if (student->grades[i] < 3) {
            return true;
        }
    }
    return false; // Все оценки удовлетворительные
}


void print_st(Student *head) {
    Student *current = head;
    while (current != nullptr) {
        cout << current->surname << " ";
        for (int i = 0; i < 4; ++i) {
            cout << current->grades[i] << " ";
        }
        cout << endl;
        current = current->next;
    }
}

// Функция для удаления студентов с неудовлетворительными оценками
void del_st(Student *&head) {
    Student *current = head;
    while (current != nullptr) {
        if (hasFailingGrade(current)) {
            Student *studentToDelete = current;
            current = current->next;
            delete_st(head, studentToDelete);
        } else {
            current = current->next;
        }
    }
}


int main() {
    Student *studentsList = nullptr;

    new_stud(studentsList, "Ivanov", 5, 4, 3, 5);
    new_stud(studentsList, "Petrov", 4, 5, 3, 4);
    new_stud(studentsList, "Sidorov", 3, 2, 1, 3);
    new_stud(studentsList, "Smirnov", 2, 5, 4, 3);
    new_stud(studentsList, "Safonov", 5, 3, 4, 5);

    cout << "First:" << endl;
    print_st(studentsList);

    del_st(studentsList);

    cout << endl << "Befor delete:" << endl;
    print_st(studentsList);

    return 0;
}

