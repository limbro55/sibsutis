#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

int M = 0, C = 0, Deep = 0;

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

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n-i;
    }
}

void FillRand(int A[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        A[i] = rand();
    }
}

void FillCopy(int mas[], int A[], int B[], int n){
    for (int i = 0; i < n; i++){
        A[i] = mas[i];
        B[i] = mas[i];
    }
}

int QuickSort_v1(int *A, int R, int L = 0){
    M++;
    int x = A[L];
    int i = L;
    int j = R;
    while (i <= j){
        C++;
        while (A[i]<x){
            i++;
            C++;
        }
        while (A[j] > x){
            j--;
            C++;
        }
        if (i <= j ){
            swap(A[i],A[j]);
            M+=3;
            i++;
            j--;
        }
    }
    if (L < j){
        QuickSort_v1(A, j, L);
        Deep++;
    }
       
    if (i < R){
        QuickSort_v1(A, R, i);
        Deep++;
    }

return 1;
}


int QuickSort_v2(int *A, int R, int L = 0) {
    while(L < R){
        int i = L;
        int j = R;
        int c = A[(L + R) / 2];
        while (i <= j){
            C++;
            while (A[i] < c) {
                i++;
                C++;
            }
            while (A[j] > c){
                j--;
                C++;
            }
            if (i <= j){
                swap(A[i], A[j]);
                M += 3;
                i++;
                j--;
            }
        }

        if (j - L < R - i){
            QuickSort_v2(A, j, L);
            L = i;;
            Deep++;
        } else {
            QuickSort_v2(A, R, i);
            R = j;
            Deep++;
        }
    }
    return 1;
}


int main(){
    
    cout << " " << setw(25) << "QuickSort version 1(Mф + Cф)" << endl;
    cout << "n" << setw(9) << "inc" << setw(10) << "dec" << setw(10) << "rand" << endl;

    //100
    int n = 100;
    int *A = new int[n];
    int *B;
    
    FillInc(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    int inc = M+C;
    
    FillDec(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    int dec = M+C;
    
    FillRand(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    int rand = M+C;
    
    cout << n << setw(8) << inc << setw(9) << dec << setw(10) << rand << endl;
    delete[] A;
    
    //200
    n = 200;
    A = new int[n];
    
    FillInc(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    inc = M+C;
    
    FillDec(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    dec = M+C;
    
    FillRand(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    rand = M+C;
    
    cout << n << setw(8) << inc << setw(9) << dec << setw(10) << rand << endl;
    delete[] A;
    
    //300
    n = 300;
    A = new int[n];
    
    FillInc(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    inc = M+C;
    
    FillDec(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    dec = M+C;
    
    FillRand(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    rand = M+C;
    
    cout << n << setw(8) << inc << setw(9) << dec << setw(10) << rand << endl;
    delete[] A;
    
    
    //400
    n = 400;
    A = new int[n];
    
    FillInc(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    inc = M+C;
    
    FillDec(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    dec = M+C;
    
    FillRand(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    rand = M+C;
    
    cout << n << setw(8) << inc << setw(9) << dec << setw(10) << rand << endl;
    delete[] A;
    
    
    //500
    n = 500;
    A = new int[n];
    
    FillInc(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    inc = M+C;
    
    FillDec(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    dec = M+C;
    
    FillRand(A, n);
    M = 0; C = 0;
    QuickSort_v1(A, n-1);
    rand = M+C;
    
    cout << n << setw(8) << inc << setw(9) << dec << setw(10) << rand << endl;
    delete[] A;
    cout << endl << endl;
    
    
    //задание 4
    int *mas;
    cout << setw(20) << "QuickSort1" << setw(20) << "QuickSort2" << endl;
    cout << setw(2) << "n" << setw(7) << "dec" << setw(7) << "rand" << setw(7) << "inc" << setw(7) << "dec" << setw(7) << "rand" << setw(7) << "inc" << endl;
    
    
    //100
    n = 100;
    A = new int[n];
    B = new int[n];
    mas = new int[n];
    
    //dec
    FillDec(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    int dec_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    int dec_v2 = Deep;
    
    //rand
    FillRand(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    int rand_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    int rand_v2 = Deep;
    
    //inc
    FillInc(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    int inc_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    int inc_v2 = Deep;
    
    delete[] A;
    delete[] B;
    delete[] mas;
    
    cout << setw(2) << n << setw(5) << dec_v1 << setw(7) << rand_v1 << setw(7) << inc_v1 << setw(7) << dec_v2 << setw(7) << rand_v2 << setw(7) << inc_v2 << endl;
    
    
    
    //200
    n = 200;
    A = new int[n];
    B = new int[n];
    mas = new int[n];
    
    //dec
    FillDec(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    dec_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    dec_v2 = Deep;
    
    //rand
    FillRand(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    rand_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    rand_v2 = Deep;
    
    //inc
    FillInc(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    inc_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    inc_v2 = Deep;
    
    delete[] A;
    delete[] B;
    delete[] mas;
    
    cout << setw(2) << n << setw(5) << dec_v1 << setw(7) << rand_v1 << setw(7) << inc_v1 << setw(7) << dec_v2 << setw(7) << rand_v2 << setw(7) << inc_v2 << endl;
    
    
    
    //300
    n = 300;
    A = new int[n];
    B = new int[n];
    mas = new int[n];
    
    //dec
    FillDec(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    dec_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    dec_v2 = Deep;
    
    //rand
    FillRand(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    rand_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    rand_v2 = Deep;
    
    //inc
    FillInc(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    inc_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    inc_v2 = Deep;
    
    delete[] A;
    delete[] B;
    delete[] mas;
    
    cout << setw(2) << n << setw(5) << dec_v1 << setw(7) << rand_v1 << setw(7) << inc_v1 << setw(7) << dec_v2 << setw(7) << rand_v2 << setw(7) << inc_v2 << endl;
    
    
    
    //400
    n = 400;
    A = new int[n];
    B = new int[n];
    mas = new int[n];
    
    //dec
    FillDec(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    dec_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    dec_v2 = Deep;
    
    //rand
    FillRand(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    rand_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    rand_v2 = Deep;
    
    //inc
    FillInc(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    inc_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    inc_v2 = Deep;
    
    delete[] A;
    delete[] B;
    delete[] mas;
    
    cout << setw(2) << n << setw(5) << dec_v1 << setw(7) << rand_v1 << setw(7) << inc_v1 << setw(7) << dec_v2 << setw(7) << rand_v2 << setw(7) << inc_v2 << endl;
    
    
    
    //500
    n = 500;
    A = new int[n];
    B = new int[n];
    mas = new int[n];
    
    //dec
    FillDec(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    dec_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    dec_v2 = Deep;
    
    //rand
    FillRand(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    rand_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    rand_v2 = Deep;
    
    //inc
    FillInc(mas, n);
    FillCopy(mas, A, B, n);
    Deep = 0;
    QuickSort_v1(A, n-1);
    inc_v1 = Deep;
    Deep = 0;
    QuickSort_v2(B, n-1);
    inc_v2 = Deep;
    
    delete[] A;
    delete[] B;
    delete[] mas;
    
    cout << setw(2) << n << setw(5) << dec_v1 << setw(7) << rand_v1 << setw(7) << inc_v1 << setw(7) << dec_v2 << setw(7) << rand_v2 << setw(7) << inc_v2 << endl;
    
    
    
    return 0;
}
