#include "struct.h" 
#include <iostream>
#include <cstdlib>
#include <ctime> 

void zapolnenie_mas(int mas[], int n){
    srand(time(NULL));
    int check[n];
    for(int h = 0; h < n; h++){
        check[h] = -1;
    }
    for(int i = 0; i < n; i++){
        int temp = rand() % (n * 10);
        bool check_element = true;
        for(int j = 0; j < n; j++){
            if(check[j] == temp){
                check_element = false;
            }
        }
        if (check_element == true){
            mas[i] = temp;
            check[i] = temp;
        }else{
            i--;
        }
    }
}

void obhod_leftward_to_the_right(Vertex *vertex){ //слева направо
    if(vertex != NULL){
        obhod_leftward_to_the_right(vertex->Left);
        std::cout << vertex->Key << ' ';
        obhod_leftward_to_the_right(vertex->Right);
    }
}

int razmer(Vertex *vertex){
    if(vertex == NULL){
        return 0;
    }else{
        return (1 + razmer(vertex->Left) + razmer(vertex->Right));
    }
}

int control_summa(Vertex *vertex){
    if(vertex == NULL){
        return 0;
    }else{
        return vertex->Key + control_summa(vertex->Left) + control_summa(vertex->Right);
    }
}

int height(Vertex *vertex){
    if(vertex == NULL){
        return 0;
    }else{
        return (1 + std::max(height(vertex->Left), height(vertex->Right)));
    }
}

int average_height(Vertex *vertex, int L){
    if(vertex == NULL){
        return 0;
    }else{
        return (L + average_height(vertex->Left, L+1) + average_height(vertex->Right, L+1));
    }
}

void printSquareMatrix (int **arr, int size){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      cout << "\t";
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
}
