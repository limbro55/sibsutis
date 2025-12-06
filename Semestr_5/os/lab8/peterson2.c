#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

volatile _Atomic int flag[2];
volatile _Atomic int turn;
volatile _Atomic int counter = 0;

void lock(int self) {
    int other = 1 - self;
    flag[self] = 1;
    turn = other;
    while (flag[other] && turn == other) {
        // busy wait
    }
}

void unlock(int self) {
    flag[self] = 0;
}

void* thread_func(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 1000000; i++) {
        lock(id);
        counter++;     // критическая секция
        unlock(id);
    }

    return NULL;
}

int main() {
    pthread_t t0, t1;

    flag[0] = flag[1] = 0;
    turn = 0;

    int id0 = 0, id1 = 1;

    pthread_create(&t0, NULL, thread_func, &id0);
    pthread_create(&t1, NULL, thread_func, &id1);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("counter = %d\n", counter);
    return 0;
}
