/*
 * Q10: IPC using Message Queue
 *      Sender sends a message; Receiver reads it.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

#define MSG_KEY  1234
#define MSG_TYPE 1
#define MSG_SIZE 128

struct msgbuf {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    int msgid;
    struct msgbuf msg;
    pid_t pid;

    msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msgid < 0) { perror("msgget"); exit(EXIT_FAILURE); }

    pid = fork();
    if (pid < 0) { perror("fork"); exit(EXIT_FAILURE); }

    if (pid == 0) {
        /* ---- CHILD = RECEIVER ---- */
        if (msgrcv(msgid, &msg, MSG_SIZE, MSG_TYPE, 0) < 0) {
            perror("msgrcv"); exit(EXIT_FAILURE);
        }
        printf("[RECEIVER] Got: \"%s\"\n", msg.mtext);
        exit(EXIT_SUCCESS);
    } else {
        /* ---- PARENT = SENDER ---- */
        msg.mtype = MSG_TYPE;
        strncpy(msg.mtext, "Hello from Sender via Message Queue!", MSG_SIZE - 1);

        if (msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0) < 0) {
            perror("msgsnd"); exit(EXIT_FAILURE);
        }
        printf("[SENDER] Sent: \"%s\"\n", msg.mtext);

        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
        printf("Message queue removed.\n");
    }

    return 0;
}
