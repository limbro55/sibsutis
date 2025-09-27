#include <ctime>
#include "Sort.h"

double timer(void (*tip_sort)(int[], int), int A[], int n) {
    clock_t start, end;
    start = clock();

    tip_sort(A, n); 

    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}


int main(){
    int n = 32000;
    int A[n];
    double time_taken;

    FillRand(A, n);
    time_taken = timer(BubbleSort, A, n);
    cout << "Время выполнения BubbleSort: " << time_taken << " seconds" << endl;

    FillRand(A, n);
    time_taken = timer(ShakerSort, A, n);
    cout << "Время выполнения ShakerSort: " << time_taken << " seconds" << endl;

    FillRand(A, n);
    time_taken = timer(SelectSort, A, n);
    cout << "Время выполнения SelectSort: " << time_taken << " seconds" << endl;

    FillRand(A, n);
    time_taken = timer(InsertSort, A, n);
    cout << "Время выполнения InsertSort: " << time_taken << " seconds" << endl;

    FillRand(A, n);
    time_taken = timer(ShellSort, A, n);
    cout << "Время выполнения ShellSort: " << time_taken << " seconds" << endl;

    FillRand(A, n);
    time_taken = timer(MergeSort, A, n);
    cout << "Время выполнения MergeSort: " << time_taken << " seconds" << endl;
    
    FillRand(A, n);
    time_taken = timer(HeapSort, A, n);
    cout << "Время выполнения HeapSort: " << time_taken << " seconds" << endl;

}