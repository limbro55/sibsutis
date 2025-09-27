#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <locale>
using namespace std;

int CountNumbers = 50;
int Size_Table = ceil(CountNumbers / (2 * log2(CountNumbers))); ;//размер хэш табл
 

//для представление узла связанного списка
struct Stack
{
    Stack* next;
    int data;
};

//для бакета
struct Hash_Table
{
    Stack* data;
};
//вычисляет хэш-значение
int HashFunc(int elem, int Size_Table)
{
    return elem % Size_Table;
}

void printHash(Hash_Table* head,int elem, int Size_Table)
{
    cout << "\nМетод прямого связывания\n" << endl;
    for (int i = 0; i < Size_Table; i++)
    {
        cout << i << " ";
        Stack* p = head[i].data;
        while (p != NULL)
        {
            
                cout << " -> " << p->data;
                p = p->next;
            
        }
        cout << "\t" << endl;
    }
    cout << endl;
}

//функция добавляет значение в хэш-таблицу
void Add(Hash_Table* head, int elem, int& collision, int Size_Table)
{
    int hash = HashFunc(elem, Size_Table); 
    Stack* newNode = new Stack; //новый узел для хранения эл
    newNode->data = elem;  
    newNode->next = NULL;
    Stack* p = head[hash].data;
    while (p != nullptr)
    {
        if (p->data == elem)
        {
            return;
        }
        p = p->next;
       
    }
    if (head[hash].data == NULL) 
    {
        head[hash].data = newNode;
    }
    else 
    {
        Stack* p = head[hash].data; 
        while (p->next != NULL)

        {
            p = p->next;
        }
         p->next = newNode;//новый узел в конце списка
         collision++;
        
    }
}

int Search(Hash_Table* head, int elem, int Size_Table)
{
    int hash = HashFunc(elem, Size_Table);
    int i = 1;
    Stack* p = head[hash].data;

    while (p != NULL)
    {
        if (p->data == elem)
        {
            cout << "Элемент " << elem << " найден в позиции "<<i<< " найден в позиции " <<hash << endl;
            return 1;
        }
        i++;
        p = p->next;
    }
    cout << "Элемент " << elem << " не найден" << endl;
    return 0;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int collision = 0;
    int elem;
    Hash_Table* head = new Hash_Table[Size_Table];
    int primes[] = { 11, 17, 29, 43, 59, 61, 71, 73, 97, 101 };
    int numPrimes = sizeof(primes) / sizeof(int);
    for (int i = 0; i < Size_Table; i++)
    {
        head[i].data = NULL;
    }

    cout << "Сгенерированные числа\n" << endl;
    for (int i = 0; i < CountNumbers; i++)
    {
        elem = rand() % 101 + 11;
        int hash = HashFunc(elem, Size_Table);
        cout << elem << ": hash-adres-> " << hash << endl;
        Add(head, elem, collision, Size_Table);
    }

    printHash(head,elem, Size_Table);
    cout << "Размер Таблицы: " << Size_Table << "\n" << endl;
    cout << "Кол-во коллизий: " << collision << "\n" << endl;


    //тестирование хэш-таблиц различных размеров
    collision = 0;
    int CountSimvl = rand() % (101 - 50) + 50;
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Размер хеш-таблицы  |   Количество символов |   Количество коллизий |" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    for (int i = 0; i < numPrimes; i++)
    {
        int size = primes[i];
        int collision = 0;
        Hash_Table* head = new Hash_Table[size];

        for (int j = 0; j < size; j++)
        {
            head[j].data = NULL;
        }

        for (int j = 0; j < CountSimvl; j++)
        {
            int elem = rand() % 101 + 11;
            Add(head, elem, collision, size);
        }
        cout << "\t" << size << "\t    |\t\t" << CountSimvl << "\t    |\t\t" << collision << "\t    |\t\t" << endl;
    
    }


    cout << endl;
    cout << "Введите элемент поиска: ";
    cin >> elem;
    Search(head, elem, Size_Table);
  
    return 0;
}