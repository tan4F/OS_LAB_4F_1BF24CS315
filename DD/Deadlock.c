#include <stdio.h>

int main() {
    int n, m, i, j;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[100][100], request[100][100];
    int avail[100], work[100], safeSeq[100];
    int finish[100];

    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i);

        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i);

        for (j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter the available resources: ");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    for (j = 0; j < m; j++) {
        work[j] = avail[j];
    }

    int count = 0;

    while (count < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canSatisfy = 1;

                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canSatisfy = 0;
                        break;
                    }
                }

                if (canSatisfy == 1) {
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
            printf("System is in deadlock.\n");
            return 0;
        }
    }

    printf("System is in safe state.\n");
    printf("Safe Sequence is: ");

    for (i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }

    printf("\n");

    return 0;
}
