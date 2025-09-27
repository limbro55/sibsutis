#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Vertex{
    int Key;
    int Balance;
    int index;
    Vertex* Left;
    Vertex* Right;
};

bool Rost;
int VR = 1, HR = 1;
Vertex* root = nullptr;
Vertex* root_ISDP = nullptr;
Vertex* root_DBD = nullptr;

void LL_Rotate(Vertex*& p) {
    Vertex* q = p->Left;
    p->Balance = 0;
    q->Balance = 0;
    p->Left = q->Right;
    q->Right = p;
    p = q;
}

void RR_Rotate(Vertex*& p) {
    Vertex* q = p->Right;
    p->Balance = 0;
    q->Balance = 0;
    p->Right = q->Left;
    q->Left = p;
    p = q;
}

void LR_Rotate(Vertex*& p) {
    Vertex* q = p->Left;
    Vertex* r = q->Right;

    if (r->Balance < 0)
        p->Balance = 1;
    else
        p->Balance = 0;

    if (r->Balance > 0)
        q->Balance = -1;
    else
        q->Balance = 0;

    r->Balance = 0;
    q->Right = r->Left;
    p->Left = r->Right;
    r->Left = q;
    r->Right = p;
    p = r;
}

void RL_Rotate(Vertex*& p) {
    Vertex* q = p->Right;
    Vertex* r = q->Left;

    if (r->Balance > 0)
        p->Balance = -1;
    else
        p->Balance = 0;

    if (r->Balance < 0)
        q->Balance = 1;
    else
        q->Balance = 0;

    r->Balance = 0;
    q->Left = r->Right;
    p->Right = r->Left;
    r->Left = p;
    r->Right = q;
    p = r;
}

void AddAVL(int key, Vertex*& p) {
    if (p == nullptr) {
        p = new Vertex;
        p->Key = key;
        p->Left = nullptr;
        p->Right = nullptr;
        p->Balance = 0;
        Rost = true;
    }
    else if (key < p->Key) {
        AddAVL(key, p->Left);
        if (Rost) {
            if (p->Balance > 0) {
                p->Balance = 0;
                Rost = false;
            }
            else if (p->Balance == 0) {
                p->Balance = -1;
                Rost = true;
            }
            else {
                if (p->Left->Balance < 0) {
                    LL_Rotate(p);
                    Rost = false;
                }
                else {
                    LR_Rotate(p);
                    Rost = false;
                }
            }
        }
    }
    else if (key > p->Key) {
        AddAVL(key, p->Right);
        if (Rost) {
            if (p->Balance < 0) {
                p->Balance = 0;
                Rost = false;
            }
            else if (p->Balance == 0) {
                p->Balance = 1;
                Rost = true;
            }
            else { 
                if (p->Right->Balance > 0) {
                    RR_Rotate(p);
                    Rost = false;
                }
                else {
                    RL_Rotate(p);
                    Rost = false;
                }
            }
        }
    }
    else {
        Rost = false;
    }
}

void B2INSERT(int D, Vertex*& p) {
    if (p == nullptr) {
        p = new Vertex;
        p->Key = D;
        p->Left = nullptr;
        p->Right = nullptr;
        p->Balance = 0;
        VR = 1;
    } else if (D < p->Key) {
        B2INSERT(D, p->Left);
        if (VR == 1) {
            if (p->Balance == 0) {
                Vertex* q = p->Left;
                p->Left = q->Right;
                q->Right = p;
                p = q;
                q->Balance = 1;
                VR = 0;
                HR = 1;
            } else {
                p->Balance = 0;
                VR = 1;
                HR = 0;
            }
        } else {
            HR = 0;
        }
    } else if (D > p->Key) {
        B2INSERT(D, p->Right);
        if (VR == 1) {
            p->Balance = 1;
            HR = 1;
            VR = 0;
        } else if (HR == 1) {
            if (p->Balance == 1) {
                Vertex* q = p->Right;
                p->Balance = 0;
                q->Balance = 0;
                p->Right = q->Left;
                q->Left = p;
                p = q;
                VR = 1;
                HR = 0;
            } else {
                HR = 0;
            }
        }
    }
}

void pinning_index(Vertex* vertex, int current_index) {
    if (vertex != nullptr) {
        vertex->index = current_index;
        pinning_index(vertex->Left, 2 * current_index);
        pinning_index(vertex->Right, 2 * current_index + 1);
    }
}

void obhod_lr(Vertex *vertex){
    if(vertex != nullptr){
        obhod_lr(vertex->Left);
        cout  << vertex->Key<< " ";
        obhod_lr(vertex->Right);
    }
}

void TreeUpDown(Vertex *vertex) { 
    if (vertex != nullptr) {
        cout << "(" << vertex->index << ": " << vertex->Key << ") ";
        TreeUpDown(vertex->Left);
        TreeUpDown(vertex->Right);
    }
}

void zapolnenie_mas(int mas[], int n){
    srand(time(nullptr));
    int check[n];
    for(int h = 0; h < n; h++){
        check[h] = -1;
    }
    for(int i = 0; i < n; i++){
        int temp = rand() % n+1;
        bool check_element = true;
        for(int j = 0; j < n; j++){
            if(check[j] == temp){
                check_element = false;
            }
        }
        if (check_element){
            mas[i] = temp;
            check[i] = temp;
        }else{
            i--;
        }
    }
}

void insert_ISDP(Vertex*& vertex, int mas[], int start, int end) {
    if (start > end) {
        return;
    }
    int mid = (start + end) / 2;

    vertex = new Vertex;
    vertex->Key = mas[mid];
    vertex->Left = nullptr;
    vertex->Right = nullptr;
    vertex->Balance = 0;
    
    insert_ISDP(vertex->Left, mas, start, mid - 1);
    insert_ISDP(vertex->Right, mas, mid + 1, end);
}

void filling_trees(int mas[], int n){
    for(int i = 0; i < n; i++){
        AddAVL(mas[i], root);
        B2INSERT(mas[i], root_DBD);
    }
    sort(mas, mas + n); 
    insert_ISDP(root_ISDP, mas, 0, n - 1);
}

int razmer(Vertex *vertex){
    if(vertex == nullptr){
        return 0;
    }else{
        return (1 + razmer(vertex->Left) + razmer(vertex->Right));
    }
}

int control_summa(Vertex *vertex){
    if(vertex == nullptr){
        return 0;
    }else{
        return vertex->Key + control_summa(vertex->Left) + control_summa(vertex->Right);
    }
}

int height(Vertex *vertex){
    if(vertex == nullptr){
        return 0;
    }else{
        return (1 + max(height(vertex->Left), height(vertex->Right)));
    }
}

double average_height(Vertex *vertex, int L){
    if(vertex == nullptr){
        return 0;
    }else{
        return (L + average_height(vertex->Left, L+1) + average_height(vertex->Right, L+1));
    }
}

int main() {
    const int n = 100;
    int mas[n];
    
    zapolnenie_mas(mas, n);
    filling_trees(mas, n);
    pinning_index(root, 1);
    
    obhod_lr(root);
    
    cout << endl << endl;
    cout << setw(5) << "n=100" 
              << setw(15) << "Размер" 
              << setw(25) << "Контр.сумма" 
              << setw(16) << "Высота" 
              << setw(27) << "Средн.высота" << endl;
    cout << setw(5) << "ИСДП" 
              << setw(8) << razmer(root_ISDP) 
              << setw(13) << control_summa(root_ISDP) 
              << setw(12) << height(root_ISDP) 
              << setw(12) << (razmer(root_ISDP) != 0 ? average_height(root_ISDP, 1) / razmer(root_ISDP) : 0) 
              << endl;
    cout << setw(5) << " АВЛ" 
              << setw(8) << razmer(root) 
              << setw(13) << control_summa(root) 
              << setw(12) << height(root) 
              << setw(12) << (razmer(root) != 0 ? average_height(root, 1) / razmer(root) : 0) 
              << endl;
    cout << setw(5) << " ДБД" 
              << setw(8) << razmer(root_DBD) 
              << setw(13) << control_summa(root_DBD) 
              << setw(12) << height(root_DBD) 
              << setw(12) << (razmer(root_DBD) != 0 ? average_height(root_DBD, 1) / razmer(root_DBD) : 0) 
              << endl;
    return 0;
}