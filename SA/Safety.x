#include <stdio.h>

int main() {
    int n, m, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], work[m], safeSeq[n];
    int finish[n];

    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Maximum Demand Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    for (j = 0; j < m; j++) {
        work[j] = avail[j];
    }

    int count = 0;

    while (count < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canRun = 1;

                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = 0;
                        break;
                    }
                }

                if (canRun == 1) {
                    for (j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }

                    safeSeq[count] = i;
                    count++;

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            printf("\nSystem is not in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in a safe state.\n");
    printf("Safe sequence is: ");

    for (i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);

        if (i < n - 1) {
            printf(" -> ");
        }
    }

    printf("\n");

    return 0;
}
