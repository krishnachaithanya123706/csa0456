/*
 * Q11: Multithreading Demo using POSIX pthreads
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

typedef struct {
    int thread_id;
    int value;
} ThreadArg;

void *thread_func(void *arg) {
    ThreadArg *ta = (ThreadArg *)arg;
    printf("[Thread %d] Started. Received value = %d\n", ta->thread_id, ta->value);
    sleep(1);
    int result = ta->value * ta->value;
    printf("[Thread %d] Square of %d = %d\n", ta->thread_id, ta->value, result);
    pthread_exit((void *)(long)result);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArg args[NUM_THREADS];
    void *ret_val;
    int i;

    printf("=== Multithreading Demo (%d threads) ===\n\n", NUM_THREADS);

    for (i = 0; i < NUM_THREADS; i++) {
        args[i].thread_id = i + 1;
        args[i].value = (i + 1) * 3;
        if (pthread_create(&threads[i], NULL, thread_func, &args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &ret_val);
        printf("[Main] Thread %d returned: %ld\n", i + 1, (long)ret_val);
    }

    printf("\nAll threads finished.\n");
    return 0;
}
