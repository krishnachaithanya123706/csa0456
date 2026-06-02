/*
 * Q13: Memory Allocation Strategies
 *      Demonstrates First Fit, Best Fit, and Worst Fit in one program.
 */
#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS   10
#define MAX_PROCESSES 10

void first_fit(int blocks[], int nb, int procs[], int np) {
    int alloc[MAX_PROCESSES];
    int bsize[MAX_BLOCKS];
    memcpy(bsize, blocks, nb * sizeof(int));
    for (int i = 0; i < np; i++) alloc[i] = -1;

    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nb; j++) {
            if (bsize[j] >= procs[i]) {
                alloc[i] = j + 1;
                bsize[j] -= procs[i];
                break;
            }
        }
    }
    printf("\n--- First Fit ---\n");
    printf("%-10s %-10s %-10s\n", "Process", "Size", "Block");
    for (int i = 0; i < np; i++) {
        if (alloc[i] != -1)
            printf("P%-9d %-10d Block %d\n", i+1, procs[i], alloc[i]);
        else
            printf("P%-9d %-10d Not Allocated\n", i+1, procs[i]);
    }
}

void best_fit(int blocks[], int nb, int procs[], int np) {
    int alloc[MAX_PROCESSES];
    int bsize[MAX_BLOCKS];
    memcpy(bsize, blocks, nb * sizeof(int));
    for (int i = 0; i < np; i++) alloc[i] = -1;

    for (int i = 0; i < np; i++) {
        int best = -1;
        for (int j = 0; j < nb; j++) {
            if (bsize[j] >= procs[i]) {
                if (best == -1 || bsize[j] < bsize[best])
                    best = j;
            }
        }
        if (best != -1) { alloc[i] = best + 1; bsize[best] -= procs[i]; }
    }
    printf("\n--- Best Fit ---\n");
    printf("%-10s %-10s %-10s\n", "Process", "Size", "Block");
    for (int i = 0; i < np; i++) {
        if (alloc[i] != -1)
            printf("P%-9d %-10d Block %d\n", i+1, procs[i], alloc[i]);
        else
            printf("P%-9d %-10d Not Allocated\n", i+1, procs[i]);
    }
}

void worst_fit(int blocks[], int nb, int procs[], int np) {
    int alloc[MAX_PROCESSES];
    int bsize[MAX_BLOCKS];
    memcpy(bsize, blocks, nb * sizeof(int));
    for (int i = 0; i < np; i++) alloc[i] = -1;

    for (int i = 0; i < np; i++) {
        int worst = -1;
        for (int j = 0; j < nb; j++) {
            if (bsize[j] >= procs[i]) {
                if (worst == -1 || bsize[j] > bsize[worst])
                    worst = j;
            }
        }
        if (worst != -1) { alloc[i] = worst + 1; bsize[worst] -= procs[i]; }
    }
    printf("\n--- Worst Fit ---\n");
    printf("%-10s %-10s %-10s\n", "Process", "Size", "Block");
    for (int i = 0; i < np; i++) {
        if (alloc[i] != -1)
            printf("P%-9d %-10d Block %d\n", i+1, procs[i], alloc[i]);
        else
            printf("P%-9d %-10d Not Allocated\n", i+1, procs[i]);
    }
}

int main() {
    int nb, np, i;
    int blocks[MAX_BLOCKS], procs[MAX_PROCESSES];

    printf("=== Memory Allocation Strategies ===\n");
    printf("Enter number of memory blocks  : "); scanf("%d", &nb);
    for (i = 0; i < nb; i++) { printf("  Block %d size: ", i+1); scanf("%d", &blocks[i]); }
    printf("Enter number of processes      : "); scanf("%d", &np);
    for (i = 0; i < np; i++) { printf("  Process %d size: ", i+1); scanf("%d", &procs[i]); }

    first_fit(blocks, nb, procs, np);
    best_fit (blocks, nb, procs, np);
    worst_fit(blocks, nb, procs, np);

    return 0;
}
