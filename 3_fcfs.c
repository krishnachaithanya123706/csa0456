#include <stdio.h>

#define MAX 20

int main() {
    int n, i;
    int pid[MAX], bt[MAX], at[MAX];
    int wt[MAX], tat[MAX], ct[MAX];
    float avg_wt = 0, avg_tat = 0;

    printf("=== FCFS Scheduling ===\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d - Burst Time  : ", i + 1);
        scanf("%d", &bt[i]);
        pid[i] = i + 1;
    }

    /* Sort by arrival time (simple bubble sort) */
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (at[j] > at[j + 1]) {
                int tmp;
                tmp = at[j]; at[j] = at[j+1]; at[j+1] = tmp;
                tmp = bt[j]; bt[j] = bt[j+1]; bt[j+1] = tmp;
                tmp = pid[j]; pid[j] = pid[j+1]; pid[j+1] = tmp;
            }
        }
    }

    /* Compute completion, turnaround, and waiting times */
    ct[0] = at[0] + bt[0];
    for (i = 1; i < n; i++) {
        if (ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt  += wt[i];
    }

    /* Display results */
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
