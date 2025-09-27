#include "struct.h"

//ДОП
void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// Вычисление матрицы весов AW
void calculation_AW(int **AW, int **VW, int size){
	for(int i = 0; i < size; i++){
		for(int j = (i + 1); j < size; j++){
			AW[i][j] = AW[i][j-1] + VW[1][j];
		}
	}
}

// Вычисление матрицы взвешенных высот (AP) и матрицы индексов (AR)
void calculation_APandAR(int **AP, int **AR, int **AW, int size){
	for(int i = 0; i < size - 1; i++){
		int j = i + 1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	for(int h = 2; h < size; h++){
		for(int i = 0; i < size - h; i++){
			int j = i + h;
			int m = AR[i][j - 1];
			int min = AP[i][m - 1] + AP[m][j];
			for(int k = m + 1; k <= AR[i + 1][j]; k++){
				int x = AP[i][k - 1] + AP[k][j];
				if(x < min){
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

//Wn*hn
int sumLengthWaysTreeDOP(Vertex* root, int k){
	int S;
	if(root == NULL){
		S = 0;
	}else{
		S=root->weight * k + sumLengthWaysTreeDOP(root->Left, k + 1) + sumLengthWaysTreeDOP(root->Right, k + 1);
	}
	return S;
}

//вес дерева W
int weightTree(Vertex* root){
	int n;
	if(root == NULL){
		n=0;
	}else{
		n = root->weight + weightTree(root->Left) + weightTree(root->Right);
	}
	return n;
}


// Средневзвешенная высота дерева
float weightedAverageHeightTree(Vertex *p) {
    if (p == NULL)
        return 0;
    else
        return (float)sumLengthWaysTreeDOP(p, 1) / weightTree(p);
}


//Добавление вершины методом двойной рекурсии
void addRST_R(Vertex *&p, int data, int weight) {
    if (p == NULL) {
        p = new Vertex;
        p -> Key = data;
        p -> weight = weight;
    } else if (data < p -> Key)
        addRST_R(p -> Left, data, weight);
    else if (data > p -> Key)
        addRST_R(p -> Right, data, weight);
}

void createTreeDOP(Vertex*& root, int lBorder, int rBorder, int **AR, int **VW){
	if(lBorder < rBorder){
		int k = AR[lBorder][rBorder];
        addRST_R(root, VW[0][k], VW[1][k]);
		createTreeDOP(root, lBorder, k - 1, AR, VW);
		createTreeDOP(root, k, rBorder, AR, VW);
	}
}

// Функция для сортировки вершин по убыванию весов
void sortVerticesByWeight(int **VW, int size) {
    for (int i = 1; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (VW[1][i] < VW[1][j]) { 
                swap(&VW[0][i], &VW[0][j]); // Перестановка ключей
                swap(&VW[1][i], &VW[1][j]); // Перестановка весов
            }
        }
    }
}

void A1(Vertex *&root, int **VW, int size) {

    sortVerticesByWeight(VW, size);
    
    // Добавляем вершины в дерево
    for (int i = 1; i < size; i++) {
        addRST_R(root, VW[0][i], VW[1][i]);
    }
}

// A2 
void A2(Vertex *&root, int **VW, int L, int R) {
    int wes = 0, sum = 0;

    // проверка на корректные границы
    if (L <= R) {
        
        for (int i = L; i <= R; i++) {
            wes += VW[1][i];
        }

        int i = L;
        
        while (i <= R && (sum + VW[1][i]) <= wes / 2) {
            sum += VW[1][i];
            i++;
        }

        addRST_R(root, VW[0][i], VW[1][i]);

        A2(root->Left, VW, L, i - 1);
        A2(root->Right, VW, i + 1, R);
    }
}