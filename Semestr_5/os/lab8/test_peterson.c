#include "common.h"
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <sys/sysinfo.h>

#define COUNTER_TEST_ITERATIONS 1000000

// Shared counter for testing
atomic_int shared_counter = 0;
peterson_lock_2_t peterson_lock;

// Test function for Peterson algorithm
void* increment_counter_peterson(void* arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < COUNTER_TEST_ITERATIONS; i++) {
        peterson_lock_2_acquire(&peterson_lock, thread_id);
        shared_counter++;
        peterson_lock_2_release(&peterson_lock, thread_id);
    }
    
    return NULL;
}

// Test with different memory order models
void test_peterson_memory_order(int memory_order_model) {
    printf("\n=== Testing Peterson with Memory Order Model %d ===\n", memory_order_model);
    
    pthread_t threads[2];
    int thread_ids[2] = {0, 1};
    
    atomic_store(&shared_counter, 0);
    peterson_lock_2_init(&peterson_lock);
    
    double start = get_time();
    
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, increment_counter_peterson, &thread_ids[i]);
    }
    
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    
    double end = get_time();
    
    printf("Expected: %d, Got: %d\n", 
           2 * COUNTER_TEST_ITERATIONS, 
           atomic_load(&shared_counter));
    printf("Time: %.6f seconds\n", end - start);
    printf("Result: %s\n\n", 
           atomic_load(&shared_counter) == 2 * COUNTER_TEST_ITERATIONS ? "PASS" : "FAIL");
}

// Test on different CPU cores
void test_on_cores(const char* cores, const char* description) {
    printf("\n=== Testing on %s ===\n", description);
    
    // Create CPU set
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    
    if (strcmp(cores, "0") == 0) {
        CPU_SET(0, &cpuset);
    } else if (strcmp(cores, "0,1") == 0) {
        CPU_SET(0, &cpuset);
        CPU_SET(1, &cpuset);
    } else {
        int num_cores = get_nprocs();
        for (int i = 0; i < num_cores; i++) {
            CPU_SET(i, &cpuset);
        }
    }
    
    pthread_t threads[2];
    int thread_ids[2] = {0, 1};
    
    atomic_store(&shared_counter, 0);
    peterson_lock_2_init(&peterson_lock);
    
    double start = get_time();
    
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, increment_counter_peterson, &thread_ids[i]);
        
        // Set thread affinity
        pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &cpuset);
    }
    
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    
    double end = get_time();
    
    printf("Cores: %s\n", cores);
    printf("Expected: %d, Got: %d\n", 
           2 * COUNTER_TEST_ITERATIONS, 
           atomic_load(&shared_counter));
    printf("Time: %.6f seconds\n", end - start);
    printf("Result: %s\n", 
           atomic_load(&shared_counter) == 2 * COUNTER_TEST_ITERATIONS ? "PASS" : "FAIL");
}

int main() {
    printf("========= PETERSON ALGORITHM TESTING =========\n");
    
    // Test on different core configurations
    test_on_cores("0", "Single Core");
    test_on_cores("0,1", "Two Cores");
    
    cpu_set_t all_cores;
    CPU_ZERO(&all_cores);
    char all_cores_str[256] = "";
    int num_cores = get_nprocs();
    for (int i = 0; i < num_cores; i++) {
        CPU_SET(i, &all_cores);
        char temp[10];
        sprintf(temp, "%s%d", i > 0 ? "," : "", i);
        strcat(all_cores_str, temp);
    }
    test_on_cores(all_cores_str, "All Cores");
    
    printf("\n========= TEST COMPLETED =========\n");
    
    return 0;
}