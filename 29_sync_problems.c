/*
 * Q29: Classical Process Synchronization Problems
 *      Demonstrates:
 *        (a) Bounded Buffer (Producer-Consumer)
 *        (b) Reader-Writer
 *        (c) Dining Philosophers
 *      in a single menu-driven program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/* --------- (a) Bounded Buffer ---------- */
#define BUF_SIZE 5
#define ITEMS    5
int buffer[BUF_SIZE], in_bb = 0, out_bb = 0;
sem_t empty_bb, full_bb;
pthread_mutex_t mtx_bb;

void *prod_bb(void *a) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&empty_bb); pthread_mutex_lock(&mtx_bb);
        buffer[in_bb] = i * 10; printf("[Producer] item=%d slot=%d\n", i*10, in_bb);
        in_bb = (in_bb + 1) % BUF_SIZE;
        pthread_mutex_unlock(&mtx_bb); sem_post(&full_bb); usleep(100000);
    }
    return NULL;
}
void *cons_bb(void *a) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&full_bb); pthread_mutex_lock(&mtx_bb);
        int val = buffer[out_bb]; printf("[Consumer] item=%d slot=%d\n", val, out_bb);
        out_bb = (out_bb + 1) % BUF_SIZE;
        pthread_mutex_unlock(&mtx_bb); sem_post(&empty_bb); usleep(150000);
    }
    return NULL;
}
void run_bounded_buffer() {
    pthread_t p, c;
    sem_init(&empty_bb, 0, BUF_SIZE); sem_init(&full_bb, 0, 0);
    pthread_mutex_init(&mtx_bb, NULL);
    printf("\n=== (a) Bounded Buffer ===\n");
    pthread_create(&p, NULL, prod_bb, NULL); pthread_create(&c, NULL, cons_bb, NULL);
    pthread_join(p, NULL); pthread_join(c, NULL);
    sem_destroy(&empty_bb); sem_destroy(&full_bb); pthread_mutex_destroy(&mtx_bb);
}

/* --------- (b) Reader-Writer ---------- */
int shared_rw = 0, rc = 0;
sem_t wrt_rw; pthread_mutex_t mtx_rw;
void *rdr(void *a) {
    int id = *(int *)a;
    pthread_mutex_lock(&mtx_rw); rc++;
    if (rc == 1) sem_wait(&wrt_rw);
    pthread_mutex_unlock(&mtx_rw);
    printf("[Reader %d] reads %d\n", id, shared_rw); usleep(100000);
    pthread_mutex_lock(&mtx_rw); rc--;
    if (rc == 0) sem_post(&wrt_rw);
    pthread_mutex_unlock(&mtx_rw);
    return NULL;
}
void *wtr(void *a) {
    int id = *(int *)a;
    sem_wait(&wrt_rw);
    shared_rw += 100; printf("[Writer %d] wrote %d\n", id, shared_rw);
    sem_post(&wrt_rw);
    return NULL;
}
void run_reader_writer() {
    pthread_t r[3], w[2]; int rid[3] = {1,2,3}, wid[2] = {1,2};
    sem_init(&wrt_rw, 0, 1); pthread_mutex_init(&mtx_rw, NULL);
    printf("\n=== (b) Reader-Writer ===\n");
    for (int i=0;i<2;i++) pthread_create(&w[i], NULL, wtr, &wid[i]);
    for (int i=0;i<3;i++) pthread_create(&r[i], NULL, rdr, &rid[i]);
    for (int i=0;i<2;i++) pthread_join(w[i], NULL);
    for (int i=0;i<3;i++) pthread_join(r[i], NULL);
    sem_destroy(&wrt_rw); pthread_mutex_destroy(&mtx_rw);
}

/* --------- (c) Dining Philosophers ---------- */
#define PHILO 5
int phil_state[PHILO];
pthread_mutex_t pmtx; pthread_cond_t pcond[PHILO];
#define PLEFT  ((pi+PHILO-1)%PHILO)
#define PRIGHT ((pi+1)%PHILO)
void ptest(int pi) {
    if (phil_state[pi]==1 && phil_state[PLEFT]!=2 && phil_state[PRIGHT]!=2)
        { phil_state[pi]=2; pthread_cond_signal(&pcond[pi]); }
}
void pickup(int pi) { pthread_mutex_lock(&pmtx); phil_state[pi]=1; ptest(pi);
    while(phil_state[pi]!=2) pthread_cond_wait(&pcond[pi],&pmtx); pthread_mutex_unlock(&pmtx); }
void putdown(int pi) { pthread_mutex_lock(&pmtx); phil_state[pi]=0; ptest(PLEFT); ptest(PRIGHT); pthread_mutex_unlock(&pmtx); }
void *philosopher(void *a) {
    int pi=*(int *)a;
    printf("[Philosopher %d] thinking\n", pi+1); usleep(100000);
    pickup(pi); printf("[Philosopher %d] eating\n", pi+1); usleep(100000);
    putdown(pi); printf("[Philosopher %d] done\n", pi+1);
    return NULL;
}
void run_dining() {
    pthread_t tid[PHILO]; int ids[PHILO];
    pthread_mutex_init(&pmtx, NULL);
    for(int i=0;i<PHILO;i++){pthread_cond_init(&pcond[i],NULL);phil_state[i]=0;}
    printf("\n=== (c) Dining Philosophers ===\n");
    for(int i=0;i<PHILO;i++){ids[i]=i;pthread_create(&tid[i],NULL,philosopher,&ids[i]);}
    for(int i=0;i<PHILO;i++) pthread_join(tid[i],NULL);
    pthread_mutex_destroy(&pmtx);
    for(int i=0;i<PHILO;i++) pthread_cond_destroy(&pcond[i]);
}

int main() {
    int ch;
    printf("=== Classical Synchronization Problems ===\n");
    printf("1.Bounded Buffer  2.Reader-Writer  3.Dining Philosophers  4.All  5.Exit\n");
    printf("Choice: "); scanf("%d", &ch);
    switch(ch) {
        case 1: run_bounded_buffer(); break;
        case 2: run_reader_writer(); break;
        case 3: run_dining(); break;
        case 4: run_bounded_buffer(); run_reader_writer(); run_dining(); break;
        default: printf("Bye.\n");
    }
    return 0;
}
