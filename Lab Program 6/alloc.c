#include <stdio.h>

int b_num, p_num;

// Memory block sizes
int blocks[20];

// Process sizes
int processes[20];

void first_fit()
{
    int alloc[20];
    int temp_blocks[20];
    int i, j;

    // Initialize allocation array
    for(i=0;i<p_num;i++)
        alloc[i] = -1;

    // Copy original block sizes
    for(i=0;i<b_num;i++)
        temp_blocks[i] = blocks[i];

    // First Fit
    for(i=0;i<p_num;i++)
    {
        for(j=0;j<b_num;j++)
        {
            if(temp_blocks[j] >= processes[i])
            {
                alloc[i] = j;                 // Assign block
                temp_blocks[j] -= processes[i]; // Reduce free space
                break;                        // First suitable block found
            }
        }
    }

    printf("\n--- First Fit ---\n");
    printf("Process\tSize\tBlock\n");

    for(i=0;i<p_num;i++)
    {
        if(alloc[i] != -1)
            printf("P%d\t%d\t%d\n",i+1,processes[i],alloc[i]+1);
        else
            printf("P%d\t%d\tNot Allocated\n",i+1,processes[i]);
    }
}

void best_fit()
{
    int alloc[20];
    int temp_blocks[20];
    int i,j,best_idx;

    for(i=0;i<p_num;i++)
        alloc[i] = -1;

    for(i=0;i<b_num;i++)
        temp_blocks[i] = blocks[i];

    // Best Fit
    for(i=0;i<p_num;i++)
    {
        best_idx = -1;

        for(j=0;j<b_num;j++)
        {
            if(temp_blocks[j] >= processes[i])
            {
                if(best_idx == -1 ||
                   temp_blocks[j] < temp_blocks[best_idx])
                {
                    best_idx = j;
                }
            }
        }

        if(best_idx != -1)
        {
            alloc[i] = best_idx;
            temp_blocks[best_idx] -= processes[i];
        }
    }

    printf("\n--- Best Fit ---\n");
    printf("Process\tSize\tBlock\n");

    for(i=0;i<p_num;i++)
    {
        if(alloc[i] != -1)
            printf("P%d\t%d\t%d\n",i+1,processes[i],alloc[i]+1);
        else
            printf("P%d\t%d\tNot Allocated\n",i+1,processes[i]);
    }
}

void worst_fit()
{
    int alloc[20];
    int temp_blocks[20];
    int i,j,worst_idx;

    for(i=0;i<p_num;i++)
        alloc[i] = -1;

    for(i=0;i<b_num;i++)
        temp_blocks[i] = blocks[i];

    // Worst Fit
    for(i=0;i<p_num;i++)
    {
        worst_idx = -1;

        for(j=0;j<b_num;j++)
        {
            if(temp_blocks[j] >= processes[i])
            {
                if(worst_idx == -1 ||
                   temp_blocks[j] > temp_blocks[worst_idx])
                {
                    worst_idx = j;
                }
            }
        }

        if(worst_idx != -1)
        {
            alloc[i] = worst_idx;
            temp_blocks[worst_idx] -= processes[i];
        }
    }

    printf("\n--- Worst Fit ---\n");
    printf("Process\tSize\tBlock\n");

    for(i=0;i<p_num;i++)
    {
        if(alloc[i] != -1)
            printf("P%d\t%d\t%d\n",i+1,processes[i],alloc[i]+1);
        else
            printf("P%d\t%d\tNot Allocated\n",i+1,processes[i]);
    }
}

int main()
{
    int i, choice;

    printf("Enter number of Memory Blocks: ");
    scanf("%d",&b_num);

    printf("Enter block sizes:\n");
    for(i=0;i<b_num;i++)
        scanf("%d",&blocks[i]);

    printf("Enter number of Processes: ");
    scanf("%d",&p_num);

    printf("Enter process sizes:\n");
    for(i=0;i<p_num;i++)
        scanf("%d",&processes[i]);

    while(1)
    {
        printf("\n1.First Fit");
        printf("\n2.Best Fit");
        printf("\n3.Worst Fit");
        printf("\n4.Exit");
        printf("\nChoice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                first_fit();
                break;

            case 2:
                best_fit();
                break;

            case 3:
                worst_fit();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid Choice\n");
        }
    }
}
