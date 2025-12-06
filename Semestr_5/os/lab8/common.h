#ifndef COMMON_H
#define COMMON_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>


#define ARRAY_SIZE 100000000
#define NUM_THREADS 4


double get_time(void);


long long sequential_sum(const int* array, size_t size);
long long parallel_sum_pthreads(const int* array, size_t size, int num_threads);


#endif