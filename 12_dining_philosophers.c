/*
 * Q12: Dining Philosophers Problem
 *      Uses mutexes (pthreads) to simulate 5 philosophers.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define THINKING 0
#define HUNGRY   1
#define EATING   2
#define LEFT  ((i + N - 1) % N)
#define RIGHT ((i + 1) % N)

int state[N];
pthread_mutex_t mutex;
pthread_cond_t  cond[N];

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        printf("  Philosopher %d is EATING\n", i + 1);
        pthread_cond_signal(&cond[i]);
    }
}

void pick_up(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", i + 1);
    test(i);
    while (state[i] != EATING)
        pthread_cond_wait(&cond[i], &mutex);
    pthread_mutex_unlock(&mutex);
}

void put_down(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    printf("  Philosopher %d put down forks, now THINKING\n", i + 1);
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *arg) {
    int i = *(int *)arg;
    for (int round = 0; round < 3; round++) {
        printf("Philosopher %d is THINKING\n", i + 1);
        usleep(rand() % 500000);
        pick_up(i);
        usleep(rand() % 500000);
        put_down(i);
    }
    return NULL;
}

int main() {
    pthread_t tid[N];
    int id[N];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; i++) {
        pthread_cond_init(&cond[i], NULL);
        state[i] = THINKING;
    }

    printf("=== Dining Philosophers Problem ===\n\n");

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &id[i]);
    }
    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < N; i++)
        pthread_cond_destroy(&cond[i]);

    printf("\nAll philosophers finished.\n");
    return 0;
}
