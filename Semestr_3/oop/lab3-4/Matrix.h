#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>


using namespase std;

template <typename T> class Matrix {
private:
  T **M;
  int m;
  int n;

public:
  // 1. Конструктор по умолчанию
  Matrix() : M(nullptr), m(0), n(0) {}

  Matrix(int rows, int cols) : m(rows), n(cols) {
    if (m > 0 && n > 0) {
      M = new T *[m];
      for (int i = 0; i < m; ++i) {
        M[i] = new T[n];
        for (int j = 0; j < n; ++j) {
          M[i][j] = 0;
        }
      }
    } else {
      M = nullptr;
      m = n = 0;
    }
  }

  // 3. Конструктор копирования
  Matrix(const Matrix<T> &other) : m(other.m), n(other.n) {
    if (other.M) {
      M = new T *[m];
      for (int i = 0; i < m; ++i) {
        M[i] = new T[n];
        for (int j = 0; j < n; ++j) {
          M[i][j] = other.M[i][j];
        }
      }
    } else {
      M = nullptr;
      m = n = 0;
    }
  }

  // 4. Оператор присваивания
  Matrix<T> &operator=(const Matrix<T> &other) {
    if (this == &other)
      return *this; // Проверка самоприсваивания

    if (M) {
      for (int i = 0; i < m; ++i)
        delete[] M[i];
      delete[] M;
    }

    // Копируем новые размеры
    m = other.m;
    n = other.n;

    // Копируем данные
    if (other.M) {
      M = new T *[m];
      for (int i = 0; i < m; ++i) {
        M[i] = new T[n];
        for (int j = 0; j < n; ++j) {
          M[i][j] = other.M[i][j];
        }
      }
    } else {
      M = nullptr;
      m = n = 0;
    }

    return *this;
  }

  // 5. Метод для установки элемента матрицы
  void SetM(int row, int col, T value) {
    if (row >= 0 && row < m && col >= 0 && col < n) {
      M[row][col] = value;
    } else {
      cout << "Ошибка: Индекс выходит за пределы матрицы.\n";
    }
  }

  // 6. Метод для получения элемента матрицы
  T GetM(int row, int col) const {
    if (row >= 0 && row < m && col >= 0 && col < n) {
      return M[row][col];
    } else {
      cout << "Ошибка: Индекс выходит за пределы матрицы.\n";
      return T();
    }
  }

  void Print(const string &name) const {
    cout << "Object: " << name << "\n";
    if (M) {
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          cout << setw(5) << M[i][j] << " ";
        }
        cout << "\n";
      }
      cout << "---------------------\n";
    } else {
      cout << "Матрица пуста.\n---------------------\n";
    }
  }

  // 8. Деструктор
  ~Matrix() {
    if (M) {
      for (int i = 0; i < m; ++i)
        delete[] M[i];
      delete[] M;
    }
  }
};
