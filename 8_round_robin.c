#include <stdio.h>

#define MAX 20

int main() {
    int n, i, tq;
    int pid[MAX], bt[MAX], at[MAX], rem_bt[MAX];
    int wt[MAX], tat[MAX], ct[MAX];
    float avg_wt = 0, avg_tat = 0;

    printf("=== Round Robin Scheduling ===\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d - Burst Time  : ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
        wt[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int current_time = 0, done = 0;
    int queue[MAX * 100], front = 0, rear = 0;
    int in_queue[MAX];
    for (i = 0; i < n; i++) in_queue[i] = 0;

    /* Add processes with arrival time 0 */
    for (i = 0; i < n; i++) {
        if (at[i] == 0) { queue[rear++] = i; in_queue[i] = 1; }
    }

    while (done < n) {
        if (front == rear) { current_time++; /* idle */
            for (i = 0; i < n; i++) {
                if (!in_queue[i] && rem_bt[i] > 0 && at[i] <= current_time) {
                    queue[rear++] = i; in_queue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        int exec = (rem_bt[idx] > tq) ? tq : rem_bt[idx];
        current_time += exec;
        rem_bt[idx] -= exec;

        /* Enqueue newly arrived processes */
        for (i = 0; i < n; i++) {
            if (!in_queue[i] && rem_bt[i] > 0 && at[i] <= current_time) {
                queue[rear++] = i; in_queue[i] = 1;
            }
        }

        if (rem_bt[idx] == 0) {
            ct[idx]  = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx]  = tat[idx] - bt[idx];
            avg_tat += tat[idx];
            avg_wt  += wt[idx];
            done++;
        } else {
            queue[rear++] = idx; /* re-enqueue */
        }
    }

    printf("\n%-6s %-8s %-8s %-8s %-8s %-8s\n",
           "PID", "AT", "BT", "CT", "TAT", "WT");
    printf("----------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-6d %-8d %-8d %-8d %-8d %-8d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Turnaround Time : %.2f\n", avg_tat / n);
    printf("Average Waiting Time    : %.2f\n", avg_wt  / n);

    return 0;
}
