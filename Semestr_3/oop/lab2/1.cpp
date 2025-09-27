#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int getRandomNumber(int max = 100) {
    return rand() % (max + 1);
}

void fillMatrix(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = getRandomNumber();
        }
    }
}

void printMatrix(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// a) Заполнение одномерного массива по правым диагоналям
void fillByRightDiagonals(int** matrix, int* D, int N) {
    int index = 0;
    for (int sum = 0; sum <= 2 * (N - 1); ++sum) {
        for (int i = 0; i < N; ++i) {
            int j = sum - i;
            if (j >= 0 && j < N) {
                D[index++] = matrix[i][j];
            }
        }
    }
}

// b) Заполнение одномерного массива по левым диагоналям
void fillByLeftDiagonals(int** matrix, int* D, int N) {
    int index = 0;
    for (int sum = 0; sum <= 2 * (N - 1); ++sum) {
        for (int i = 0; i < N; ++i) {
            int j = sum - (N - 1 - i);
            if (j >= 0 && j < N) {
                D[index++] = matrix[i][j];
            }
        }
    }
}

// c) Заполнение одномерного массива по спирали
void fillBySpiralFromCenter(int** matrix, int* D, int N) {
    int index = 0;
    int x = N / 2, y = N / 2;
    int layer = 1;
    D[index++] = matrix[x][y];
    
    while (layer <= N / 2) {
        // вправо
        for (int i = 0; i < layer; ++i) {
            y++;
            if (x >= 0 && x < N && y >= 0 && y < N) {
                D[index++] = matrix[x][y];
            }
        }
        // вниз
        for (int i = 0; i < layer; ++i) {
            x++;
            if (x >= 0 && x < N && y >= 0 && y < N) {
                D[index++] = matrix[x][y];
            }
        }
        // влево
        for (int i = 0; i < layer + 1; ++i) {
            y--;
            if (x >= 0 && x < N && y >= 0 && y < N) {
                D[index++] = matrix[x][y];
            }
        }
        // вверх
        for (int i = 0; i < layer + 1; ++i) {
            x--;
            if (x >= 0 && x < N && y >= 0 && y < N) {
                D[index++] = matrix[x][y];
            }
        }
        layer++;
    }
}

// d) Заполнение одномерного массива по спирали
void fillBySpiralFromCorner(int** matrix, int* D, int N) {
    int index = 0;
    int layer = 0;
    
    while (layer < (N + 1) / 2) {
        // вправо
        for (int i = layer; i < N - layer; ++i) {
            D[index++] = matrix[layer][i];
        }
        // вниз
        for (int i = layer + 1; i < N - layer; ++i) {
            D[index++] = matrix[i][N - layer - 1];
        }
        // влево
        for (int i = N - layer - 2; i >= layer; --i) {
            D[index++] = matrix[N - layer - 1][i];
        }
        // вверх
        for (int i = N - layer - 2; i > layer; --i) {
            D[index++] = matrix[i][layer];
        }
        layer++;
    }
}

int main() {
    srand(time(0));
    
    int N;
    cout << "Введите размер матрицы N: ";
    cin >> N;

    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }
    
    fillMatrix(matrix, N);

    cout << "Исходная матрица:" << endl;
    printMatrix(matrix, N);

    int* D = new int[N * N];

    // a)
    fillByRightDiagonals(matrix, D, N);
    cout << "\nМассив D по правым диагоналям:" << endl;
    for (int i = 0; i < N * N; ++i) {
        cout << D[i] << " ";
    }
    cout << endl;

    // b)
    fillByLeftDiagonals(matrix, D, N);
    cout << "\nМассив D по левым диагоналям:" << endl;
    for (int i = 0; i < N * N; ++i) {
        cout << D[i] << " ";
    }
    cout << endl;

    // c)
    fillBySpiralFromCenter(matrix, D, N);
    cout << "\nМассив D по спирали (из центра):" << endl;
    for (int i = 0; i < N * N; ++i) {
        cout << D[i] << " ";
    }
    cout << endl;

    // d)
    fillBySpiralFromCorner(matrix, D, N);
    cout << "\nМассив D по спирали (с угла):" << endl;
    for (int i = 0; i < N * N; ++i) {
        cout << D[i] << " ";
    }
    cout << endl;

    // Очистка памяти
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] D;

    return 0;
}
