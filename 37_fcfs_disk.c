/*
 * Q37: FCFS Disk Scheduling Algorithm
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int main() {
    int n, head, i;
    int requests[MAX];
    int total_movement = 0;

    printf("=== FCFS Disk Scheduling ===\n");
    printf("Enter number of disk requests: "); scanf("%d", &n);
    printf("Enter disk requests:\n");
    for (i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: "); scanf("%d", &head);

    printf("\nHead Movement:\n%d", head);
    int current = head;
    for (i = 0; i < n; i++) {
        int seek = abs(requests[i] - current);
        total_movement += seek;
        current = requests[i];
        printf(" -> %d", current);
    }

    printf("\n\nTotal Seek Operations : %d\n", n);
    printf("Total Head Movement   : %d cylinders\n", total_movement);
    printf("Average Seek Time     : %.2f cylinders\n", (float)total_movement / n);

    return 0;
}
