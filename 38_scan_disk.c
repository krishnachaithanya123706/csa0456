/*
 * Q38: SCAN (Elevator) Disk Scheduling Algorithm
 *      Head moves in one direction servicing requests,
 *      then reverses when no more requests in that direction.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int cmp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main() {
    int n, head, direction, disk_size;
    int requests[MAX];
    int total_movement = 0;

    printf("=== SCAN Disk Scheduling ===\n");
    printf("Enter number of disk requests: "); scanf("%d", &n);
    printf("Enter disk requests:\n");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: "); scanf("%d", &head);
    printf("Enter disk size (max cylinder): "); scanf("%d", &disk_size);
    printf("Direction (0=left, 1=right): "); scanf("%d", &direction);

    qsort(requests, n, sizeof(int), cmp);

    /* Find split point */
    int pos = 0;
    while (pos < n && requests[pos] < head) pos++;

    printf("\nHead Movement: %d", head);
    int current = head;

    if (direction == 1) { /* Move right first */
        for (int i = pos; i < n; i++) {
            total_movement += abs(requests[i] - current);
            current = requests[i];
            printf(" -> %d", current);
        }
        /* Go to end then come back */
        if (current != disk_size - 1) {
            total_movement += abs(disk_size - 1 - current);
            current = disk_size - 1;
            printf(" -> %d", current);
        }
        for (int i = pos - 1; i >= 0; i--) {
            total_movement += abs(requests[i] - current);
            current = requests[i];
            printf(" -> %d", current);
        }
    } else { /* Move left first */
        for (int i = pos - 1; i >= 0; i--) {
            total_movement += abs(requests[i] - current);
            current = requests[i];
            printf(" -> %d", current);
        }
        if (current != 0) {
            total_movement += current;
            current = 0;
            printf(" -> 0");
        }
        for (int i = pos; i < n; i++) {
            total_movement += abs(requests[i] - current);
            current = requests[i];
            printf(" -> %d", current);
        }
    }

    printf("\n\nTotal Head Movement : %d cylinders\n", total_movement);
    printf("Average Seek Time   : %.2f cylinders\n", (float)total_movement / n);
    return 0;
}
