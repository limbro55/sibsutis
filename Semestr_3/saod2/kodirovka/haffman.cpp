#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    double probability;
    vector<bool> code;
    Node* left;
    Node* right;

    Node(double p) : probability(p), left(nullptr), right(nullptr) {}
};

struct Encoding {
    char character = 0;
    float probability = 0;
    int length = 0;
    string codeword;
};

// Функция для вставки вероятности в массив P и сортировки его
int Up(vector<double>& P, double q) {
    int n = P.size();
    P.push_back(0);  // Увеличиваем размер массива для вставки нового элемента
    int i = n - 1;
    while (i >= 0 && P[i] <= q) {
        P[i + 1] = P[i];
        i--;
    }
    P[i + 1] = q;
    return i + 1;  // Возвращаем индекс вставленного элемента
}

// Функция для формирования кодовых слов
void Down(vector<Node*>& nodes, int j) {
    vector<bool> S = nodes[j]->code;  // Сохраняем кодовую последовательность j-го узла
    int L = nodes[j]->code.size();  // Длина кода

    for (int i = j; i < nodes.size() - 1; ++i) {
        nodes[i] = nodes[i + 1];  // Сдвигаем узлы вверх
    }

    nodes[nodes.size() - 2]->code = S;
    nodes[nodes.size() - 1]->code = S;
    nodes[nodes.size() - 2]->code.push_back(0);
    nodes[nodes.size() - 1]->code.push_back(1);
}

void Huffman(int n, vector<double>& P, vector<Node*>& nodes) {
    if (n == 2) {
        nodes[0]->code.push_back(0);
        nodes[1]->code.push_back(1);
    } else {
        double q = P[n - 1] + P[n - 2];
        int j = Up(P, q);
        Huffman(n - 1, P, nodes);
        Down(nodes, j);
    }
}

int main() {
    int n;
    cout << "Введите количество символов: ";
    cin >> n;

    vector<double> P(n);
    cout << "Введите вероятности: ";
    for (int i = 0; i < n; ++i) {
        cin >> P[i];
    }

    // Создаем узлы для каждого символа
    vector<Node*> nodes;
    for (double p : P) {
        nodes.push_back(new Node(p));
    }

    sort(P.rbegin(), P.rend());  // Сортируем вероятности по убыванию

    Huffman(n, P, nodes);

    // Выводим коды
    for (int i = 0; i < nodes.size(); ++i) {
        cout << "Символ " << i + 1 << " код: ";
        for (bool bit : nodes[i]->code) {
            cout << bit;
        }
        cout << endl;
        delete nodes[i];  // Освобождаем память
    }

    return 0;
}
