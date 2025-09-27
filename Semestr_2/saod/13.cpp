#include <iostream>
#include <ctime>
#include <math.h>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

int kolvo = 0;

struct tLE {
    tLE *next;
    int data;
};

struct Queue{
    tLE *head;
    tLE *tail;
};


void StackMassInc(int n, tLE*(&head)){
    int i = n;
    tLE* p;
    p = NULL;
    do{
        head = new tLE;
        head->next = p;
        p = head;
        head->data = i;
        i--;
    }while(i > 0);
}


void StackMassDec(int n, tLE*(&head)){
    int i = 1;
    tLE* p;
    p = NULL;
    do{
        head = new tLE;
        head->next = p;
        p = head;
        head->data = i;
        i++;
    }while (i <= n);
}


void StackMassRand(int n, tLE*(&head)){
    srand(time(NULL));
    int i = 1;
    tLE* p;
    p = NULL;
    do{
        head = new tLE;
        head->next = p;
        p = head;
        head->data = rand() % (n * 2);
        i++;
    }while (i <= n);
}


void PrintList(tLE *p){
    while (p != NULL){
        cout << p->data << " ";
        p = p -> next;
    }
    cout << endl;
}


void SummaList(tLE *p){
    int summa = 0;
    while (p != NULL){
        summa += p->data;
        p = p -> next;
    }
    cout << "Summa = " << summa << endl;
}



void RunNumberList(tLE *p, int n){
    int r = 1, temp;
    for(int i = 0; i < n - 1; i++){
        temp = p->data;
        p = p->next;
        if(temp > p->data){
            r++;
        }
    }
    cout << "Series = " << r << endl;
}

void merge(tLE **a, int q, tLE **b, int r, Queue *c, int &C, int &M){
        while (q != 0 && r != 0){
        C++;
        if ((*a)->data <= (*b)->data){
            M++;
            c->tail->next = *a;
            c->tail = *a;
            *a = (*a)->next;
            q--;
        }else{
            M++;
            c->tail->next = *b;
            c->tail = *b;
            *b = (*b)->next;
            r--;
        }
    }
    while (q > 0){
        M++;
        c->tail->next = *a;
        c->tail = *a;
        *a = (*a)->next;
        q--;
    }
    while (r > 0){
        M++;
        c->tail->next = *b;
        c->tail = *b;
        *b = (*b)->next;
        r--;
    }
}


int Split(tLE *S, tLE **a, tLE **b, int &M){
    tLE *k, *p;
    *a = S;
    *b = S->next;
    int n = 1;
    k = *a;
    p = *b;
    while (p != NULL){
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
    M+=n;
    return n;
}

int MergeSort(tLE *(&S), tLE *(&tail)){
    int C = 0, M = 0;
    tLE *a;
    tLE *b;
    int n = Split(S, &a, &b, M);
    int p = 1; // предполагаемый размер серии
    int q, r;  // фактический размер серий a и b
    Queue c[2];
    while (p < n){
        c[0].tail = (tLE *)&(c[0].head);
        c[1].tail = (tLE *)&(c[1].head);

        int i = 0;
        int m = n; // текущее кол-во элементов в a и b
        while (m > 0){
            if(m >= p){
                q = p;
            }
            else{
                q = m;
            }
            m = m - q;

            if(m >= p){
                r = p;
            }else{
                r = m;
            }
            m = m - r;
            merge(&a, q, &b, r, &c[i], C, M);
            i = 1 - i;
        }
        a = c[0].head;
        b = c[1].head;
        p = 2 * p;
    }
    c[0].tail->next = NULL;
    S = c[0].head;
    tail = c[0].tail;
    return M + C;
}

void NumbersEl(tLE *p){
    kolvo = 0;
    while(p != NULL){
        p = p -> next;
        kolvo += 1;
    }
    cout << "Number of elements - " << kolvo << endl;
}


int main(){
    int n;
    tLE *head = NULL, *tail = NULL;
    int inc, dec, rand, teor;
    
    //первое задание
    n = 21;
    tLE *a=NULL, *b=NULL;
    Queue c[2];
    c[0].tail = (tLE *)&(c[0].head);
    c[1].tail = (tLE *)&(c[1].head);
    int i = 0;
    int C = 0, M = 0;
    int kolvo_a = 0, kolvo_b = 0;
    StackMassRand(n, head);
    cout << "First spisok: " << endl;
    PrintList(head);
    NumbersEl(head);
    Split(head, &a, &b, n);
    cout << endl << "list a: ";
    PrintList(a);
    kolvo = 0;
    NumbersEl(a);
    kolvo_a = kolvo;
    cout << endl << "list b: ";
    PrintList(b);
    kolvo = 0;
    NumbersEl(b);
    kolvo_b = kolvo;
    cout << endl;
    printf("The combined list: ");
    merge(&a, kolvo_a, &b, kolvo_b, &c[i], C, M);
    PrintList(head);
    cout << endl;
    printf("Combined sorted list: \n");
    n = MergeSort(head, tail);
    PrintList(head);
    RunNumberList(head, (kolvo_a + kolvo_b));
    
    
    
    
    //второе задание
    cout << endl << " " << setw(22) << "MergeSort" << endl;
    cout << " n" << setw(8) << "teor" << setw(9) << "inc" << setw(10) << "dec" << setw(10) << "rand" << endl;
    
    //100
    n = 100;
    StackMassInc(n, head);
    inc = MergeSort(head, tail);
    StackMassDec(n, head);
    dec = MergeSort(head, tail);
    StackMassRand(n, head);
    rand = MergeSort(head, tail);
    teor = n*ceil(log2(n))+ n*ceil(log2(n))+n;
    cout << n << setw(6) << teor << setw(10) << inc << setw(10) << dec << setw(9) << rand << endl;
    
    
    //200
    n = 200;
    StackMassInc(n, head);
    inc = MergeSort(head, tail);
    StackMassDec(n, head);
    dec = MergeSort(head, tail);
    StackMassRand(n, head);
    rand = MergeSort(head, tail);
    teor = n*ceil(log2(n))+ n*ceil(log2(n))+n;
    cout << n << setw(6) << teor << setw(10) << inc << setw(10) << dec << setw(9) << rand << endl;
    
    
    //300
    n = 300;
    StackMassInc(n, head);
    inc = MergeSort(head, tail);
    StackMassDec(n, head);
    dec = MergeSort(head, tail);
    StackMassRand(n, head);
    rand = MergeSort(head, tail);
    teor = n*ceil(log2(n))+ n*ceil(log2(n))+n;
    cout << n << setw(6) << teor << setw(10) << inc << setw(10) << dec << setw(9) << rand << endl;
    
    
    
    //400
    n = 400;
    StackMassInc(n, head);
    inc = MergeSort(head, tail);
    StackMassDec(n, head);
    dec = MergeSort(head, tail);
    StackMassRand(n, head);
    rand = MergeSort(head, tail);
    teor = n*ceil(log2(n))+ n*ceil(log2(n))+n;
    cout << n << setw(6) << teor << setw(10) << inc << setw(10) << dec << setw(9) << rand << endl;
    
    
    
    //500
    n = 500;
    StackMassInc(n, head);
    inc = MergeSort(head, tail);
    StackMassDec(n, head);
    dec = MergeSort(head, tail);
    StackMassRand(n, head);
    rand = MergeSort(head, tail);
    teor = n*ceil(log2(n))+ n*ceil(log2(n))+n;
    cout << n << setw(6) << teor << setw(10) << inc << setw(10) << dec << setw(9) << rand << endl;
    return 0;
}
