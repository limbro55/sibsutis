#include <iostream>
#include <ctime>
#include <math.h>
#include <iomanip>
#include <cmath>
#include <algorithm>

const int n = 50;

int collisions = 0;
int T[43];//массив для хэш табл
int countArr[43];


int partition(int arr[], int start, int end){
    int pivot = arr[start];
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    int pivotIndex = start + count;
    std::swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;

    while(i < pivotIndex && j > pivotIndex){
        while(arr[i] <= pivot){
            i++;
        }
        while(arr[j] > pivot){
            j--;
        }
        if(i < pivotIndex && j > pivotIndex){
            std::swap(arr[i++], arr[j--]);
        }
    }
    return pivotIndex;
}

void QuickSort(int arr[], int start, int end){
    if (start >= end){
        return;
    }
    int p = partition(arr, start, end);
    QuickSort(arr, start, p - 1);
    QuickSort(arr, p + 1, end);
}

//функция для разделения массива
int HashF(int num, int m){
    return num % m;
}

//линейное пробирование
int linearProbeInsert(int key, int m) {
    int index = HashF(key, m);//первый хэш индекс
    for (int q = 0; q < m; q++){
        index = (index + 1) % m;//вычисление нового индекса
        if(T[index] == 0){
            break;
        }
        if (q == (m - 1)){
            return -1;
        }
    }
    if(T[index] == 0){
        T[index] = key;
    }
    return 0;
}

//квадратичное пробирование
int QuadraticProbeInsert(int key, int m){
    int index = HashF(key, m);
    int i = 1;
    for (int q = 0; q < m; q++){
        index = (HashF(key, m) + i * i) % m;
        i++;
        if(T[index] == 0){
            break;
        }
        if(q == m - 1){
            return -1;
        }
    }
    if (T[index] == 0){
        T[index] = key;
    }
    return 0;
}

//заполнение с линейным
void HashTableLin(int m, int a[n]){
    for(int q = 0; q < n; q++){
        if(T[HashF(a[q], m)] == 0 || T[HashF(a[q], m)] == a[q]){
            T[HashF(a[q], m)] = a[q];
        }else{
            int res = linearProbeInsert(a[q], m);
            collisions++;
            if (res == -1){
                return;
            }
        }
    }
}

//заполнение с квадаратичным
void HashTableQua(int m, int a[n]){
    for (int q = 0; q < n; q++){
        if(T[HashF(a[q], m)] == 0 || T[HashF(a[q], m)] == a[q]){
            T[HashF(a[q], m)] = a[q];
        }else{
            int res = QuadraticProbeInsert(a[q], m);
            if (res == -1){
                return;
            }
            collisions++;
        }
    }
}

//инициалихация
void HashNull(){
    for(int q = 0; q < 43; q++){
        T[q] = 0;
        countArr[q] = 0;
    }
}

    int main(){
        srand(time(NULL));
        int a[n];
        int m[10] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
        HashNull();
        for(int q = 0; q < n; q++){
            a[q] = (rand() % 90) + 10;
        }

        //вывод таблицы для линейного пробирования
        std::cout << "Таблица: номер ячейки и символ для линейных проб" << std::endl;

        collisions = 0;
        HashTableLin(21, a);
        
        for (int w = 0; w < 21; w++)
            std::cout << std::setw(2) << w << "  ";
        std::cout << std::endl;
        for (int w = 0; w < 21; w++)
            std::cout << std::setw(3) << T[w] << " ";
        std::cout << std::endl << "Кол-во коллизий: " << collisions << std::endl;
        
        //вывод таблицы для квадратичного пробирования
        std::cout << std::endl << "Таблица: номер ячейки и символ для квадратичных проб" << std::endl;
        collisions = 0;
        HashNull();
        HashTableQua(21, a);
        for (int w = 0; w < 21; w++)
            std::cout << std::setw(2) << w << "  ";
        std::cout << std::endl;
        for (int w = 0; w < 21; w++)
            std::cout << std::setw(3) << T[w] << " ";
        std::cout << std::endl << "Кол-во коллизий: " << collisions << std::endl;
        
        collisions = 0;
        HashNull();
        
        //Сравнение методов пробирования для различных размеров таблиц
        std::cout << std::endl << std::setw(15) << "Размер" << std::setw(29) << "Количество" << std::setw(33) << "Коллизии" << std::endl;
        
        std::cout << std::setw(20) << "хеш-таблицы" << std::setw(36) << "исходных символов" << std::setw(25) << "линейный пр" << std::setw(33) << "квадратичные пр" << std::endl;
        
        for(int q = 0; q < 10; q++){
            std::cout << std::setw(7) << m[q] << std::setw(17) << n;
            collisions = 0;
            HashTableLin(m[q], a);
            std::cout << std::setw(17) << collisions;
            collisions = 0;

            HashNull();
            HashTableQua(m[q], a);
            std::cout << std::setw(17) << collisions << std::endl;;
            collisions = 0;
            HashNull();
        }

        return 0;
    }