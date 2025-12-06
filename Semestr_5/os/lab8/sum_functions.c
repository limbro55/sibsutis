#include "common.h"
#include <pthread.h>


//последовательное тестирование
long long sequential_sum(const int* array, size_t size) {
long long sum = 0;
for (size_t i = 0; i < size; i++) {
sum += array[i];
}
return sum;
}


typedef struct {
const int* array;
size_t start;
size_t end;
long long partial_sum;
} thread_data_t;


// Функция для потока Pthreads
void* partial_sum_thread(void* arg) {
thread_data_t* data = (thread_data_t*)arg;
data->partial_sum = 0;
for (size_t i = data->start; i < data->end; i++) {
data->partial_sum += data->array[i];
}
return NULL;
}


// Pthreads
long long parallel_sum_pthreads(const int* array, size_t size, int num_threads) {
pthread_t threads[num_threads];
thread_data_t thread_data[num_threads];
size_t chunk_size = size / num_threads;


for (int i = 0; i < num_threads; i++) {
thread_data[i].array = array;
thread_data[i].start = i * chunk_size;
thread_data[i].end = (i == num_threads - 1) ? size : (i + 1) * chunk_size;
pthread_create(&threads[i], NULL, partial_sum_thread, &thread_data[i]);
}


long long total_sum = 0;
for (int i = 0; i < num_threads; i++) {
pthread_join(threads[i], NULL);
total_sum += thread_data[i].partial_sum;
}
return total_sum;
}


double get_time() {
struct timespec ts;
clock_gettime(CLOCK_MONOTONIC, &ts);
return ts.tv_sec + ts.tv_nsec / 1e9;
}