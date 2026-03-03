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

void solveSLAE(vector<vector<Fraction>> A) {
    int m = A.size();
    int n = A[0].size() - 1;

    int rank = 0;
    vector<int> pivotCol;

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
        cout << "Главный элемент: "
             << A[pivotRow][col]
             << " (строка " << pivotRow + 1
             << ", столбец " << col + 1 << ")\n";

        swap(A[rank], A[pivotRow]);

        Fraction pivot = A[rank][col];

        for (int j = col; j <= n; j++)
            A[rank][j] /= pivot;

        for (int i = 0; i < m; i++) {
            if (i == rank) continue;
            Fraction factor = A[i][col];
            for (int j = col; j <= n; j++)
                A[i][j] = A[i][j] - factor * A[rank][j];
        }

        pivotCol.push_back(col);

        cout << "Матрица после шага:\n";
        printMatrix(A);

        rank++;
    }

    // Проверка несовместности
    for (int i = rank; i < m; i++) {
        bool zero = true;
        for (int j = 0; j < n; j++)
            if (!A[i][j].isZero())
                zero = false;

        if (zero && !A[i][n].isZero()) {
            cout << "Система несовместна.\n";
            return;
        }
    }

    cout << "Ранг системы: " << rank << "\n";

    if (rank == n) {
        cout << "Единственное решение:\n";
        for (int i = 0; i < n; i++)
            cout << "x" << i + 1 << " = " << A[i][n] << "\n";
        return;
    }

    // Свободные переменные
    vector<int> freeVars;
    for (int j = 0; j < n; j++) {
        bool isPivot = false;
        for (int k : pivotCol)
            if (k == j)
                isPivot = true;
        if (!isPivot)
            freeVars.push_back(j);
    }

    cout << "Свободные переменные: ";
    for (int v : freeVars)
        cout << "x" << v + 1 << " ";
    cout << "\n\n";

    cout << "Базисные решения:\n";

    for (size_t freeIndex = 0; freeIndex < freeVars.size(); ++freeIndex) {

        vector<Fraction> solution(n, Fraction(0));

        solution[freeVars[freeIndex]] = Fraction(1);

        for (int i = 0; i < rank; i++) {
            int col = pivotCol[i];
            Fraction sum = A[i][n];

            for (size_t j = 0; j < freeVars.size(); ++j) {
                int freeCol = freeVars[j];
                sum = sum - A[i][freeCol] * solution[freeCol];
            }

            solution[col] = sum;
        }

        cout << "Решение " << freeIndex + 1 << ":\n";
        for (int i = 0; i < n; i++)
            cout << "x" << i + 1 << " = " << solution[i] << "\n";
        cout << "\n";
    }
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

    solveSLAE(A);

    return 0;
}