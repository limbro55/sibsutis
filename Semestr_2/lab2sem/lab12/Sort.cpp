#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Sort.h"
using namespace std;

void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i+1;
    }
}

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand();
    }
}

void SelectSort(int A[], int n) {
    int k = 0;
    for (int i = 0; i < n - 1; i++) {
        k = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[k]) {
                k = j;
            }
        }
        if (k != i) { 
            swap(A[i], A[k]);
        }
    } 
}


void BubbleSort(int A[], int n){
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                swap(A[j], A[j + 1]);
            }
        }
    }
}


void ShakerSort(int A[], int n){
    int L = 0, R = n-1, K = n-1;
    while(L < R) {
        for(int j = R; j > L; j--){
            if(A[j] < A[j-1]){
                swap(A[j], A[j-1]);
                K = j;
            }
        }
        L = K;
        for(int j = L; j < R; j++){
            if(A[j] > A[j+1]){
                swap(A[j], A[j+1]);
                K = j;
            }
        }
        R = K;
    }
}


void InsertSort(int A[], int n){
    int temp, j;
    for(int i = 1; i < n; i++){
        temp = A[i]; j = i - 1;
        while(j >= 0 && temp < A[j]){
            A[j+1] = A[j];
            j = j - 1;
        }
        A[j+1] = temp;
    }
}


void ShellSort(int A[], int n){
    for(int h = n/2; h > 0; h /= 2){
        for(int i = h; i < n; i++){
            int temp = A[i];
            int j = i;
            while(j >= h && A[j - h] > temp){
                A[j] = A[j - h];
                j -= h;
            }
            A[j] = temp;
        }
    }
}


void Merge(int a[], int q, int b[], int r, int c[], int &C, int &M){
    int i = 0, j = 0, k = 0;
    while (i < q && j < r){
        C++;
        if (a[i] <= b[j]){
            M++;
            c[k++] = a[i++];
        } else {
            M++;
            c[k++] = b[j++];
        }
    }
    while (i < q){
        M++;
        c[k++] = a[i++];
    }
    while (j < r){
        M++;
        c[k++] = b[j++];
    }
}

void MergeSort(int A[], int n){
    if (n <= 1) {
        return;
    }
    int mid = n / 2;
    int a[mid], b[n - mid];

    for (int i = 0; i < mid; i++){
        a[i] = A[i];
    }

    for (int i = mid; i < n; i++){
        b[i - mid] = A[i];
    }

    MergeSort(a, mid);
    MergeSort(b, n - mid);

    int C = 0, M = 0;
    int c[n];
    Merge(a, mid, b, n - mid, c, C, M);

    for (int i = 0; i < n; i++){
        A[i] = c[i];
    }
}

void QuickSort(int A[], int R, int L){
    while(L < R){
        int i = L;
        int j = R;
        int c = A[(L + R) / 2];
        while (i <= j){
            while (A[i] < c) {
                i++;
            }
            while (A[j] > c){
                j--;
            }
            if (i <= j){
                swap(A[i], A[j]);
                i++;
                j--;
            }
        }

        if (j - L < R - i){
            QuickSort(A, j, L);
            L = i;;
        } else {
            QuickSort(A, R, i);
            R = j;
        }
    }
}

void HeapSort_build(int A[], int L, int R){
    int x = A[L];
    int i = L;
    while(1){
        int j = 2 * i;
        if (j > R){
            break;
        }
        if ((j < R) && (A[j+1] <= A[j])){
            j = j + 1;
        }
        if (x <= A[j]){
            break;
        }
        A[i] = A[j];
        i = j;
    }
    A[i] = x;

}

void HeapSort(int A[], int n){
    int L,R;
    L = floor((n-1)/2);
    while(L >= 0){
        HeapSort_build(A,L,n-1);
        L--;
    }
    R = n - 1;
    while(R > 0){
        swap(A[0], A[R]);
        R--;
        HeapSort_build(A,0,R);
    }

}