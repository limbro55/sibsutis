#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
int head = 0;
int tail = 0;

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void* producer(void* arg) {
    int item = 0;
    while (1) {
        item++;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[tail] = item;
        tail = (tail + 1) % BUFFER_SIZE;
        count++;
        printf("[PROD] put %d (head=%d, tail=%d, count=%d)\n", 
               item, head, tail, count);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        usleep(200000);
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[head];
        head = (head + 1) % BUFFER_SIZE;
        count--;
        printf("      [CONS] got %d (head=%d, tail=%d, count=%d)\n", 
               item, head, tail, count);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        usleep(500000);
    }
}

int main() {
    pthread_t prod, cons;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}