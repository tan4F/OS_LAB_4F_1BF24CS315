#include <stdio.h>

int main() {
    int n, i;
    int pid[20], at[20], bt[20], pr[20];
    int ct[20], tat[20], wt[20];
    int completed[20] = {0};

    int current_time = 0, completed_count = 0;
    int highest_priority, selected;

    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i+1);

        printf("PID: ");
        scanf("%d", &pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority (lower number = higher priority): ");
        scanf("%d", &pr[i]);
    }

    while(completed_count < n) {
        highest_priority = 9999;
        selected = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= current_time && completed[i] == 0) {
                if(pr[i] < highest_priority) {
                    highest_priority = pr[i];
                    selected = i;
                }
            }
        }

        if(selected == -1)
            current_time++;
        else {
            ct[selected] = current_time + bt[selected];
            tat[selected] = ct[selected] - at[selected];
            wt[selected] = tat[selected] - bt[selected];

            avg_wt += wt[selected];
            avg_tat += tat[selected];

            current_time = ct[selected];
            completed[selected] = 1;
            completed_count++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}
