#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("=== Process Identifier Demo ===\n");
    printf("Before fork:\n");
    printf("  Current PID  : %d\n", getpid());
    printf("  Parent PID   : %d\n", getppid());

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        printf("\n[CHILD PROCESS]\n");
        printf("  My PID       : %d\n", getpid());
        printf("  My Parent PID: %d\n", getppid());
        printf("  Child exiting...\n");
        exit(EXIT_SUCCESS);
    } else {
        /* Parent process */
        printf("\n[PARENT PROCESS]\n");
        printf("  My PID         : %d\n", getpid());
        printf("  My Parent PID  : %d\n", getppid());
        printf("  Child PID (fork): %d\n", pid);
        wait(NULL);   /* wait for child to finish */
        printf("  Child finished. Parent done.\n");
    }

    return 0;
}
