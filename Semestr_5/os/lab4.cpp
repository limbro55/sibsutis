#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("Родительский процесс запущен. PID = %d\n", getpid());

  for (int i = 0; i < 2; ++i) {
    pid_t pid = fork();

    if (pid == 0) {
      printf("%d. pid дочернего процесса = %d, pid родительского = %d\n", i,
             getpid(), getppid());

      switch (i) {
        case 0:
          execlp("ls", "ls", NULL);
          break;
        case 1:
          execlp("date", "date", NULL);
          break;
      }
    }
  }

  for (int i = 0; i < 2; ++i) {
    wait(NULL);
  }

  printf("Родительский процесс завершен.\n");
  return 0;
}
