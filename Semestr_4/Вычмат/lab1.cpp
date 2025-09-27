#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    int i, j, n, m;
    string filename = "matrix.txt";

    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла!\n";
        return 1;
    }

    file >> n >> m;
    m += 1;

    int **matrix = new int *[n];
    for (i = 0; i < n; i++)
        matrix[i] = new int[m];

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            file >> matrix[i][j];

    file.close();

    cout << "matrix: " << endl;
    for (i = 0; i < n; i++)
    {
        cout << "[";
        for (j = 0; j < m; j++) {
            cout << matrix[i][j] << (j < m - 1 ? ", " : "");
        }
        cout << "]\n";
    }

    // for(i = 0; i<n; i++){
    //     for(j = i+1;j<n;j++){
    //         for(int k = j; k<n; k++){
    //              
    //              
    //         }
    //     }
    // }

    for (i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}
