#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rt[n], ct[n], tat[n], wt[n];

    int completed = 0, current_time = 0;
    float avg_tat = 0, avg_wt = 0;

    
    for(int i = 0; i < n; i++) {
        printf("Enter Process ID for process %d: ", i+1);
        scanf("%d", &pid[i]);

        printf("Enter Arrival Time for process %d: ", i+1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for process %d: ", i+1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i]; 
    }

    
    while(completed < n) {
        int min_bt = 9999;
        int min_index = -1;

        for(int i = 0; i < n; i++) {
            if(at[i] <= current_time && rt[i] > 0) {
                if(rt[i] < min_bt) {
                    min_bt = rt[i];
                    min_index = i;
                }
            }
        }

        
        if(min_index == -1) {
            current_time++;
        }
        else {
            rt[min_index]--;   
            current_time++;

           
            if(rt[min_index] == 0) {
                completed++;
                ct[min_index] = current_time;
                tat[min_index] = ct[min_index] - at[min_index];
                wt[min_index] = tat[min_index] - bt[min_index];

                avg_tat += tat[min_index];
                avg_wt += wt[min_index];
            }
        }
    }

    
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);

    return 0;
}
