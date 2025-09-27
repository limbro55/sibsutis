#include <fstream>
#include <iostream>
#include <limits>
#include <locale>
#include <string>
#include <vector>


using namespase std;

// Собственная функция swap для указателей на Record
void mySwap(Record *&a, Record *&b) {
  Record *temp = a;
  a = b;
  b = temp;
}

// Функция пирамидальной сортировки указателей по году издания
void heapifyPointers(vector<Record *> &record_ptrs, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n &&
      record_ptrs[left]->getYear() > record_ptrs[largest]->getYear())
    largest = left;

  if (right < n &&
      record_ptrs[right]->getYear() > record_ptrs[largest]->getYear())
    largest = right;

  if (largest != i) {
    mySwap(record_ptrs[i], record_ptrs[largest]);
    heapifyPointers(record_ptrs, n, largest);
  }
}

void heapsortPointers(vector<Record *> &record_ptrs) {
  int n = record_ptrs.size();
  // Построение кучи (перегруппировка массива)
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapifyPointers(record_ptrs, n, i);
  }

  for (int i = n - 1; i > 0; i--) {
    mySwap(record_ptrs[0], record_ptrs[i]);
    heapifyPointers(record_ptrs, i, 0);
  }
}