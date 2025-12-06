#include "common.h"
#include <pthread.h>
#include <string.h>

// Peterson lock for N threads (filter lock)
void peterson_lock_init(peterson_lock_t *lock, int num_threads) {
    lock->num_threads = num_threads;
    lock->flag = (atomic_bool*)malloc(num_threads * sizeof(atomic_bool));
    lock->turn = (atomic_int*)malloc((num_threads - 1) * sizeof(atomic_int));
    
    for (int i = 0; i < num_threads; i++) {
        atomic_init(&lock->flag[i], false);
    }
    for (int i = 0; i < num_threads - 1; i++) {
        atomic_init(&lock->turn[i], 0);
    }
}

void peterson_lock_destroy(peterson_lock_t *lock) {
    free(lock->flag);
    free(lock->turn);
}

void peterson_lock_acquire(peterson_lock_t *lock, int thread_id) {
    for (int level = 0; level < lock->num_threads - 1; level++) {
        atomic_store_explicit(&lock->flag[thread_id], true, memory_order_relaxed);
        atomic_store_explicit(&lock->turn[level], thread_id, memory_order_relaxed);
        
        // Wait until no other thread at this level or turn is not this thread
        bool someone_else_wants = true;
        while (someone_else_wants) {
            someone_else_wants = false;
            for (int k = 0; k < lock->num_threads; k++) {
                if (k != thread_id && 
                    atomic_load_explicit(&lock->flag[k], memory_order_acquire) &&
                    atomic_load_explicit(&lock->turn[level], memory_order_acquire) == thread_id) {
                    someone_else_wants = true;
                    break;
                }
            }
        }
    }
}

void peterson_lock_release(peterson_lock_t *lock, int thread_id) {
    atomic_store_explicit(&lock->flag[thread_id], false, memory_order_release);
}

// Simplified Peterson lock for 2 threads (original algorithm)
typedef struct {
    atomic_bool flag[2];
    atomic_int turn;
} peterson_lock_2_t;

void peterson_lock_2_init(peterson_lock_2_t *lock) {
    atomic_init(&lock->flag[0], false);
    atomic_init(&lock->flag[1], false);
    atomic_init(&lock->turn, 0);
}

void peterson_lock_2_acquire(peterson_lock_2_t *lock, int thread_id) {
    int other = 1 - thread_id;
    
    // Different memory order models for testing
    atomic_store_explicit(&lock->flag[thread_id], true, memory_order_relaxed);
    atomic_store_explicit(&lock->turn, thread_id, memory_order_release);
    
    // Spin while other thread wants to enter and it's its turn
    while (atomic_load_explicit(&lock->flag[other], memory_order_acquire) && 
           atomic_load_explicit(&lock->turn, memory_order_acquire) == thread_id) {
        // Busy wait
    }
}

void peterson_lock_2_release(peterson_lock_2_t *lock, int thread_id) {
    atomic_store_explicit(&lock->flag[thread_id], false, memory_order_release);
}