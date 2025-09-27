#include <iostream>
#include <iomanip>
#include <cstdlib> 
#include <ctime>    
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    int** data;
    long long sum;

public:
    // 1a. Конструктор по умолчанию (0x0 матрица)
    Matrix() : rows(0), cols(0), sum(0) {
        data = nullptr;
    }

    // 1b. Конструктор для единичной квадратной матрицы заданного размера
    Matrix(int size) : rows(size), cols(size), sum(0) {
        if (size > 0) {
            data = new int*[rows];
            for(int i = 0; i < rows; ++i) {
                data[i] = new int[cols];
                for(int j = 0; j < cols; ++j) {
                    data[i][j] = (i == j) ? 1 : 0;
                }
            }
        } else {
            data = nullptr;
        }
    }

    // 1c. Конструктор для матрицы заданной размерности
    Matrix(int r, int c) : rows(r), cols(c), sum(0) {
        if(r > 0 && c > 0) {
            data = new int*[rows];
            for(int i = 0; i < rows; ++i) {
                data[i] = new int[cols];
                for(int j = 0; j < cols; ++j) {
                    data[i][j] = 0;
                }
            }
        } else {
            data = nullptr;
        }
    }

    // Копирующий конструктор (для корректной работы с динамической памятью)
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), sum(other.sum) {
        if(other.data) {
            data = new int*[rows];
            for(int i = 0; i < rows; ++i) {
                data[i] = new int[cols];
                for(int j = 0; j < cols; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        } else {
            data = nullptr;
        }
    }

    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if(this == &other) return *this;

        for(int i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;

        // Копируем новые значения
        rows = other.rows;
        cols = other.cols;
        sum = other.sum;

        if(other.data) {
            data = new int*[rows];
            for(int i = 0; i < rows; ++i) {
                data[i] = new int[cols];
                for(int j = 0; j < cols; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        } else {
            data = nullptr;
        }
        return *this;
    }

    // 3. Ввод значений матрицы с клавиатуры
    void input() {
        if(data) {
            cout << "Введите элементы матрицы (" << rows << "x" << cols << "):\n";
            for(int i = 0; i < rows; ++i) {
                for(int j = 0; j < cols; ++j) {
                    cin >> data[i][j];
                }
            }
        } else {
            cout << "Матрица пустая.\n";
        }
    }

    // 4. Заполнение матрицы случайными числами
    void fillRandom(int min = 0, int max = 10) {
        if(data) {
            srand(time(0)); 
            for(int i = 0; i < rows; ++i) {
                for(int j = 0; j < cols; ++j) {
                    data[i][j] = min + rand() % (max - min + 1);
                }
            }
        } else {
            cout << "Матрица пустая.\n";
        }
    }

    // 5. Вывод матрицы на экран
    void print() const {
        if(data) {
            for(int i = 0; i < rows; ++i) {
                for(int j = 0; j < cols; ++j) {
                    cout << setw(5) << data[i][j] << " ";
                }
                cout << endl;
            }
        } else {
            cout << "Матрица пустая.\n";
        }
    }

    // 6. Подсчет суммы элементов матрицы
    void calculateSum() {
        sum = 0;
        if(data) {
            for(int i = 0; i < rows; ++i)
                for(int j = 0; j < cols; ++j)
                    sum += data[i][j];
        }
    }

    // Получение суммы  
    long long getSum() const {
        return sum;
    }

    // Деструктор
    ~Matrix() {
        if(data) {
            for(int i = 0; i < rows; ++i)
                delete[] data[i];
            delete[] data;
        }
    }

    // Дополнительный метод для задания элементов как произведение индексов
    void setProductOfIndices() {
        if(data) {
            for(int i = 0; i < rows; ++i)
                for(int j = 0; j < cols; ++j)
                    data[i][j] = (i + 1) * (j + 1);
        }
    }
};

int main() {
    // Создание матриц
    Matrix M1;         
    Matrix M2(3);         
    Matrix M3(3, 4);       
    Matrix M4(2, 3);       

    // Вывод матриц M2, M3, M4
    cout << "Матрица M2 (единичная 3x3):\n";
    M2.print();
    cout << "\nМатрица M3 (3x4, заполнена нулями):\n";
    M3.print();
    cout << "\nМатрица M4 (2x3, заполнена нулями):\n";
    M4.print();

    // Заполнение M2 как произведение номеров строки и столбца
    M2.setProductOfIndices();
    cout << "\nМатрица M2 после заполнения произведениями индексов:\n";
    M2.print();

    // Заполнение M3 случайными числами
    M3.fillRandom(1, 100); // Диапазон случайных чисел от 1 до 100
    cout << "\nМатрица M3 после заполнения случайными числами:\n";
    M3.print();

    // Заполнение M4 вводом с клавиатуры
    cout << "\nВведите элементы матрицы M4 (2x3):\n";
    M4.input();
    cout << "\nМатрица M4 после ввода с клавиатуры:\n";
    M4.print();

    // Подсчет суммы элементов M3
    M3.calculateSum();
    cout << "\nСумма элементов матрицы M3: " << M3.getSum() << endl;

    return 0;
}
