#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef struct student {
    char *name;
    int scores[4];
    struct student *next;
} student;

student *create_student(const char *i_name, int score1, int score2, int score3, int score4) {
    student *temp = (student *)malloc(sizeof(student));

    if (temp != NULL) {
        temp->name = strdup(i_name);
        temp->scores[0] = score1;
        temp->scores[1] = score2;
        temp->scores[2] = score3;
        temp->scores[3] = score4;
        temp->next = NULL;
    }

    return temp;
}

student *insert(student *head, const char *i_name, int score1, int score2, int score3, int score4) {
    student *new_student = create_student(i_name, score1, score2, score3, score4);

    if (head == NULL) {
        head = new_student;
    } else {
        student *cursor = head;
        while (cursor->next != NULL) {
            cursor = cursor->next;
        }

        cursor->next = new_student;
    }

    return head;
}

void print_students(student *list) {
    while (list) {
        cout << list->name << " " << list->scores[0] << " " << list->scores[1] << " " << list->scores[2] << " " << list->scores[3] << endl;
        list = list->next;
    }
}

void sort_students(student *head) {
    student *current = head;
    student *index = NULL;
    char temp_name[50];
    int temp_scores[4];

    if (head == NULL) {
        return;
    } else {
        while (current != NULL) {
            index = current->next;

            while (index != NULL) {
                if (strcmp(current->name, index->name) > 0) {
                    strcpy(temp_name, current->name);
                    strcpy(current->name, index->name);
                    strcpy(index->name, temp_name);

                    memcpy(temp_scores, current->scores, sizeof(int) * 4);
                    memcpy(current->scores, index->scores, sizeof(int) * 4);
                    memcpy(index->scores, temp_scores, sizeof(int) * 4);
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

int main() {
    student *students_list = NULL;

    students_list = insert(students_list, "Лера", 5, 4, 5, 5);
    students_list = insert(students_list, "Sasha", 4, 4, 5, 3);
    students_list = insert(students_list, "Katia", 3, 2, 5, 2);
    students_list = insert(students_list, "Danil", 2, 2, 4, 3);
    students_list = insert(students_list, "Andrey", 5, 2, 2, 3);

    cout << "First:" << endl;
    print_students(students_list);

    sort_students(students_list);

    cout << endl << "Sort:" << endl;
    print_students(students_list);

    return 0;
}
