#include <iostream>
#include <ctime>
#include <algorithm>
#include <set>

using namespace std;

struct tree {
    int data;
    tree* left;
    tree* right;
};

tree* addnode(tree *d, int key) {
    if (d == NULL) {
        d = new tree;
        d->data = key;
        d->left = NULL;
        d->right = NULL;
    }
    else if (key < d->data) {
        d->left = addnode(d->left, key);
    }
    else if (key > d->data) {
        d->right = addnode(d->right, key);
    }
    return d;
}

void LeftRight(tree* p) { 
    if (p != NULL) {
        LeftRight(p->left);
        cout << p->data << " ";
        LeftRight(p->right);
    }
}

tree* SDP1(tree* d, int key) {
    if (d == NULL) {
        d = new tree;
        d->data = key;
        d->left = NULL;
        d->right = NULL;
    }
    else if (key < d->data) {
        d->left = addnode(d->left, key);
    }
    else if (key > d->data) {
        d->right = addnode(d->right, key);
    }
    return d;
}

tree* SDP2(tree** root, int D) {
    tree** p = root;
    int check = 1;
    while ((*p != NULL) && (check == 1)) {
        if (D < (*p)->data) {
            p = &((*p)->left);
        } else if (D > (*p)->data) {
            p = &((*p)->right);
        } else {
            check = 0;
        }
    }
    if (*p == NULL) {
        *p = addnode(*p, D);
    }
    return *p;
}

void deleteX(int X, tree** root) {
    tree** p = root;
    while ((*p != NULL)) {
        if (X > (*p)->data) {
            p = &((*p)->right);
        } else if (X < (*p)->data) {
            p = &((*p)->left);
        } else {
            break;
        }
    }
    tree* q = *p;
    if (*p != NULL) {
        if (q->left == NULL) {
            *p = q->right;
        } else if (q->right == NULL) {
            *p = q->left;
        } else {
            tree* s = q;
            tree* r = q->left;
            while (r->right != NULL) {
                s = r;
                r = r->right;
            }
            if (s != q) {
                s->right = r->left;
            } else {
                s->left = r->left;
            }
            r->left = q->left;
            r->right = q->right;
            *p = r;
        }
    }
    delete q;
}

int main() {
    srand(time(NULL));
    tree* rootrec = NULL;
    tree* rootdvoi = NULL;

    int n = 5;
    int* arr = new int[n];
    set<int> uniqueValues; // Множество для хранения уникальных значений

    cout << "MassivSort: ";
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;  // Генерация массива с уникальными значениями
        uniqueValues.insert(arr[i]);
        cout << arr[i] << " ";
    }
    cout << "\n" << endl;

    cout << "MassivNeSort: ";
    // Перемешиваем массив случайным образом
    for (int i = 0; i < n; i++) {
        int randomIndex = rand() % n;
        swap(arr[i], arr[randomIndex]);
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";   
    }
    cout << "\n" << endl;

    for (int i = 0; i < n; i++) {
        SDP2(&rootdvoi, arr[i]);
        rootrec = SDP1(rootrec, arr[i]);
    }

    cout << "Tree before deletions: ";
    LeftRight(rootrec);
    cout << "\n" << endl;

    // Удаляем элементы автоматически
    for (int i = 0; i < n; i++) {
        deleteX(arr[i], &rootrec);
        cout << "Tree without element " << arr[i] << ": ";
        LeftRight(rootrec);
        cout << "\n" << endl;
    }

    delete[] arr;
    
    return 0;
}