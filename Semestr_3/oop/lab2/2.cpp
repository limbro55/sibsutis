#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    int rows;
    cout << "Введите количество строк: ";
    cin >> rows;

    int** matrix = new int*[rows];

    for (int i = 0; i < rows; ++i) {
        int cols;
        cout << "Введите количество элементов в строке " << i + 1 << ": ";
        cin >> cols;

        matrix[i] = new int[cols]; // массив для i-й строки

        
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 100; 
        }
    }

    cout << "\nДинамический двумерный массив:\n";
    for (int i = 0; i < rows; ++i) {
        int j = 0;
        while (matrix[i][j] != '\0') {
            cout << matrix[i][j] << " ";
            ++j;
        }
        cout << endl;
    }

    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}