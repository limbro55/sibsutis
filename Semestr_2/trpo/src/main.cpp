#include "typing_trainer.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int EASY_LENGTH = 30;
const int MEDIUM_LENGTH = 50;
const int HARD_LENGTH = 100;

int main() {
    srand(static_cast<unsigned int>(time(0))); // инициализация генератора случайных чисел
    char choice;
    do {
        cout << "Выберите действие:" << endl;
        cout << "1. Начать новый тест" << endl;
        cout << "2. Посмотреть предыдущие результаты" << endl;
        cout << "3. Выйти" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                int difficulty;
                cout << "Выберите уровень сложности: 1. Легкий 2. Средний 3. Сложный: ";
                cin >> difficulty;
                int stringLength;
                if (difficulty == 1) {
                    stringLength = EASY_LENGTH;
                } else if (difficulty == 2) {
                    stringLength = MEDIUM_LENGTH;
                } else if (difficulty == 3) {
                    stringLength = HARD_LENGTH;
                } else {
                    cout << "Неправильный выбор. Используется средний уровень сложности." << endl;
                    stringLength = MEDIUM_LENGTH;
                }
                startTypingTest(stringLength);
                break;
            }
            case '2':
                viewResults();
                break;
            case '3':
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неправильный выбор, попробуйте снова." << endl;
        }
    } while (choice != '3');

    return 0;
}
