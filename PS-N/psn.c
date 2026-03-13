#include <stdio.h>

int main() {
    int n, i;
    int pid[20], at[20], bt[20], pr[20];
    int rt[20], ct[20], tat[20], wt[20];

    int current_time = 0, completed = 0;
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

        printf("Priority: ");
        scanf("%d", &pr[i]);

        rt[i] = bt[i];
    }

    while(completed < n) {
        highest_priority = 9999;
        selected = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= current_time && rt[i] > 0) {
                if(pr[i] < highest_priority) {
                    highest_priority = pr[i];
                    selected = i;
                }
            }
        }

        if(selected == -1)
            current_time++;
        else {
            rt[selected]--;
            current_time++;

            if(rt[selected] == 0) {
                ct[selected] = current_time;
                tat[selected] = ct[selected] - at[selected];
                wt[selected] = tat[selected] - bt[selected];

                avg_wt += wt[selected];
                avg_tat += tat[selected];

                completed++;
            }
        }
    }

    printf("\nPID\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", pid[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}
