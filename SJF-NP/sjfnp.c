#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[4], at[4], bt[4], ct[4], tat[4], wt[4];
    int completed[4] = {0};
    int current_time = 0, done = 0;

    float avg_tat = 0, avg_wt = 0;


    for(int i = 0; i < n; i++) {
        printf("Enter Process ID for process %d: ", i+1);
        scanf("%d", &pid[i]);

        printf("Enter Arrival Time for process %d: ", i+1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for process %d: ", i+1);
        scanf("%d", &bt[i]);
    }


    while(done < n) {
        int idx = -1;
        int min_bt = 9999; 

       
        for(int i = 0; i < n; i++) {
            if(at[i] <= current_time && completed[i] == 0) {
                if(bt[i] < min_bt) {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

       
        if(idx == -1) {
            current_time++;
        }
        else {
            ct[idx] = current_time + bt[idx];
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            current_time = ct[idx];
            completed[idx] = 1;
            done++;
        }
    }


    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);

    return 0;
}
