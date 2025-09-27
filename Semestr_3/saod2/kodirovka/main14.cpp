#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

using namespace std;

#define d 256

int directSearch(const wstring &text, const wstring &pattern) {
    int textLen = text.length();
    int patternLen = pattern.length();
    int comparisonCount = 0;

    wcout << L"Прямой поиск:\n";
    for (int i = 0; i <= textLen - patternLen; i++) {
        int j;
        for (j = 0; j < patternLen; j++) {
            comparisonCount++;
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == patternLen) {
            wcout << L"Найдено вхождение: индекс " << i << L"\n";
        }
    }
    return comparisonCount;
}

int rabinKarpSearch(const wstring &text, const wstring &pattern) {
    int n = text.length();
    int m = pattern.length();
    int q = 101;
    int p = 0;
    int t = 0;
    int h = 1;
    int comparisonCount = 0;

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    wcout << L"Метод Рабина-Карпа:\n";
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            int j;
            for (j = 0; j < m; j++) {
                comparisonCount++;
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m) {
                wcout << L"Найдено вхождение: индекс " << i << L"\n";
            }
        } else {
            comparisonCount++;
        }

        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
    return comparisonCount;
}

int main() {
    try {
        // Установка локали
        locale loc("");
        locale::global(loc);
        wcin.imbue(loc);
        wcout.imbue(loc);

        // Строка текста
        wstring text = L"aacabusnaabhdyvhd";
        wstring pattern = L"aab";

        wcout << L"Текст: " << text << L"\n";
        wcout << L"Подстрока: " << pattern << L"\n";

        // Поиск подстроки
        int directComparisons = directSearch(text, pattern);
        wcout << endl;
        int rabinKarpComparisons = rabinKarpSearch(text, pattern);

        wcout << L"\nКоличество сравнений:\n";
        wcout << L"Прямой поиск: " << directComparisons << L"\n";
        wcout << L"Метод Рабина-Карпа: " << rabinKarpComparisons << L"\n";

    } catch (const std::exception &e) {
        wcerr << L"Ошибка: " << e.what() << L"\n";
        return 1;
    }

    return 0;
}
