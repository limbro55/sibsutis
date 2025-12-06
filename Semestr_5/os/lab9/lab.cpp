#define _GNU_SOURCE
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t stop;

void handle_signal(int sig) { stop = 1; }

char sh[6];
void* Thread(void* pParams);

pthread_spinlock_t lock;

int main(void) {
  signal(SIGINT, handle_signal);
  signal(SIGTERM, handle_signal);

  pthread_t thread_id;
  pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
  pthread_create(&thread_id, NULL, &Thread, NULL);
  while (!stop) {
    pthread_spin_lock(&lock);
    printf("%s\n", sh);
    pthread_spin_unlock(&lock);
    usleep(100000);
  }
  pthread_cancel(thread_id);
  pthread_join(thread_id, NULL);
  pthread_spin_destroy(&lock);
}

void* Thread(void* pParams) {
  int counter = 0;
  while (!stop) {
    pthread_spin_lock(&lock);
    if (counter % 2 == 0) {
      sh[0] = 'H';
      sh[1] = 'e';
      sh[2] = 'l';
      sh[3] = 'l';
      sh[4] = 'o';
      sh[5] = '\0';
    } else {
      sh[0] = 'B';
      sh[1] = 'y';
      sh[2] = 'e';
      sh[3] = '_';
      sh[4] = 'u';
      sh[5] = '\0';
    }
    counter++;
    pthread_spin_unlock(&lock);
  }
  printf("Поток корректно завершился...\n");
  return NULL;
}
