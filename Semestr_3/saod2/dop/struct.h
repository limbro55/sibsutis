#ifndef STRUCT
#define STRUCT

#include <iostream>
#include <ctime>
#include <algorithm>
#include <queue>

using namespace std;

struct Vertex {
    int Key;
    int weight;
    int index;
    Vertex *Left = NULL;
    Vertex *Right = NULL;
};

#endif 