/*
 * Q19: Process Synchronization using Mutex Locks
 *      Two threads increment a shared counter safely.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ITERATIONS 100000

long shared_counter = 0;
pthread_mutex_t mutex;

void *increment(void *arg) {
    const char *name = (const char *)arg;
    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        shared_counter++;
        pthread_mutex_unlock(&mutex);
    }
    printf("[%s] Done incrementing.\n", name);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);

    printf("=== Mutex Synchronization Demo ===\n");
    printf("Two threads each increment shared counter %d times.\n\n", ITERATIONS);

    pthread_create(&t1, NULL, increment, "Thread-1");
    pthread_create(&t2, NULL, increment, "Thread-2");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("\nExpected counter : %d\n", 2 * ITERATIONS);
    printf("Actual counter   : %ld\n", shared_counter);
    printf("Result           : %s\n",
           shared_counter == 2 * ITERATIONS ? "CORRECT (No race condition)" : "WRONG (Race condition!)");

    return 0;
}
