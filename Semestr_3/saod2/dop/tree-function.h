#include "struct.h"
#include <iostream>
#include <cstdlib>
#include <ctime> 

void zapolnenie_mas(int mas[], int n);

void obhod_leftward_to_the_right(Vertex *vertex); 

int razmer(Vertex *vertex);

int control_summa(Vertex *vertex);

int height(Vertex *vertex);

int average_height(Vertex *vertex, int L);

void printSquareMatrix (int **arr, int size);
