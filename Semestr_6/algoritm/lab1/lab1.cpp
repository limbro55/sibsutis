#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>

using namespace std;

class Fraction {
private:
    long long num, den;

    void normalize() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        long long g = gcd(llabs(num), llabs(den));
        if (g != 0) {
            num /= g;
            den /= g;
        }
    }

public:
    Fraction(long long n = 0, long long d = 1) : num(n), den(d) {
        normalize();
    }

    bool isZero() const { return num == 0; }
    long long absNum() const { return llabs(num); }

    Fraction operator+(const Fraction& o) const {
        return Fraction(num * o.den + o.num * den, den * o.den);
    }

    Fraction operator-(const Fraction& o) const {
        return Fraction(num * o.den - o.num * den, den * o.den);
    }

    Fraction operator*(const Fraction& o) const {
        return Fraction(num * o.num, den * o.den);
    }

    Fraction operator/(const Fraction& o) const {
        return Fraction(num * o.den, den * o.num);
    }

    Fraction& operator/=(const Fraction& o) {
        *this = *this / o;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Fraction& f) {
        if (f.den == 1) os << f.num;
        else os << f.num << "/" << f.den;
        return os;
    }
};

void printMatrix(const vector<vector<Fraction>>& A) {
    for (auto& row : A) {
        for (auto& x : row)
            cout << x << "\t";
        cout << "\n";
    }
    cout << "----------------------------------\n";
}

bool solveSLAE(vector<vector<Fraction>>& A, vector<Fraction>& x) {
    int m = A.size();
    int n = A[0].size() - 1;

    int rank = 0;

    for (int col = 0; col < n && rank < m; col++) {

        int pivotRow = -1;
        for (int i = rank; i < m; i++) {
            if (!A[i][col].isZero()) {
                pivotRow = i;
                break;
            }
        }

        if (pivotRow == -1)
            continue;

        cout << "Шаг " << rank + 1 << "\n";
        cout << "Выбран главный элемент: "
             << A[pivotRow][col]
             << " (строка " << pivotRow + 1
             << ", столбец " << col + 1 << ")\n";

        swap(A[rank], A[pivotRow]);

        Fraction pivot = A[rank][col];

        // Нормализация строки
        for (int j = col; j <= n; j++)
            A[rank][j] /= pivot;

        // Обнуление остальных строк
        for (int i = 0; i < m; i++) {
            if (i == rank) continue;
            Fraction factor = A[i][col];
            for (int j = col; j <= n; j++)
                A[i][j] = A[i][j] - factor * A[rank][j];
        }

        cout << "Матрица после шага:\n";
        printMatrix(A);

        rank++;
    }

    // Проверка на несовместность
    for (int i = 0; i < m; i++) {
        bool allZero = true;
        for (int j = 0; j < n; j++)
            if (!A[i][j].isZero())
                allZero = false;

        if (allZero && !A[i][n].isZero()) {
            cout << "Система несовместна.\n";
            return false;
        }
    }

    if (rank < n) {
        cout << "Система имеет бесконечно много решений.\n";
        cout << "Ранг = " << rank
             << ", число неизвестных = " << n << "\n";
        return false;
    }

    // Единственное решение
    x.assign(n, Fraction(0));

    for (int i = 0; i < n; i++)
        x[i] = A[i][n];

    return true;
}

int main() {
    ifstream fin("matrix.txt");
    if (!fin) {
        cout << "Ошибка открытия файла\n";
        return 1;
    }

    int m, n;
    fin >> m >> n;

    vector<vector<Fraction>> A(m, vector<Fraction>(n+1));

    for (int i = 0; i < m; i++)
        for (int j = 0; j <= n; j++) {
            long long t;
            fin >> t;
            A[i][j] = Fraction(t);
        }

    fin.close();

    cout << "Исходная матрица:\n";
    printMatrix(A);

    vector<Fraction> x;

    if (!solveSLAE(A, x))
        return 0;

    cout << "Единственное решение системы:\n";
    for (int i = 0; i < n; i++)
        cout << "x" << i + 1 << " = " << x[i] << "\n";

    return 0;
}