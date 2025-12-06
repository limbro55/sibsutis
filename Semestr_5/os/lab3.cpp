#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Дочерний процесс
        printf("Дочерний процесс: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(100); 
        printf("Дочерний процесс завершен\n");
    } else if (pid > 0) {
        // Родительский процесс
        printf("Родительский процесс: PID = %d, Child PID = %d\n", getpid(), pid);
        sleep(100);
        printf("Родительский процесс завершен\n");
    } else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}