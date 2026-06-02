/*
 * Q23: First Fit Memory Allocation Algorithm
 */
#include <stdio.h>

#define MAX 20

int main() {
    int nb, np, i;
    int blocks[MAX], procs[MAX], alloc[MAX];
    int bsize[MAX];

    printf("=== First Fit Memory Allocation ===\n");
    printf("Enter number of blocks   : "); scanf("%d", &nb);
    for (i = 0; i < nb; i++) { printf("  Block %d size: ", i+1); scanf("%d", &blocks[i]); bsize[i] = blocks[i]; }
    printf("Enter number of processes: "); scanf("%d", &np);
    for (i = 0; i < np; i++) { printf("  Process %d size: ", i+1); scanf("%d", &procs[i]); alloc[i] = -1; }

    for (i = 0; i < np; i++) {
        for (int j = 0; j < nb; j++) {
            if (bsize[j] >= procs[i]) {
                alloc[i] = j + 1;
                bsize[j] -= procs[i];
                break;
            }
        }
    }

    printf("\n%-10s %-12s %-12s %-12s\n", "Process", "Size(KB)", "Block Alloc", "Remaining");
    printf("--------------------------------------------------\n");
    for (i = 0; i < np; i++) {
        if (alloc[i] != -1)
            printf("P%-9d %-12d Block %-6d %-12d\n", i+1, procs[i], alloc[i], bsize[alloc[i]-1]);
        else
            printf("P%-9d %-12d Not Allocated\n", i+1, procs[i]);
    }
    return 0;
}
