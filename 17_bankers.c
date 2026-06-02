/*
 * Q17: Banker's Algorithm (Deadlock Avoidance)
 */
#include <stdio.h>

#define MAX_P 10
#define MAX_R 10

int n, m; /* processes, resources */
int alloc[MAX_P][MAX_R], max_need[MAX_P][MAX_R];
int need[MAX_P][MAX_R], avail[MAX_R];

void compute_need() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max_need[i][j] - alloc[i][j];
}

int is_safe() {
    int work[MAX_R], finish[MAX_P] = {0};
    int safe_seq[MAX_P], count = 0;

    for (int j = 0; j < m; j++) work[j] = avail[j];

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int ok = 1;
                for (int j = 0; j < m; j++)
                    if (need[i][j] > work[j]) { ok = 0; break; }
                if (ok) {
                    for (int j = 0; j < m; j++) work[j] += alloc[i][j];
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) { printf("System is in UNSAFE state (Deadlock possible).\n"); return 0; }
    }

    printf("System is in SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++) printf("P%d%s", safe_seq[i], i < n-1 ? " -> " : "\n");
    return 1;
}

int main() {
    printf("=== Banker's Algorithm ===\n");
    printf("Number of processes : "); scanf("%d", &n);
    printf("Number of resources : "); scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("  P%d: ", i);
        for (int j = 0; j < m; j++) scanf("%d", &alloc[i][j]);
    }
    printf("Enter Maximum Need Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("  P%d: ", i);
        for (int j = 0; j < m; j++) scanf("%d", &max_need[i][j]);
    }
    printf("Enter Available Resources: ");
    for (int j = 0; j < m; j++) scanf("%d", &avail[j]);

    compute_need();

    printf("\n--- Need Matrix ---\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) printf("%d ", need[i][j]);
        printf("\n");
    }

    printf("\n");
    is_safe();
    return 0;
}
