#include "struct.h"

void swap(int* a, int* b);

void calculation_AW(int **AW, int **VW, int size);

void calculation_APandAR(int **AP, int **AR, int **AW, int size);

int sumLengthWaysTreeDOP(Vertex* root, int k);

int weightTree(Vertex* root);

float weightedAverageHeightTree(Vertex *p);

void addRST_R(Vertex *&p, int data, int weight);

void createTreeDOP(Vertex*& root, int lBorder, int rBorder, int **AR, int **VW);

void sortVerticesByWeight(int **VW, int size);

void A1(Vertex *&root, int **VW, int size); // Алгоритм A1

void A2(Vertex *&root, int **VW, int L, int R);  // Алгоритм A2