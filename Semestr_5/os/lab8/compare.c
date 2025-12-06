#include "common.h"

typedef struct {
    double seq_time;
    double pthreads_time;
    double speedup;
} comparison_result_t;

comparison_result_t compare_approaches(int* array, size_t size, int num_threads) {
    comparison_result_t result;
    
    // Тестируем последовательную версию
    double start = get_time();
    long long seq_sum = sequential_sum(array, size);
    double end = get_time();
    result.seq_time = end - start;
    
    // Тестируем pthreads версию
    start = get_time();
    long long pthreads_sum = parallel_sum_pthreads(array, size, num_threads);
    end = get_time();
    result.pthreads_time = end - start;
    
    if (seq_sum != pthreads_sum) {
        printf("ERROR %lld vs %lld\n", seq_sum, pthreads_sum);
    }
    
    result.speedup = result.seq_time / result.pthreads_time;
    return result;
}

int main() {
    int* array = malloc(ARRAY_SIZE * sizeof(int));
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100;
    }
    
    printf("Comparing approaches with array size: %d\n", ARRAY_SIZE);
    printf("Number of threads: %d\n\n", NUM_THREADS);
    
    comparison_result_t result = compare_approaches(array, ARRAY_SIZE, NUM_THREADS);
    
    printf("RESULTS\n");
    printf("Sequential:  %.6f seconds\n", result.seq_time);
    printf("Pthreads:    %.6f seconds\n", result.pthreads_time);
    printf("Speedup:          %.2fx\n", result.speedup);
    printf("Efficiency:       %.1f%%\n", (result.speedup / NUM_THREADS) * 100);
    
    free(array);
    return 0;
}