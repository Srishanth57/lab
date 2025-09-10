#include <stdio.h>
#include <stdbool.h>
#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

// Function to print allocation results
void print_allocation(int blocks[], int n, int process[], int m, int allocation[])
{
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < m; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, process[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// First Fit Allocation
void first_fit(int blocks[], int n, int process[], int m)
{
    int allocation[MAX_PROCESSES];
    int block_copy[MAX_BLOCKS];

    // Initialize allocation array and copy blocks
    for (int i = 0; i < m; i++)
        allocation[i] = -1;
    for (int i = 0; i < n; i++)
        block_copy[i] = blocks[i];

    // Allocate processes
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (block_copy[j] >= process[i])
            {
                allocation[i] = j;
                block_copy[j] -= process[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:");
    print_allocation(blocks, n, process, m, allocation);
}

// Best Fit Allocation
void best_fit(int blocks[], int n, int process[], int m)
{
    int allocation[MAX_PROCESSES];
    int block_copy[MAX_BLOCKS];

    // Initialize allocation array and copy blocks
    for (int i = 0; i < m; i++)
        allocation[i] = -1;
    for (int i = 0; i < n; i++)
        block_copy[i] = blocks[i];

    // Allocate processes
    for (int i = 0; i < m; i++)
    {
        int best_idx = -1;
        for (int j = 0; j < n; j++)
        {
            if (block_copy[j] >= process[i])
            {
                if (best_idx == -1 || block_copy[j] < block_copy[best_idx])
                {
                    best_idx = j;
                }
            }
        }
        if (best_idx != -1)
        {
            allocation[i] = best_idx;
            block_copy[best_idx] -= process[i];
        }
    }

    printf("\nBest Fit Allocation:");
    print_allocation(blocks, n, process, m, allocation);
}

// Worst Fit Allocation
void worst_fit(int blocks[], int n, int process[], int m)
{
    int allocation[MAX_PROCESSES];
    int block_copy[MAX_BLOCKS];

    // Initialize allocation array and copy blocks
    for (int i = 0; i < m; i++)
        allocation[i] = -1;
    for (int i = 0; i < n; i++)
        block_copy[i] = blocks[i];

    // Allocate processes
    for (int i = 0; i < m; i++)
    {
        int worst_idx = -1;
        for (int j = 0; j < n; j++)
        {
            if (block_copy[j] >= process[i])
            {
                if (worst_idx == -1 || block_copy[j] > block_copy[worst_idx])
                {
                    worst_idx = j;
                }
            }
        }
        if (worst_idx != -1)
        {
            allocation[i] = worst_idx;
            block_copy[worst_idx] -= process[i];
        }
    }

    printf("\nWorst Fit Allocation:");
    print_allocation(blocks, n, process, m, allocation);
}

int main()
{
    int blocks[MAX_BLOCKS], process[MAX_PROCESSES];
    int n, m;

    // Input number of blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    // Input block sizes
    printf("Enter the sizes of memory blocks:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i]);
    }

    // Input number of processes
    printf("\nEnter the number of processes: ");
    scanf("%d", &m);

    // Input process sizes
    printf("Enter the sizes of processes:\n");
    for (int i = 0; i < m; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &process[i]);
    }

    // Simulate all three algorithms
    first_fit(blocks, n, process, m);
    best_fit(blocks, n, process, m);
    worst_fit(blocks, n, process, m);

    return 0;
}