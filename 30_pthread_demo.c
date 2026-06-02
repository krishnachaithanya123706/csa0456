/*
 * Q30: POSIX Thread Functions Demo
 *      (i)  pthread_create()
 *      (ii) pthread_join()
 *      (iii)pthread_equal()
 *      (iv) pthread_exit()
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t saved_tid; /* we save one thread's ID to demo pthread_equal */

/* ---- (iv) pthread_exit demo ---- */
void *thread_exit_demo(void *arg) {
    int id = *(int *)arg;
    printf("[Thread %d] Running. Will call pthread_exit.\n", id);
    sleep(1);
    pthread_exit((void *)(long)(id * 100));
    /* Code below never runs */
    printf("This line should never print.\n");
    return NULL;
}

/* ---- (iii) pthread_equal demo ---- */
void *thread_equal_demo(void *arg) {
    int id = *(int *)arg;
    printf("[Thread %d] My TID matches saved? %s\n",
           id,
           pthread_equal(pthread_self(), saved_tid) ? "YES" : "NO");
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    int ids[3] = {1, 2, 3};
    void *ret;

    printf("=== POSIX Thread Functions Demo ===\n\n");

    /* (i) pthread_create */
    printf("--- (i) pthread_create ---\n");
    if (pthread_create(&t1, NULL, thread_exit_demo, &ids[0]) != 0) {
        perror("pthread_create t1"); exit(EXIT_FAILURE);
    }
    if (pthread_create(&t2, NULL, thread_exit_demo, &ids[1]) != 0) {
        perror("pthread_create t2"); exit(EXIT_FAILURE);
    }
    printf("Two threads created.\n\n");

    /* (ii) pthread_join */
    printf("--- (ii) pthread_join ---\n");
    pthread_join(t1, &ret);
    printf("[Main] Thread 1 joined, return value = %ld\n", (long)ret);
    pthread_join(t2, &ret);
    printf("[Main] Thread 2 joined, return value = %ld\n\n", (long)ret);

    /* (iii) pthread_equal */
    printf("--- (iii) pthread_equal ---\n");
    pthread_create(&t3, NULL, thread_exit_demo, &ids[2]);
    saved_tid = t3;   /* save t3 so we compare inside its function */

    pthread_t t4;
    int id4 = 4;
    pthread_create(&t4, NULL, thread_equal_demo, &id4);
    /* t4 checks if its TID equals saved_tid (t3) - should be NO */

    pthread_t t5;
    int id5 = 5;
    /* Create another thread whose ID we'll compare with itself */
    pthread_create(&t5, NULL, thread_equal_demo, &id5);

    printf("[Main] t3 == t3? %s\n", pthread_equal(t3, t3) ? "YES" : "NO");
    printf("[Main] t3 == t4? %s\n\n", pthread_equal(t3, t4) ? "YES" : "NO");

    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    printf("--- (iv) pthread_exit ---\n");
    printf("Thread functions above all called pthread_exit() internally.\n");
    printf("Main thread calls return 0 (equivalent to pthread_exit for main).\n");

    return 0;
}
