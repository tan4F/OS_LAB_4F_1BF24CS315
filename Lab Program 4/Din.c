#include <stdio.h>
#include <stdlib.h>

#define N 5

int fork_sem[N] = {1, 1, 1, 1, 1}; // The Orbs (1 = Free, 0 = Taken)
int eating[N] = {0};               // Player State (1 = Eating, 0 = Waiting)

void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

int main() {
    int p, left, right, choice, count;

    printf("--- Dining Philosophers (Custom Semaphores) ---\n");

    while (1) {
        printf("\n1. Single Philosopher Starts Eating\n");
        printf("2. Multiple Philosophers Start Eating (2 or more)\n");
        printf("3. Stop Eating\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            // ==========================================
            // OPTION 1: SINGLE PHILOSOPHER
            // ==========================================
            case 1:
                printf("Enter Philosopher ID (0 to 4): ");
                scanf("%d", &p);

                if (p < 0 || p >= N) {
                    printf("Invalid ID!\n");
                    continue;
                }

                left = p;
                right = (p + 1) % N; 

                // Check if BOTH forks are available
                if (fork_sem[left] > 0 && fork_sem[right] > 0) {
                    wait(&fork_sem[left]);
                    wait(&fork_sem[right]);
                    eating[p] = 1; 
                    printf("\nPhilosopher %d is EATING (Grabbed forks %d and %d)\n", p, left, right);
                } else {
                    printf("\nPhilosopher %d must WAIT. Forks are busy.\n", p);
                }
                break;

            // ==========================================
            // OPTION 2: MULTIPLE PHILOSOPHERS (2 OR MORE)
            // ==========================================
           /* case 2:
                printf("How many philosophers want to eat at the same time? ");
                scanf("%d", &count);

                if (count < 2 || count > N) {
                    printf("Invalid count! Must be between 2 and %d.\n", N);
                    continue;
                }

                int req[N];
                int temp_forks[N] = {0}; // Shopping list to track conflicts internally
                int conflict = 0;

                for (int i = 0; i < count; i++) {
                    printf("Enter Philosopher ID %d: ", i + 1);
                    scanf("%d", &req[i]);
                    
                    if (req[i] < 0 || req[i] >= N || eating[req[i]] == 1) {
                        printf("Invalid ID or they are already eating!\n");
                        conflict = 1;
                    }
                }

                if (conflict) break;

                // Check for conflicts on the forks
                for (int i = 0; i < count; i++) {
                    left = req[i];
                    right = (req[i] + 1) % N;
                    
                    temp_forks[left]++;
                    temp_forks[right]++;
                    
                    // If a fork is already taken globally, OR if two requested players want the same fork locally
                    if (fork_sem[left] <= 0 || fork_sem[right] <= 0 || temp_forks[left] > 1 || temp_forks[right] > 1) {
                        conflict = 1;
                    }
                }

                if (conflict) {
                    printf("\nConflict! Those philosophers cannot all eat at the same time. Someone must wait.\n");
                } else {
                    // No conflicts! Everyone gets to eat simultaneously
                    for (int i = 0; i < count; i++) {
                        left = req[i];
                        right = (req[i] + 1) % N;
                        
                        wait(&fork_sem[left]);
                        wait(&fork_sem[right]);
                        eating[req[i]] = 1;
                        
                        printf("Philosopher %d is EATING (Grabbed forks %d and %d)\n", req[i], left, right);
                    }
                    printf("\nAll requested philosophers successfully started eating!\n");
                }
                break; */
 
            // ==========================================
            // OPTION 3: STOP EATING
            // ==========================================
            case 3:
                printf("Enter Philosopher ID to stop eating (0 to 4): ");
                scanf("%d", &p);

                if (p < 0 || p >= N) {
                    printf("Invalid ID!\n");
                    continue;
                }

                if (eating[p] == 1) {
                    left = p;
                    right = (p + 1) % N;

                    signal(&fork_sem[left]);
                    signal(&fork_sem[right]);
                    eating[p] = 0; 
                    
                    printf("\nPhilosopher %d stopped eating and dropped forks %d and %d\n", p, left, right);
                } else {
                    printf("\nPhilosopher %d is not eating right now.\n", p);
                }
                break;

            // ==========================================
            // OPTION 4: EXIT
            // ==========================================
            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
