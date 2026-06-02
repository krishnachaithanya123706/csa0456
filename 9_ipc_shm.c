/*
 * Q9: IPC using Shared Memory
 *     Writer writes a message; Reader reads it.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_SIZE 1024
#define SHM_KEY  9999

int main() {
    int shmid;
    char *shm_ptr;
    pid_t pid;
    const char *message = "Hello from Writer via Shared Memory!";

    /* Create shared memory segment */
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) { perror("shmget"); exit(EXIT_FAILURE); }

    pid = fork();
    if (pid < 0) { perror("fork"); exit(EXIT_FAILURE); }

    if (pid == 0) {
        /* ---- CHILD = READER ---- */
        sleep(1); /* wait for parent to write */
        shm_ptr = shmat(shmid, NULL, 0);
        if (shm_ptr == (char *)-1) { perror("shmat"); exit(EXIT_FAILURE); }

        printf("[READER] Message received: \"%s\"\n", shm_ptr);
        shmdt(shm_ptr);
        exit(EXIT_SUCCESS);
    } else {
        /* ---- PARENT = WRITER ---- */
        shm_ptr = shmat(shmid, NULL, 0);
        if (shm_ptr == (char *)-1) { perror("shmat"); exit(EXIT_FAILURE); }

        strncpy(shm_ptr, message, SHM_SIZE - 1);
        printf("[WRITER] Message written : \"%s\"\n", shm_ptr);
        shmdt(shm_ptr);

        wait(NULL);
        /* Remove shared memory */
        shmctl(shmid, IPC_RMID, NULL);
        printf("Shared memory removed.\n");
    }

    return 0;
}
