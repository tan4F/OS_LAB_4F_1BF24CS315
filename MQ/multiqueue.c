#include <stdio.h>

typedef struct {
    int pid, at, bt, rem, ct, tat, wt, type;
} P;

void display(P a[], int n) {
    float tat = 0, wt = 0;

    printf("\nPID Q AT BT CT TAT WT\n");
    for(int i = 0; i < n; i++) {
        a[i].tat = a[i].ct - a[i].at;
        a[i].wt = a[i].tat - a[i].bt;

        tat += a[i].tat;
        wt += a[i].wt;

        printf("%d  %d %d %d %d %d %d\n",
               a[i].pid, a[i].type, a[i].at, a[i].bt,
               a[i].ct, a[i].tat, a[i].wt);
    }

    printf("\nAvg TAT = %.2f | Avg WT = %.2f\n", tat/n, wt/n);
}

int main() {
    int n, tq, t = 0, done = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    P p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d [AT BT Type(1/2)]: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].type);

        p[i].rem = p[i].bt;
        p[i].ct = 0;
    }
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(p[i].at > p[j].at) {
                P temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    while(done < n) {
        int flag = 0;
        for(int i = 0; i < n; i++) {
            if(p[i].type == 1 && p[i].rem > 0 && p[i].at <= t) {
                flag = 1;

                int slice = (p[i].rem > tq) ? tq : p[i].rem;
                p[i].rem -= slice;
                t += slice;

                if(p[i].rem == 0) {
                    p[i].ct = t;
                    done++;
                }
            }
        }
        if(!flag) {
            for(int i = 0; i < n; i++) {
                if(p[i].type == 2 && p[i].rem > 0 && p[i].at <= t) {
                    flag = 1;

                    t += p[i].rem;
                    p[i].rem = 0;
                    p[i].ct = t;
                    done++;

                    break;
                }
            }
        }

        if(!flag) t++;
    }

    display(p, n);
    return 0;
}
