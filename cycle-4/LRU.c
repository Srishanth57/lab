#include <stdio.h>
#include <stdbool.h>
#define SIZE 20

int calc_lru(int arr[], int count)
{
    int frame[3] = {-1, -1, -1}; // Frame array
    int recent[3] = {0, 0, 0};   // Tracks usage order (higher = more recent)
    int page_faults = 0;
    int time = 0; // Simulated time for tracking recency

    for (int index = 0; index < count; index++)
    {
        bool flag = false;
        int pos = -1;

        // Check if page exists in frame
        for (int i = 0; i < 3; i++)
        {
            if (frame[i] == arr[index])
            {
                flag = true;
                pos = i;
                break;
            }
        }

        if (!flag)
        { // Page fault
            // Find empty slot or least recently used
            int lru_idx = 0;
            if (frame[2] == -1)
            { // If there's empty space
                for (int i = 0; i < 3; i++)
                {
                    if (frame[i] == -1)
                    {
                        lru_idx = i;
                        break;
                    }
                }
            }
            else
            { // Find least recently used
                int min_time = recent[0];
                for (int i = 1; i < 3; i++)
                {
                    if (recent[i] < min_time)
                    {
                        min_time = recent[i];
                        lru_idx = i;
                    }
                }
            }
            frame[lru_idx] = arr[index];
            recent[lru_idx] = ++time;
            page_faults++;
        }
        else
        { // Page hit - update recency
            recent[pos] = ++time;
        }

        // Print current state
        printf("Page: %d | Frames: ", arr[index]);
        for (int i = 0; i < 3; i++)
        {
            if (frame[i] != -1)
                printf("%d ", frame[i]);
            else
                printf("- ");
        }
        printf("\n");
    }
    return page_faults;
}
int main()
{
    int count;
    int arr[SIZE];

    printf("Enter the number of processes: ");
    scanf("%d", &count);

    if (count > SIZE)
    {
        printf("Input exceeds maximum size of %d\n", SIZE);
        return 1;
    }

    printf("Enter the process sequence (space separated): ");
    for (int i = 0; i < count; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Test LRU
    printf("\nLRU Algorithm:\n");
    int lru_faults = calc_lru(arr, count);
    printf("Total LRU page faults: %d\n", lru_faults);

     return 0;
}