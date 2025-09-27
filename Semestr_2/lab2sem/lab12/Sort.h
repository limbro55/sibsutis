#pragma once 

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

void PrintMas(int A[], int n);

void FillInc(int A[], int n);

void FillRand(int A[], int n);

void SelectSort(int A[], int n);

void BubbleSort(int A[], int n);

void ShakerSort(int A[], int n);

void InsertSort(int A[], int n);

void ShellSort(int A[], int n);

void MergeSort(int A[], int n);

void QuickSort(int A[], int R, int L = 0);

void HeapSort_build(int A[], int L, int R);

void HeapSort(int A[], int n );