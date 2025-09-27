#include <iostream>
#include <iomanip>
#include <cstdlib> 
#include <ctime>    
#include <string>
#include"./Matrix.h"

using namespace std;

int main()
{
    // Создание матрицы M (3x4) с типом int
    Matrix<int> M(3, 4);
    M.Print("M");
    
    // Заполнение матрицы значениями по формуле
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            M.SetM(i, j, i + j);
        }
    }
    M.Print("M");
    
    // Создание матрицы M1 как копии 
    Matrix<int> M1 = M;
    M1.Print("M1"); 
    
    // Создание матрицы M2 и присваивание ей M
    Matrix<int> M2;
    M2 = M;
    M2.Print("M2"); // Вывод матрицы M2
    
    // Создание матрицы M3 и цепочка присваиваний
    Matrix<int> M3;
    M3 = M2 = M1 = M;
    M3.Print("M3");
    
    return 0;
}
