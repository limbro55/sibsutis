#include "struct.h"
#include "DOP-tree.h"
#include "tree-function.h"

int main() {
    int x;
    srand(time(NULL));
    const int n = 6;
    const int n1 = 6;
    int **VandW = new int*[2];
    
    
    for (int i = 0; i < 2; i++){
        VandW[i] = new int[n + 1];
        VandW[i][0] = 0;
    }
    
    
    bool table[n] = {false};
    for (int i = 1; i < n + 1; i++){
        while (table[x = rand() % n]);
        table[x] = true;
        VandW[0][i] = x;
    }
    
    // Сортировка вершин
    for (int i = 1; i < n + 1; i++) {
        for (int j = n - 1 + 1; j > i; j--) {
            if (VandW[0][j] < VandW[0][j - 1]) {
                swap(&VandW[0][j], &VandW[0][j - 1]);
            }
        }
    }
    
    for (int i = 1; i < n + 1; i++){
        VandW[1][i] = rand() % n + 1;
    }
    
    cout << "n=6" << endl;
    int **AW1 = new int*[n1 + 1]; // матрица весов
    int **AP1 = new int*[n1 + 1]; // матрица взвешенных высот
    int **AR1 = new int*[n1 + 1]; // матрица индексов
  
    for (int i = 0; i < n1 + 1; i++){
        AW1[i] = new int[n1 + 1];
        AP1[i] = new int[n1 + 1];
        AR1[i] = new int[n1 + 1];
        for (int j = 0; j < n1 + 1; j++)
            AW1[i][j] = AP1[i][j] = AR1[i][j] = 0;
    }
    calculation_AW(AW1, VandW, n1 + 1);
    calculation_APandAR(AP1, AR1, AW1, n1 + 1);
    if (n1 < 26){
        cout << "Матрица AW:" << endl;
        printSquareMatrix(AW1, n1 + 1);
        cout << "Матрица AP:" << endl;
        printSquareMatrix(AP1, n1 + 1);
        cout << "Матрица AR:" << endl;
        printSquareMatrix(AR1, n1 + 1);
    }
    cout << endl;
    // Вывод начальных данных и весов
    short int tmp = 0;
    cout << "n=6" << endl;
    for (int i = 1; i < n + 1; i++){ 
        cout.width(4);
        cout << VandW[0][i];
        cout << "[";
        cout.width(2);
        cout << VandW[1][i]; 
        cout << "]" <<"  ";
        tmp++;
        if(tmp == 10){
        cout << endl;
        tmp = 0;
        }
    }
    
    cout << endl;

    int **AW = new int*[n + 1]; // матрица весов
    int **AP = new int*[n + 1]; // матрица взвешенных высот
    int **AR = new int*[n + 1]; // матрица индексов
  
    for (int i = 0; i < n + 1; i++){
        AW[i] = new int[n + 1];
        AP[i] = new int[n + 1];
        AR[i] = new int[n + 1];
        for (int j = 0; j < n + 1; j++)
            AW[i][j] = AP[i][j] = AR[i][j] = 0;
    }
    calculation_AW(AW, VandW, n + 1);
    calculation_APandAR(AP, AR, AW, n + 1);
    
    Vertex* DOP = NULL;
    createTreeDOP(DOP, 0, n, AR, VandW);
    cout << "ДОП (точный алгоритм)" << endl;
    cout << "Обход слева направо:" << endl;
    obhod_leftward_to_the_right(DOP);
    cout << endl << "Размер: " << razmer(DOP)<< endl;
    cout << "Контр. сумма: " << control_summa(DOP)<< endl;
    cout << "Средневзвеш.высота: " << weightedAverageHeightTree(DOP) << endl;
    cout << "AP[0,n] / AW[0,n] = " << (double)AP[0][n] / AW[0][n] << endl;
    cout << endl << endl;
    cout << "n=6       Размер      Контр. сумма    Высота      Средневзвеш.высота" << endl;
    for (int q = 100; q < 101; q += 100){
        cout << "ДОП";
        cout << "\t    "<<razmer(DOP);
        cout << "\t         "<<control_summa(DOP);
        cout << "\t         "<<height(DOP);
        cout << "\t       "<<weightedAverageHeightTree(DOP);
        cout << endl;
    }


    // Применение A1
    Vertex* A1Tree = NULL;
    A1(A1Tree, VandW, n + 1);
    cout << "Дерево A1" << endl;
    cout << "Обход слева направо:" << endl;
    obhod_leftward_to_the_right(A1Tree);
    cout << endl << "Размер: " << razmer(A1Tree) << endl;
    cout << "Контр. сумма: " << control_summa(A1Tree) << endl;
    cout << "Средневзвеш.высота: " << weightedAverageHeightTree(A1Tree) << endl;

    Vertex* A2Tree = NULL;
    A2(A2Tree, VandW, 1, n);  // Индексы L = 1, R = n для начального вызова
    cout << "Дерево A2" << endl;
    obhod_leftward_to_the_right(A2Tree);
    cout << endl << "Размер: " << razmer(A2Tree) << endl;
    cout << "Контр. сумма: " << control_summa(A2Tree) << endl;
    cout << "Средневзвеш.высота: " << weightedAverageHeightTree(A2Tree) << endl;


    return 0;
}
