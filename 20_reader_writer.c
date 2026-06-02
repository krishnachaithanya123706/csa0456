/*
 * Q20: Reader-Writer Problem using Semaphores
 *      Multiple readers can read simultaneously;
 *      Writer gets exclusive access.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 4
#define NUM_WRITERS 2

int shared_data = 0;
int reader_count = 0;

sem_t   wrt;        /* Writer's semaphore – mutual exclusion */
pthread_mutex_t mutex; /* Protects reader_count */

void *reader(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&mutex);
        reader_count++;
        if (reader_count == 1) sem_wait(&wrt); /* First reader blocks writer */
        pthread_mutex_unlock(&mutex);

        printf("[Reader %d] Reading shared_data = %d\n", id, shared_data);
        usleep(100000);

        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0) sem_post(&wrt); /* Last reader unblocks writer */
        pthread_mutex_unlock(&mutex);

        usleep(200000);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 3; i++) {
        sem_wait(&wrt);
        shared_data += 10;
        printf("[Writer %d] Wrote shared_data = %d\n", id, shared_data);
        sem_post(&wrt);
        usleep(300000);
    }
    return NULL;
}

int main() {
    pthread_t rtid[NUM_READERS], wtid[NUM_WRITERS];
    int rid[NUM_READERS], wid[NUM_WRITERS];

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    printf("=== Reader-Writer Problem (Semaphores) ===\n\n");

    for (int i = 0; i < NUM_WRITERS; i++) {
        wid[i] = i + 1;
        pthread_create(&wtid[i], NULL, writer, &wid[i]);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        rid[i] = i + 1;
        pthread_create(&rtid[i], NULL, reader, &rid[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++) pthread_join(wtid[i], NULL);
    for (int i = 0; i < NUM_READERS; i++) pthread_join(rtid[i], NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);
    printf("\nDone.\n");
    return 0;
}
