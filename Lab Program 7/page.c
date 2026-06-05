#include <stdio.h>

int n, f;
int ref[100];   // Reference String

// ================= FIFO =================
void fifo()
{
    int mem[20];
    int i, j, k, faults = 0, hit, ptr = 0;

    // Initialize frames as empty
    for (i = 0; i < f; i++)
        mem[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");

    for (i = 0; i < n; i++)
    {
        hit = 0;

        // Check if page already exists
        for (j = 0; j < f; j++)
        {
            if (mem[j] == ref[i])
            {
                hit = 1;
                break;
            }
        }

        // Page Fault
        if (hit == 0)
        {
            mem[ptr] = ref[i];

            // Move pointer circularly
            ptr = (ptr + 1) % f;

            faults++;
        }

        printf("Page %d -> ", ref[i]);

        for (k = 0; k < f; k++)
        {
            if (mem[k] != -1)
                printf("%d ", mem[k]);
            else
                printf("- ");
        }

        if (hit)
            printf("(HIT)\n");
        else
            printf("(FAULT)\n");
    }

    printf("\nTotal FIFO Page Faults = %d\n", faults);
}

// ================= LRU =================
void lru()
{
    int mem[20];
    int time[20];

    int i, j, k;
    int faults = 0;
    int hit;
    int counter = 0;
    int min_time;
    int rep_index;

    for (i = 0; i < f; i++)
    {
        mem[i] = -1;
        time[i] = 0;
    }

    printf("\n--- LRU Page Replacement ---\n");

    for (i = 0; i < n; i++)
    {
        hit = 0;
        counter++;

        // Check for HIT
        for (j = 0; j < f; j++)
        {
            if (mem[j] == ref[i])
            {
                hit = 1;

                // Update last used time
                time[j] = counter;
                break;
            }
        }

        if (hit == 0)
        {
            rep_index = -1;

            // Check for empty frame
            for (j = 0; j < f; j++)
            {
                if (mem[j] == -1)
                {
                    rep_index = j;
                    break;
                }
            }

            // No empty frame -> find LRU page
            if (rep_index == -1)
            {
                rep_index = 0;
                min_time = time[0];

                for (j = 1; j < f; j++)
                {
                    if (time[j] < min_time)
                    {
                        min_time = time[j];
                        rep_index = j;
                    }
                }
            }

            mem[rep_index] = ref[i];
            time[rep_index] = counter;

            faults++;
        }

        printf("Page %d -> ", ref[i]);

        for (k = 0; k < f; k++)
        {
            if (mem[k] != -1)
                printf("%d ", mem[k]);
            else
                printf("- ");
        }

        if (hit)
            printf("(HIT)\n");
        else
            printf("(FAULT)\n");
    }

    printf("\nTotal LRU Page Faults = %d\n", faults);
}

// ================= OPTIMAL =================
void optimal()
{
    int mem[20];
    int i, j, k;
    int faults = 0;
    int hit;
    int rep_index;
    int max_dist;

    for (i = 0; i < f; i++)
        mem[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");

    for (i = 0; i < n; i++)
    {
        hit = 0;

        // Check for HIT
        for (j = 0; j < f; j++)
        {
            if (mem[j] == ref[i])
            {
                hit = 1;
                break;
            }
        }

        if (hit == 0)
        {
            rep_index = -1;

            // Check empty frame
            for (j = 0; j < f; j++)
            {
                if (mem[j] == -1)
                {
                    rep_index = j;
                    break;
                }
            }

            // No empty frame
            if (rep_index == -1)
            {
                max_dist = -1;

                for (j = 0; j < f; j++)
                {
                    for (k = i + 1; k < n; k++)
                    {
                        if (mem[j] == ref[k])
                            break;
                    }

                    // Page used farthest in future
                    if (k > max_dist)
                    {
                        max_dist = k;
                        rep_index = j;
                    }
                }
            }

            mem[rep_index] = ref[i];
            faults++;
        }

        printf("Page %d -> ", ref[i]);

        for (k = 0; k < f; k++)
        {
            if (mem[k] != -1)
                printf("%d ", mem[k]);
            else
                printf("- ");
        }

        if (hit)
            printf("(HIT)\n");
        else
            printf("(FAULT)\n");
    }

    printf("\nTotal Optimal Page Faults = %d\n", faults);
}

// ================= MAIN =================
int main()
{
    int i, choice;

    printf("--- Page Replacement Algorithms ---\n");

    printf("Enter number of Frames: ");
    scanf("%d", &f);

    printf("Enter total pages in Reference String: ");
    scanf("%d", &n);

    printf("Enter Reference String:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    while (1)
    {
        printf("\n1. FIFO");
        printf("\n2. LRU");
        printf("\n3. Optimal");
        printf("\n4. Exit");
        printf("\nEnter choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                fifo();
                break;

            case 2:
                lru();
                break;

            case 3:
                optimal();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
