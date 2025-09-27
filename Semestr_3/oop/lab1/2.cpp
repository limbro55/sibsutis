#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int** genRandMatrix(int size, int* rowSizes, int maxValue) {
    int** matrix = new int*[size];

    for (int i = 0; i < size; ++i) {
        rowSizes[i] = rand() % 10 + 1;
        matrix[i] = new int[rowSizes[i]];

        for (int j = 0; j < rowSizes[i]; ++j) {
            matrix[i][j] = rand() % maxValue;
        }
    }

    return matrix;
}

void printMatrix(int** matrix, int size, int* rowSizes) {
    for (int i = 0; i < size; ++i) {
        cout << rowSizes[i] << ": ";
        for (int j = 0; j < rowSizes[i]; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0)); 
    int size = rand() % 10 + 1; 
    int maxValue = 100; 

    int* rowSizes = new int[size];
    
    int** matrix = genRandMatrix(size, rowSizes, maxValue);
    
    printMatrix(matrix, size, rowSizes);
    
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i]; 
    }
    delete[] matrix; 
    delete[] rowSizes; 

    return 0;
}
