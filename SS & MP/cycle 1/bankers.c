#include <stdio.h>

int main()
{
    int n, r, i, j;
    printf("Enter the no. of processes and resources: ");
    scanf("%d%d", &n, &r);

    int max[n][r], alloc[n][r], need[n][r], avail[r], work[r], finish[n];

    // Input claim matrix (max matrix)
    printf("Enter the claim matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Input allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input resource vector (total resources)
    int resource_vector[r];
    printf("Resource vector:");
    for (int i = 0; i < r; i++)
    {
        scanf("%d", &resource_vector[i]);
    }

    // Calculate available resources = resource_vector - sum of all allocations
    for (int i = 0; i < r; i++)
    {
        avail[i] = resource_vector[i];
        for (int j = 0; j < n; j++)
        {
            avail[i] -= alloc[j][i];
        }
        work[i] = avail[i];
    }

    // Calculate need matrix and initialize finish array
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
        finish[i] = 0;
    }

    int safeSequence[n];
    int flag = 0, count = 0;

    // Banker's algorithm execution
    do
    {
        flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int safe = 1;
                // Check if process can be allocated resources
                for (int j = 0; j < r; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        safe = 0;
                        break;
                    }
                }

                if (safe)
                {
                    // Display process execution details
                    printf("All the resources can be allocated to Process %d ", i + 1);
                    printf("Available resources are: ");

                    // Add allocated resources back to work array
                    for (int j = 0; j < r; j++)
                    {
                        work[j] += alloc[i][j];
                    }

                    // Display updated available resources
                    for (int j = 0; j < r; j++)
                    {
                        printf("%d ", work[j]);
                    }
                    printf("\n");
                    printf("Process %d executed?:y\n", i + 1);

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    flag = 1;
                }
            }
        }
    } while (flag && count < n);

    // Check if system is in safe state
    if (count == n)
    {
        printf("System is in safe mode\n");
        printf("The given state is safe state\n");
    }
    else
    {
        printf("System is not in safe state\n");
        printf("The given state is unsafe state\n");
    }

    return 0;
}