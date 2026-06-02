/*
 * Q18: Producer-Consumer Problem using Semaphores
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS       10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty_slots;   /* counts empty buffer slots  */
sem_t full_slots;    /* counts full buffer slots   */
pthread_mutex_t mutex;

void *producer(void *arg) {
    for (int i = 1; i <= ITEMS; i++) {
        int item = i * 10;
        sem_wait(&empty_slots);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("[Producer] Produced item %d at slot %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full_slots);
        usleep(200000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&full_slots);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("[Consumer] Consumed item %d from slot %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_slots);
        usleep(300000);
    }
    return NULL;
}

int main() {
    pthread_t prod_tid, cons_tid;

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots,  0, 0);
    pthread_mutex_init(&mutex, NULL);

    printf("=== Producer-Consumer (Semaphores) | Buffer=%d | Items=%d ===\n\n",
           BUFFER_SIZE, ITEMS);

    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);
    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&mutex);

    printf("\nAll items produced and consumed.\n");
    return 0;
}
