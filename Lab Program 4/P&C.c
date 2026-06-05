#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// The Buffer Array and Pointers
int buffer[MAX];
int in = 0;
int out = 0;

// The Semaphores
int mutex = 1;      // Master lock (1 = Unlocked, 0 = Locked)
int empty = MAX;    // Counts empty slots
int full = 0;       // Counts filled slots

// Custom Semaphore Functions
void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

int main() {
    int choice, item;

    printf("--- Producer-Consumer (Custom Semaphores) ---\n");
    printf("Buffer Size: %d\n", MAX);

    while (1) {
        printf("\n[ State -> Full: %d | Empty: %d | Mutex: %d ]\n", full, empty, mutex);
        printf("1. Produce\n");
        printf("2. Consume\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            // ==========================================
            // OPTION 1: PRODUCE
            // ==========================================
            case 1:
                // Check if there is an empty slot AND the master lock is available
                if (empty > 0 && mutex == 1) {
                    printf("Enter item value to produce: ");
                    scanf("%d", &item);

                    wait(&empty);  // Take an empty slot
                    wait(&mutex);  // Lock the buffer

                    // --- CRITICAL SECTION START ---
                    buffer[in] = item;
                    printf("\nSUCCESS: Produced item %d at slot %d\n", item, in);
                    in = (in + 1) % MAX; // Move pointer circularly
                    // --- CRITICAL SECTION END ---

                    signal(&mutex); // Unlock the buffer
                    signal(&full);  // Add to the full slot count

                } else {
                    printf("\nERROR: Buffer is full! Cannot produce.\n");
                }
                break;

            // ==========================================
            // OPTION 2: CONSUME
            // ==========================================
            case 2:
                // Check if there is a full slot AND the master lock is available
                if (full > 0 && mutex == 1) {
                    
                    wait(&full);   // Take a full slot
                    wait(&mutex);  // Lock the buffer

                    // --- CRITICAL SECTION START ---
                    item = buffer[out];
                    printf("\nSUCCESS: Consumed item %d from slot %d\n", item, out);
                    out = (out + 1) % MAX; // Move pointer circularly
                    // --- CRITICAL SECTION END ---

                    signal(&mutex); // Unlock the buffer
                    signal(&empty); // Add to the empty slot count

                } else {
                    printf("\nERROR: Buffer is empty! Cannot consume.\n");
                }
                break;

            // ==========================================
            // OPTION 3: EXIT
            // ==========================================
            case 3:
                exit(0);

            default:
                printf("\nInvalid choice!\n");
        }
    }
    return 0;
}
