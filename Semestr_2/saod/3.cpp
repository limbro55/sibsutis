#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

void FillInc (int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i+1;
    }
}

void FillDec (int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n-i;
    }
}

void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand()%100;
    }
}

void Heapify(int A[], int n, int i, int &M, int &C) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && A[left] > A[largest]) {
        largest = left;
        C++;
    }

    if (right < n && A[right] > A[largest]) {
        largest = right;
        C++;
    }

    if (largest != i) {
        swap(A[i], A[largest]);
        M += 3;
        Heapify(A, n, largest, M, C);
    }
}

int HeapSort(int A[], int n) {
    int M = 0, C = 0;
    for (int i = n/2 - 1; i >= 0; i--) {
        Heapify(A, n, i, M, C);
    }

    for (int i = n-1; i > 0; i--) {
        swap(A[0], A[i]);
        M += 3;
        Heapify(A, i, 0, M, C);
    }

    return M + C;
}

void QuickSort(int A[], int low, int high, int &M, int &C) {
    int i = low;
    int j = high;
    int x = A[(low + high) / 2];

    while (i <= j) {
        while (A[i] < x) {
            i++;
            C++;
        }
        while (A[j] > x) {
            j--;
            C++;
        }
        if (i <= j) {
            swap(A[i], A[j]);
            M += 3;
            i++;
            j--;
        }
    }

    if (low < j) {
        QuickSort(A, low, j, M, C);
    }
    if (i < high) {
        QuickSort(A, i, high, M, C);
    }
}

int QuickSortWrapper(int A[], int n) {
    int M = 0, C = 0;
    QuickSort(A, 0, n - 1, M, C);
    return M + C;
}

int main(){
    int n = 100;
    int *A;
    srand(time(NULL));
    A = (int *)malloc(sizeof(int)*n);
    
    cout  << setw(35)  << "Heapsort&QuickSort "  << endl;

    cout<< setw(2)<< "n"<< setw(20) << "Rand"<< setw(10) << "Dec" << setw(10) << "Inc" << endl;

    
    
    FillRand(A,n);
    int Heap_rez = HeapSort(A, n);
    FillDec(A,n);
    int Heap_dec = HeapSort(A,n);
    FillInc(A,n);
    int Heap_inc= HeapSort(A,n);
    cout << n << setw(10) << "HeapS" << setw(10) << Heap_rez  << setw(10) << Heap_dec << setw(10) << Heap_inc <<  endl;

    FillRand(A,n);
    int Quick_rez = QuickSortWrapper(A, n);
    FillDec(A,n);
    int Quick_dec = QuickSortWrapper(A,n);
    FillInc(A,n);
    int Quick_inc= QuickSortWrapper(A,n);
    cout << n << setw(10) << "Quick" << setw(10) << Quick_rez  << setw(10) << Quick_dec << setw(10) << Quick_inc <<  endl;

    
    n = 200;
    FillRand(A,n);
    int Heap_rez2 = HeapSort(A, n);
    FillDec(A,n);
    int Heap_dec2 = HeapSort(A,n);
    FillInc(A,n);
    int Heap_inc2 = HeapSort(A,n);
    cout << n << setw(10) << "HeapS" << setw(10) << Heap_rez2  << setw(10) << Heap_dec2 << setw(10) << Heap_inc2 <<  endl;

    FillRand(A,n);
    int Quick_rez2 = QuickSortWrapper(A, n);
    FillDec(A,n);
    int Quick_dec2 = QuickSortWrapper(A,n);
    FillInc(A,n);
    int Quick_inc2 = QuickSortWrapper(A,n);
    cout << n << setw(10) << "Quick" << setw(10) << Quick_rez2  << setw(10) << Quick_dec2 << setw(10) << Quick_inc2 <<  endl;


    n = 300;
    FillRand(A,n);
    int Heap_rez3 = HeapSort(A, n);
    FillDec(A,n);
    int Heap_dec3 = HeapSort(A,n);
    FillInc(A,n);
    int Heap_inc3 = HeapSort(A,n);
    cout << n << setw(10) << "HeapS" << setw(10) << Heap_rez3  << setw(10) << Heap_dec3 << setw(10) << Heap_inc3 <<  endl;

    FillRand(A,n);
    int Quick_rez3 = QuickSortWrapper(A, n);
    FillDec(A,n);
    int Quick_dec3 = QuickSortWrapper(A,n);
    FillInc(A,n);
    int Quick_inc3 = QuickSortWrapper(A,n);
    cout << n << setw(10) << "Quick" << setw(10) << Quick_rez3  << setw(10) << Quick_dec3 << setw(10) << Quick_inc3 <<  endl;


    n = 400;
    FillRand(A,n);
    int Heap_rez4 = HeapSort(A, n);
    FillDec(A,n);
    int Heap_dec4 = HeapSort(A,n);
    FillInc(A,n);
    int Heap_inc4 = HeapSort(A,n);
    cout << n << setw(10) << "HeapS" << setw(10) << Heap_rez4  << setw(10) << Heap_dec4 << setw(10) << Heap_inc4 <<  endl;

    FillRand(A,n);
    int Quick_rez4 = QuickSortWrapper(A, n);
    FillDec(A,n);
    int Quick_dec4 = QuickSortWrapper(A,n);
    FillInc(A,n);
    int Quick_inc4 = QuickSortWrapper(A,n);
    cout << n << setw(10) << "Quick" << setw(10) << Quick_rez4  << setw(10) << Quick_dec4 << setw(10) << Quick_inc4 <<  endl;


    n = 500;
    FillRand(A,n);
    int Heap_rez5 = HeapSort(A, n);
    FillDec(A,n);
    int Heap_dec5 = HeapSort(A,n);
    FillInc(A,n);
    int Heap_inc5 = HeapSort(A,n);
    cout << n << setw(10) << "HeapS" << setw(10) << Heap_rez5  << setw(10) << Heap_dec5 << setw(10) << Heap_inc5 <<  endl;

    FillRand(A,n);
    int Quick_rez5 = QuickSortWrapper(A, n);
    FillDec(A,n);
    int Quick_dec5 = QuickSortWrapper(A,n);
    FillInc(A,n);
    int Quick_inc5 = QuickSortWrapper(A,n);
    cout << n << setw(10) << "Quick" << setw(10) << Quick_rez5  << setw(10) << Quick_dec5 << setw(10) << Quick_inc5 <<  endl;


}
