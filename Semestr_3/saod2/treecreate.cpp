#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

struct Encoding {
    char character = 0;
    float probability = 0;
    float q = 0;
    int length = 0;
    char* codeword = nullptr;
};

void calculate_probabilities(
        const std::string& filename, std::vector<Encoding>& symbols)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return;
    }

    std::unordered_map<char, float> frequency;
    int total_characters = 0;
    char ch;
    while (file.get(ch)) {
        frequency[ch]++;
        total_characters++;
    }

    for (const auto& pair : frequency) {
        Encoding symbol;
        symbol.character = pair.first;
        symbol.probability = (float)(pair.second) / total_characters;
        symbols.push_back(symbol);
    }

    file.close();
}

void quick_sort(std::vector<Encoding>& symbols, int left, int right)
{
    Encoding x = symbols[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (symbols[i].probability > x.probability) {
            i++;
        }
        while (symbols[j].probability < x.probability) {
            j--;
        }

        if (i <= j) {
            Encoding temp = symbols[i];
            symbols[i] = symbols[j];
            symbols[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        quick_sort(symbols, left, j);
    }
    if (i < right) {
        quick_sort(symbols, i, right);
    }
}

Encoding* shannon(Encoding*& symbol, int alphabet_size)
{
    Encoding* shannon = new Encoding[alphabet_size];
    float cumulative_probability = 0;

    for (int i = 0; i < alphabet_size; i++) {
        shannon[i].character = symbol[i].character;
        shannon[i].probability = symbol[i].probability;
        shannon[i].length = (int)ceil(log2(1 / shannon[i].probability));
        shannon[i].q = cumulative_probability;
        cumulative_probability += shannon[i].probability;
    }

    for (int i = 0; i < alphabet_size; i++) {
        float temp = shannon[i].q;
        shannon[i].codeword = new char[shannon[i].length + 1];

        for (int j = 0; j < shannon[i].length; j++) {
            temp *= 2;
            shannon[i].codeword[j] = (char)(floor(temp) + '0');

            if (temp >= 1) {
                temp -= 1;
            }
        }
        shannon[i].codeword[shannon[i].length] = '\0';
    }

    return shannon;
}

std::string
encode_file(Encoding* shannon, const std::string& filename, int message_size)
{
    std::ifstream file(filename);
    std::string encoded_text;
    char symbol;

    while (file.get(symbol)) {
        for (int i = 0; i < message_size; i++) {
            if (shannon[i].character == symbol) {
                encoded_text += shannon[i].codeword;
                break;
            }
        }
    }

    file.close();

    return encoded_text;
}

float calculate_entropy(Encoding* shannon, int alphabet_size)
{
    float entropy = 0;

    for (int i = 0; i < alphabet_size; i++) {
        entropy += (shannon[i].probability * log2(shannon[i].probability));
    }

    return -entropy;
}

float calculate_average_length(Encoding* shannon, int alphabet_size)
{
    float average_length = 0;

    for (int i = 0; i < alphabet_size; i++) {
        average_length += shannon[i].length * shannon[i].probability;
    }

    return average_length;
}

bool craft_inequality(Encoding* shannon, int alphabet_size)
{
    float sum = 0;

    for (int i = 0; i < alphabet_size; i++) {
        sum += pow(2, -shannon[i].length);
    }

    return sum <= 1;
}

int main()
{
    std::string filename = "file.txt";
    std::vector<Encoding> symbols;

    calculate_probabilities(filename, symbols);
    quick_sort(symbols, 0, symbols.size() - 1);

    Encoding* chanceSymbols = symbols.data();
    Encoding* code = shannon(chanceSymbols, symbols.size());}