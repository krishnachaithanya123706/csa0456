/*
 * Q39: C-SCAN (Circular SCAN) Disk Scheduling Algorithm
 *      Head moves in one direction only; upon reaching the end,
 *      it jumps to the beginning and continues in the same direction.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int cmp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main() {
    int n, head, disk_size;
    int requests[MAX];
    int total_movement = 0;

    printf("=== C-SCAN Disk Scheduling ===\n");
    printf("Enter number of disk requests: "); scanf("%d", &n);
    printf("Enter disk requests:\n");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: "); scanf("%d", &head);
    printf("Enter disk size (max cylinder no.): "); scanf("%d", &disk_size);

    qsort(requests, n, sizeof(int), cmp);

    /* Find starting position */
    int pos = 0;
    while (pos < n && requests[pos] < head) pos++;

    printf("\nHead Movement (C-SCAN, right direction): %d", head);
    int current = head;

    /* Service right side */
    for (int i = pos; i < n; i++) {
        total_movement += abs(requests[i] - current);
        current = requests[i];
        printf(" -> %d", current);
    }

    /* Jump to end, then to beginning */
    if (current != disk_size - 1) {
        total_movement += abs(disk_size - 1 - current);
        current = disk_size - 1;
        printf(" -> %d [end]", current);
    }
    /* Jump to 0 (no service during return) */
    total_movement += current; /* cost of jump to 0 */
    current = 0;
    printf(" ~~> 0 [jump]");

    /* Service left side requests (wrapped) */
    for (int i = 0; i < pos; i++) {
        total_movement += abs(requests[i] - current);
        current = requests[i];
        printf(" -> %d", current);
    }

    printf("\n\nTotal Head Movement : %d cylinders\n", total_movement);
    printf("Average Seek Time   : %.2f cylinders\n", (float)total_movement / n);
    return 0;
}
