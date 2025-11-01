#include "../include/typing_trainer.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

std::string generateRandomString(int length) {
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string randomString;
    for (int i = 0; i < length; ++i) {
        randomString += characters[rand() % characters.size()];
    }
    return randomString;
}

void saveResult(double time, int errors, double wpm) {
    ofstream outFile("typing_results.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "Time: " << time << "s, Errors: " << errors << ", WPM: " << wpm << endl;
        outFile.close();
    } else {
        cerr << "Не удалось открыть файл для записи результатов." << endl;
    }
}

void viewResults() {
    ifstream inFile("typing_results.txt");
    if (inFile.is_open()) {
        string line;
        cout << "Результаты предыдущих тестов:" << endl;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cerr << "Не удалось открыть файл для чтения результатов." << endl;
    }
}

void startTypingTest(int stringLength) {
    string testString = generateRandomString(stringLength);
    cout << "Введите следующую строку:" << endl;
    cout << testString << endl;

    auto start = steady_clock::now();
    string userInput;
    cin.ignore(); // очистка буфера ввода
    getline(cin, userInput);
    auto end = steady_clock::now();

    duration<double> elapsed_seconds = end - start;

    int correctChars = 0;
    for (int i = 0; i < min(testString.length(), userInput.length()); ++i) {
        if (testString[i] == userInput[i]) {
            ++correctChars;
        }
    }

    int errors = stringLength - correctChars;
    double wpm = (correctChars / (elapsed_seconds.count() / 60.0)) / 5.0;

    cout << "Ваше время: " << elapsed_seconds.count() << " секунд" << endl;
    cout << "Количество ошибок: " << errors << endl;
    cout << "Скорость печати: " << wpm << " слов в минуту" << endl;

    saveResult(elapsed_seconds.count(), errors, wpm);
}