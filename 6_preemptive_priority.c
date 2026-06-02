#include <stdio.h>

#define MAX 20

int main() {
    int n, i;
    int pid[MAX], bt[MAX], at[MAX], pr[MAX];
    int rem_bt[MAX], wt[MAX], tat[MAX], ct[MAX];
    int done[MAX];
    float avg_wt = 0, avg_tat = 0;

    printf("=== Preemptive Priority Scheduling ===\n");
    printf("(Lower number = Higher priority)\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d - Burst Time  : ", i + 1);
        scanf("%d", &bt[i]);
        printf("Process %d - Priority    : ", i + 1);
        scanf("%d", &pr[i]);
        rem_bt[i] = bt[i];
        done[i]   = 0;
    }

    int current_time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, min_pr = 99999;
        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= current_time && pr[i] < min_pr) {
                min_pr = pr[i];
                idx = i;
            }
        }

        if (idx == -1) { current_time++; continue; }

        rem_bt[idx]--;
        current_time++;

        if (rem_bt[idx] == 0) {
            ct[idx]  = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx]  = tat[idx] - bt[idx];
            avg_tat += tat[idx];
            avg_wt  += wt[idx];
            done[idx] = 1;
            completed++;
        }
    }

    printf("\n%-6s %-8s %-8s %-8s %-8s %-8s %-8s\n",
           "PID", "AT", "BT", "PR", "CT", "TAT", "WT");
    printf("--------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-6d %-8d %-8d %-8d %-8d %-8d %-8d\n",
               pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Turnaround Time : %.2f\n", avg_tat / n);
    printf("Average Waiting Time    : %.2f\n", avg_wt  / n);

    return 0;
}
