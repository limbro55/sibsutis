#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid1, pid2;
    
    printf("Родительский процесс: PID = %d\n", getpid());
    
    pid1 = fork();
    
    if (pid1 == 0) {
        // Первый дочерний процесс
        printf("Первый дочерний: PID = %d, PPID = %d\n", getpid(), getppid());
        
        pid2 = fork();
        if (pid2 == 0) {
            // Внучатый процесс
            printf("Внучатый процесс: PID = %d, PPID = %d\n", getpid(), getppid());
            sleep(100);
        } else {
            sleep(100);
        }
    } else {
        // Родительский процесс
        sleep(100);
    }
    
    return 0;
}