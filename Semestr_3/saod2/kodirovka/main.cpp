#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct SymbolCode {
    char symbol;
    double probability;
    std::string code;
    int length;
};

// Чтение файла и вычисление вероятностей символов
void calculateProbabilities(const std::string& filename, std::vector<SymbolCode>& symbolCodes) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        exit(1);
    }

    int frequencies[256] = {0};
    char ch;
    int total_chars = 0;

    while (file.get(ch)) {
        frequencies[(unsigned char)ch]++;
        total_chars++;
    }
    file.close();

    for (int i = 0; i < 256; ++i) {
        if (frequencies[i] > 0) {
            SymbolCode code;
            code.symbol = (char)i;
            code.probability = (double)frequencies[i] / total_chars;
            symbolCodes.push_back(code);
        }
    }
}

// Код Шеннона
void buildShannonCode(std::vector<SymbolCode>& symbolCodes) {
    std::sort(symbolCodes.begin(), symbolCodes.end(), [](const SymbolCode& a, const SymbolCode& b) {
        return a.probability > b.probability;
    });

    double Q = 0.0;
    for (auto& symbolCode : symbolCodes) {
        Q += symbolCode.probability;
        int L = static_cast<int>(std::ceil(-std::log2(symbolCode.probability)));
        symbolCode.length = L;

        double Q_start = Q - symbolCode.probability;
        std::string code;

        for (int j = 0; j < L; ++j) {
            Q_start *= 2;
            int bit = static_cast<int>(Q_start);
            code += std::to_string(bit);
            Q_start -= bit;
        }

        symbolCode.code = code;
    }
}

// Медиана для Фано
int med(const std::vector<SymbolCode>& symbols, int L, int R) {
    double SL = 0;
    int m = R;

    if(L<=R){
        for (int i = L; i <= R - 1; ++i) {
            SL += symbols[i].probability;
        }

        double SR = symbols[R].probability;

        while (SL >= SR && m > L) {
            m--;
            SL -= symbols[m].probability;
            SR += symbols[m].probability;
        }
    }
    return m;
    
}

// Код Фано
void fano(std::vector<SymbolCode>& symbols, int L, int R, int currentLength = 0) {
    if (L < R) {
        int m = med(symbols, L, R);
        for (int i = L; i <= R; ++i) {
            symbols[i].code += (i <= m ? '0' : '1');
            symbols[i].length = currentLength + 1;
        }
        fano(symbols, L, m, currentLength + 1);
        fano(symbols, m + 1, R, currentLength + 1);
    }
}

// Алгоритм Хаффмена (с использованием up и down)
int up(float*& P, int n, float q) {

    int j = 0;

    for (int i = n - 2; i > 0; i--) {
        if (P[i - 1] <= q) {
            P[i] = P[i - 1];
        } else {
            j = i;
            break;
        }
    }
    P[j] = q;
    return j;
}

void down(std::vector<SymbolCode>& symbols, int n, int j) { 
    string S = symbols[j].code;
    int L = symbols[j].length;

    for (int i = j; i < n - 1; ++i) {
        symbols[i].code = symbols[i + 1].code;
        symbols[i].length = symbols[i + 1].length;
    }

    symbols[n - 1].length = L + 1;
    symbols[n - 2].code = symbols[n - 1].code = S;

    symbols[n - 2].code = S + "0";
    symbols[n- 1 ].code = S + "1";

    symbols[n-2].length = symbols[n-1].length =  L + 1;
}

void huffmanCode(std::vector<SymbolCode>& symbols, float*& P, int n) {
    if (n == 2) {
        symbols[0].code = "0";
        symbols[1].code = "1";
        symbols[1].length = 1;
    } else {
        float q = P[n - 2] + P[n - 1];
        int j = up(P, n, q);
        huffmanCode(symbols, P, n - 1);
        down(symbols, n - 1, j);
    }
}

void buildHuffmanCode(vector<SymbolCode>& symbolCodes) {
    vector<SymbolCode> symbols = symbolCodes;
    int n = symbols.size();
    float* P = new float[n];

    for (int i = 0; i < n; ++i) {
        P[i] = symbols[i].probability;
    }

    huffmanCode(symbols, P, n);
    symbolCodes = symbols;

    delete[] P;
}

void buildGilbertMooreCode(vector<SymbolCode>& symbolCodes) {
    sort(symbolCodes.begin(), symbolCodes.end(), [](const SymbolCode& a, const SymbolCode& b) {
        return a.probability > b.probability;
    });

    double pr = 0.0; // Инициализация промежуточной суммы вероятностей

    // Расчет Qi и длин кодов
    for (auto& symbolCode : symbolCodes) {
        double Q = pr + symbolCode.probability / 2.0;
        pr += symbolCode.probability;

        int L = static_cast<int>(std::ceil(-std::log2(symbolCode.probability))) + 1;
        symbolCode.length = L;

        string binaryCode;
        for (int j = 0; j < L; ++j) {
            Q *= 2; // Умножение на 2
            int bit = static_cast<int>(Q); // Целая часть
            binaryCode += std::to_string(bit); // Добавляем бит к коду
            if (Q >= 1.0) {
                Q -= 1.0; // Убираем целую часть
            }
        }
        symbolCode.code = binaryCode;
    }
}

// Вычисление энтропии
double calculateEntropy(const std::vector<SymbolCode>& symbolCodes) {
    double entropy = 0.0;
    for (const auto& symbolCode : symbolCodes) {
        entropy -= symbolCode.probability * std::log2(symbolCode.probability);
    }
    return entropy;
}

// Средняя длина кодового слова
double averageCodeLength(const std::vector<SymbolCode>& symbolCodes) {
    double avg_length = 0.0;
    for (const auto& symbolCode : symbolCodes) {
        avg_length += symbolCode.probability * symbolCode.length;
    }
    return avg_length;
}

// Кодирование текста
std::string encodeText(const std::string& filename, const std::vector<SymbolCode>& symbolCodes, int& encodedBits) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        exit(1);
    }

    std::string encodedText;
    char ch;
    while (file.get(ch)) {
        for (const auto& code : symbolCodes) {
            if (code.symbol == ch) {
                encodedText += code.code;
                break;
            }
        }
    }
    file.close();

    encodedBits = encodedText.size();
    return encodedText;
}

// Коэффициент сжатия
double calculateCompressionRatio(int originalSize, int encodedBits) {
    return static_cast<double>(encodedBits) / (originalSize * 8) * 100;
}

// Основная программа
int main() {
    std::string filename = "text.txt";
    std::vector<SymbolCode> symbolCodes;

    calculateProbabilities(filename, symbolCodes);

    // Код Шеннона
    std::vector<SymbolCode> shannonCodes = symbolCodes;
    buildShannonCode(shannonCodes);

    // Код Фано
    std::vector<SymbolCode> fanoCodes = symbolCodes;
    std::sort(fanoCodes.begin(), fanoCodes.end(), [](const SymbolCode& a, const SymbolCode& b) {
        return a.probability > b.probability;
    });
    fano(fanoCodes, 0, fanoCodes.size() - 1);

    // Код Хаффмена
    std::vector<SymbolCode> huffmanCodes = symbolCodes;
    buildHuffmanCode(huffmanCodes);

    // Код Гилберта-Мура
    std::vector<SymbolCode> gilbertMooreCodes = symbolCodes;
    buildGilbertMooreCode(gilbertMooreCodes);

    // Энтропия
    double entropy = calculateEntropy(symbolCodes);

    // Размер исходного файла
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    int originalSize = file.tellg();
    file.close();

    // Кодирование текста
    int shannonBits, fanoBits, huffmanBits, gilbertBits;
    encodeText(filename, shannonCodes, shannonBits);
    encodeText(filename, fanoCodes, fanoBits);
    encodeText(filename, huffmanCodes, huffmanBits);
    encodeText(filename,gilbertMooreCodes,gilbertBits);

    // Коэффициенты сжатия
    double shannonCompression = calculateCompressionRatio(originalSize, shannonBits);
    double fanoCompression = calculateCompressionRatio(originalSize, fanoBits);
    double huffmanCompression = calculateCompressionRatio(originalSize, huffmanBits);
    double gilbertCompression = calculateCompressionRatio(originalSize, gilbertBits);

    // Вывод результатов
    std::cout << "Энтропия исходного текста: " << entropy << "\n";

    std::cout << "\nКод Шеннона:\n";
    std::cout << "Средняя длина кодового слова: " << averageCodeLength(shannonCodes) << "\n";
    std::cout << "Коэффициент сжатия: " << shannonCompression << "%\n";

     // Вывод результатов
    std::cout << "\nКод Шеннона:\n";
    for (const auto& code : shannonCodes) {
        std::cout << "Символ: " << code.symbol << ", Код: " << code.code
                  << ", Длина: " << code.length << "\n";
    }

    std::cout << "\nКод Фано:\n";
    std::cout << "Средняя длина кодового слова: " << averageCodeLength(fanoCodes) << "\n";
    std::cout << "Коэффициент сжатия: " << fanoCompression << "%\n";

     // Вывод результатов
    std::cout << "\nКод Фано:\n";
    for (const auto& code : fanoCodes) {
        std::cout << "Символ: " << code.symbol << ", Код: " << code.code
                  << ", Длина: " << code.length << "\n";
    }

    std::cout << "\nКод Хаффмена:\n";
    std::cout << "Средняя длина кодового слова: " << averageCodeLength(huffmanCodes) << "\n";
    std::cout << "Коэффициент сжатия: " << huffmanCompression << "%\n";

     // Вывод результатов
    // std::cout << "\nКод Хаффмена:\n";
    // for (const auto& code : huffmanCodes) {
    //     std::cout << "Символ: " << code.symbol << ", Код: " << code.code
    //               << ", Длина: " << code.length << "\n";
    // }

    std::cout << "\n Код Гулберта Мура: \n";
    std::cout << "Средняя длина кодового слова: " << averageCodeLength(gilbertMooreCodes) << "\n";
    std::cout << "Коэффициент сжатия: " << gilbertCompression << "%\n";

    // Вывод результатов
    std::cout << "\nКод Гилберта-Мура:\n";
    for (const auto& code : gilbertMooreCodes) {
        std::cout << "Символ: " << code.symbol << ", Код: " << code.code
                  << ", Длина: " << code.length << "\n";
    }

    return 0;
}
