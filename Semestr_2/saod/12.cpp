#include <iostream>
#include <ctime>
using namespace std;

struct tLE {
    tLE *next;
    int data;
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

void QueueMassInc(int n, tLE* &head) {
    tLE* p = head;
    for (int i = 1; i < n; i++){
        p->data = i;
        p->next = new tLE;
        p = p->next;
    }
    p->data = n;
    p->next = NULL;
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

void QueueMassDec(int n, tLE* &head) {
    tLE* p = head;
    for (int i = n; i > 1; i--){
        p->data = i;
        p->next = new tLE;
        p = p->next;
    }
    p->data = 1;
    p->next = NULL;
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

void QueueMassRand(int n, tLE* &head) {
    tLE* p = head;
    for (int i = 1; i < n; i++){
        p->next = new tLE;
        p = p->next;
    }
    p->next = NULL;
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

void DeleteList(tLE* &head) {
    tLE* current = head;
    tLE* next;
    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
}


int main(){
    int n;
    tLE *head = NULL, *tail = NULL;
    cout << "write kol-vo element: ";
    cin >> n;
    
    cout << "\nStack with up numbers: \n";
    StackMassInc(n, head);
    PrintList(head);
    SummaList(head);
    RunNumberList(head, n);

    cout << "\nStack with down numbers: \n";
    StackMassDec(n, head);
    PrintList(head);
    SummaList(head);
    RunNumberList(head, n);

    cout << "\nStack with rand numbers: \n";
    StackMassRand(n, head);
    PrintList(head);
    SummaList(head);
    RunNumberList(head, n);
    
    cout << "\nQueue with up numbers: \n";
    QueueMassInc(n, head);
    PrintList(head);
    SummaList(head);
    RunNumberList(head, n);
    
    cout << "\nQueue with down numbers: \n";
    QueueMassDec(n, head);
    PrintList(head);
    SummaList(head);
    RunNumberList(head, n);
    
    cout << "\nQueue with rand numbers: \n";
    DeleteList(head);
    QueueMassRand(n, head);
    PrintList(head);
    SummaList(head);
    RunNumberList(head, n);

    
    return 0;
}

