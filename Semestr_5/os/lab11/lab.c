#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0; // сколько элементов в буфере

pthread_mutex_t mutex;
sem_t empty; // свободные места
sem_t full;  // занятые места

void* producer(void* arg) {
    int item = 0;
    while (1) {
        item++;

        sem_wait(&empty);             // ждём свободное место
        pthread_mutex_lock(&mutex);   // в критическую секцию

        buffer[count++] = item;
        printf("[PROD] put %d (count=%d)\n", item, count);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);              // сигнал "элемент добавлен"

        usleep(200000);
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);              // ждём, пока что-то есть
        pthread_mutex_lock(&mutex);

        int item = buffer[--count];
        printf("      [CONS] got %d (count=%d)\n", item, count);

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
