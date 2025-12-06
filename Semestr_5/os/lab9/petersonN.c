#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

#ifndef N
#define N 5       // количество потоков
#endif

volatile _Atomic int level[N];
volatile _Atomic int waiting[N];
volatile _Atomic int counter = 0;

void lock(int self) {
    for (int L = 0; L < N - 1; L++) {
        level[self] = L;
        waiting[L] = self;

        int someone;
        do {
            someone = 0;
            for (int k = 0; k < N; k++) {
                if (k == self) continue;
                if (level[k] >= L) {
                    someone = 1;
                    break;
                }
            }
        } while (waiting[L] == self && someone);
    }
}

void unlock(int self) {
    level[self] = -1;
}

void* thread_func(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 200000; i++) {
        lock(id);

        counter++;  // критическая секция

        unlock(id);
    }

    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        level[i] = -1;
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("counter = %d\n", counter);
    return 0;
}
