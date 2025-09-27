#include <iostream>
#include <ctime>
#include <queue>
using namespace std;


struct tree {
    int index;
    int balance = 0;
    int data;
    tree *L = NULL;
    tree *R = NULL;
};

// слева направо (симметричный обход)
void LefttoRight(tree *p, bool root) {
    if (root)
        cout << endl << "Слева направо : " << endl;
    if (p != NULL) {
        LefttoRight(p->L, 0);
        cout << "(" << p->index << ":" << p->data << ") ";
        LefttoRight(p->R, 0);
    }
}

// Работа с индексами
void pinning_index(tree* root) {
    if (root == NULL) {
        return;
    }
    
    int currentID = 1;
    queue<tree*> q;
    q.push(root);
    
    while (!q.empty()) {
        int level_size = q.size();

        for (int i = 0; i < level_size; i++) {
            tree* current = q.front();
            q.pop();

            current->index = currentID++; 

            if (current->L != NULL) {
                q.push(current->L);
            }
            if (current->R != NULL) {
                q.push(current->R);
            }
        }
    }
}

void FillRand(int A[], int n) {
    srand(time(NULL));
    
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 50;
    }
}

// LL поворот
void LL(tree *&p) {
    tree *q = p->L;
    p->balance = 0;
    q->balance = 0;
    p->L = q->R;
    q->R = p;
    p = q;
}

// RR поворот
void RR(tree *&p) {
    tree *q = p->R;
    p->balance = 0;
    q->balance = 0;
    p->R = q->L;
    q->L = p;
    p = q;
}

// LR поворот
void LR(tree *&p) {
    tree *q = p->L;
    tree *r = q->R;
    if (r->balance < 0)
        p->balance = 1;
    else
        p->balance = 0;

    if (r->balance > 0)
        q->balance = -1;
    else
        q->balance = 0;

    r->balance = 0;
    q->R = r->L;
    p->L = r->R;
    r->L = q;
    r->R = p;
    p = r;
}

// RL поворот
void RL(tree *&p) {
    tree *q = p->R;
    tree *r = q->L;
    if (r->balance > 0)
        p->balance = -1;
    else
        p->balance = 0;

    if (r->balance < 0)
        q->balance = 1;
    else
        q->balance = 0;

    r->balance = 0;
    q->L = r->R;
    p->R = r->L;
    r->R = q;
    r->L = p;
    p = r;
}

// Добавление в АВЛ дерево
bool addAVL(tree *&p, int data, bool &rost) {
    if (p == NULL) {
        p = new tree;
        p->data = data;
        rost = true;
    } else if (p->data > data) {
        if (addAVL(p->L, data, rost)) {
            if (rost) {
                if (p->balance > 0) {
                    p->balance = 0;
                    rost = false;
                } else if (p->balance == 0) {
                    p->balance = -1;
                    rost = true;
                } else if ((p->L)->balance < 0) {
                    LL(p);
                    rost = false;
                } else {
                    LR(p);
                    rost = false;
                }
            }
        } else {
            return false;
        }
    }
    else if (p->data < data) {
        if (addAVL(p->R, data, rost)) {
            if (rost) {
                if (p->balance < 0) {
                    p->balance = 0;
                    rost = false;
                } else if (p->balance == 0) {
                    p->balance = 1;
                    rost = true;
                } else if ((p->R)->balance > 0) {
                    RR(p);
                    rost = false;
                } else {
                    RL(p);
                    rost = false;
                }
            }
        } else {
            return false;
        }
    } else {
        return false; // Дубликаты не вставляются
    }
    return true;
}

// Создание АВЛ дерева
tree *createAVL(int n, bool log, int*A) {
    tree *root = NULL;
    int i = 0;
    bool rost;
    while (i < n) {
        int data = A[i];

        if (addAVL(root, data, rost))
            i++;
        else if (log)
            cout << " /* Данные с ключом \"" << data << "\" уже есть в дереве */" << endl;
    }
    return root;
}


// LL1 поворот при удалении
void LL1(tree*& p, bool& ymen) {
    tree* q = p->L;
    if (q->balance == 0) {
        q->balance = 1;
        p->balance = -1;
        ymen = false;
    }
    else {
        q->balance = 0;
        p->balance = 0;
    }
    p->L = q->R;
    q->R = p;
    p = q;
}

// RR1 поворот при удалении
void RR1(tree*& p, bool& ymen) {
    tree* q = p->R;
    if (q->balance == 0) {
        q->balance = -1;
        p->balance = 1;
        ymen = false;
    }
    else {
        q->balance = 0;
        p->balance = 0;
    }
    p->R = q->L;
    q->L = p;
    p = q;
}

// Балансировка после удаления в левом поддереве
void BR(tree*& p, bool& ymen) {
    if (p->balance == 1) {
        p->balance = 0;
    }
    else if (p->balance == 0) {
        p->balance = -1;
        ymen = false;
    }
    else if (p->balance == -1) {
        if (p->L->balance <= 0) {
            // LL1 ПОВОРОТ
            LL1(p, ymen);
        }
        else {
            // LR ПОВОРОТ
            LR(p);
        }
    }
}

// Балансировка после удаления в правом поддереве
void BL(tree*& p, bool& ymen) {
    if (p->balance == -1) {
        p->balance = 0;
    }
    else if (p->balance == 0) {
        p->balance = 1;
        ymen = false;
    }
    else if (p->balance == 1) {
        if (p->R->balance >= 0) {
            RR1(p, ymen);
        }
        else {
            RL(p);
        }
    }
}

// Удаляет вершину, имеющую два поддерева
void del(tree*& r, tree *&q, bool& ymen) {
    if (r->R != NULL) {
        del(r->R, q, ymen);
        if (ymen) {
            BR(r, ymen);
        }
    }
    else {
        q->data = r->data;
        q = r;
        r = r->L;
        ymen = true;
    }
}

// Удаление узла из АВЛ дерева
bool DELETE(tree*& p, int x, bool &ymen) {
    tree *q = NULL;
    if (p == NULL)
        return 1;
    else if (p->data > x) {
        if (DELETE(p->L, x, ymen))
            return 1;
        if (ymen)
            BL(p, ymen);
    }
    else if (p->data < x) {
        if (DELETE(p->R, x, ymen))
            return 1;
        if (ymen)
            BR(p, ymen);
    }
    else {
        q = p;
        if (q->R == NULL) {
            p = q->L;
            ymen = true;
        } else if (q->L == NULL) {
            p = q->R;
            ymen = true;
        } else {
            del(q->L, q, ymen);
            if (ymen)
                BL(p, ymen);
        }
    }
    delete (q);
    return 0;
}
//-----------------------------------------------------------------------------------------

int main() {
    int x;
    srand(time(NULL));
    int n = 10;
    int* Arr = new int[n];
    FillRand(Arr, n);
    int* Arr1 = new int[n];
    FillRand(Arr1, n);
    tree* root1 = createAVL(n, 0, Arr1);
    pinning_index(root1);
    cout << "АВЛ: ";
    LefttoRight(root1, 1);
    cout << endl;
    bool ymen;
    for (int i = 0; i < 10; i++) {
        cout << "Выберите что удалить: ";
        cin >> x;
        ymen = false;
        if (DELETE(root1, x, ymen)) {
            cout << "Узел " << x << " не найден." << endl;
        }
        else {
            cout << "Узел " << x << " удален." << endl;
            cout << "АВЛ: ";
            pinning_index(root1);
            LefttoRight(root1, 1);
            cout << endl;
        }
    }

    // Освобождение памяти
    delete[] Arr;
    delete[] Arr1;

    return 0;
}
