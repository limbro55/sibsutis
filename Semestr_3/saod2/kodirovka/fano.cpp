#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

// Структура для хранения символов и их кодов
struct Symbol {
    char character;
    double probability;
    string code;
    int length;
};

// Функция для вычисления медианы
int Med(const vector<Symbol>& symbols, int L, int R) {
    double SL = 0;
    for (int i = L; i <= R - 1; ++i) {
        SL += symbols[i].probability;
    }
    double SR = symbols[R].probability;
    int m = R;
    while (SL >= SR && m > L) {
        m--;
        SL -= symbols[m].probability;
        SR += symbols[m].probability;
    }
    return m;
}

// Алгоритм Фано
void Fano(vector<Symbol>& symbols, int L, int R, int k) {
    if (L < R) {
        k++;
        int m = Med(symbols, L, R);
        for (int i = L; i <= R; ++i) {
            if (i <= m) {
                symbols[i].code += '0';
            } else {
                symbols[i].code += '1';
            }
        }
        Fano(symbols, L, m, k);
        Fano(symbols, m + 1, R, k);
    }
}

// Вычисление энтропии
double calculateEntropy(const std::vector<Symbol>& symbolCodes) {
    double entropy = 0.0;
    for (const auto& Symbol : symbolCodes) {
        entropy -= Symbol.probability * std::log2(Symbol.probability);
    }
    return entropy;
}

// Средняя длина кодового слова
double averageCodeLength(const std::vector<Symbol>& symbolCodes) {
    double avg_length = 0.0;
    for (const auto& Symbol : symbolCodes) {
        avg_length += Symbol.probability * Symbol.length;
    }
    return avg_length;
}


// Проверка неравенства Крафта
bool kraftInequality(const std::vector<Symbol>& symbols) {
    double kraft_sum = 0.0;
    for (const auto& Symbol : symbols) {
        kraft_sum += pow(2, -Symbol.length);
    }
    cout << "\nПроверка неравенства Крафта: сумма = " << kraft_sum << " (должна быть <= 1)\n";
    return kraft_sum <= 1.0;
}

int main() {
    // Чтение текста из файла
    ifstream file("text.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл text.txt" << endl;
        return 1;
    }

    // Подсчет частот символов
    unordered_map<char, int> frequency;
    char ch;
    while (file.get(ch)) {
        frequency[ch]++;
    }
    file.close();

    // Создание вектора символов с вероятностями
    vector<Symbol> symbols;
    int totalChars = 0;
    for (const auto& pair : frequency) {
        totalChars += pair.second;
    }
    for (const auto& pair : frequency) {
        symbols.push_back({pair.first, static_cast<double>(pair.second) / totalChars, ""});
    }

    // Сортировка символов по вероятностям
    sort(symbols.begin(), symbols.end(), [](const Symbol& a, const Symbol& b) {
        return a.probability > b.probability;
    });

    // Применение алгоритма Фано
    Fano(symbols, 0, symbols.size() - 1, -1);

    // Вывод кодов
    for (const auto& symbol : symbols) {
        cout << "Символ: " << symbol.character << ", Код: " << symbol.code << endl;
    }

    // Проверка выполнения неравенства Крафта
    bool kraft_result = kraftInequality(symbols);
    std::cout << "Неравенство Крафта выполняется: " << (kraft_result ? "Да" : "Нет") << "\n";

    return 0;
}
