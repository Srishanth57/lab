#include <stdio.h>
#include <stdbool.h>
#define SIZE 20

int calc_lfu_with_recency(int arr[], int count)
{
    int frame[3] = {-1, -1, -1}; // Frame array
    int freq[3] = {0, 0, 0};     // Frequency counter for each frame position
    int recent[3] = {0, 0, 0};   // Recency tracker (higher = more recent)
    int page_faults = 0;
    int time = 0; // Simulated time for recency

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
            int replace_idx = 0;
            if (frame[2] == -1)
            { // If there's empty space
                for (int i = 0; i < 3; i++)
                {
                    if (frame[i] == -1)
                    {
                        replace_idx = i;
                        break;
                    }
                }
            }
            else
            { // Find least frequently used, with recency as tiebreaker
                int min_freq = freq[0];
                int min_recent = recent[0];
                replace_idx = 0;

                for (int i = 1; i < 3; i++)
                {
                    // If this frequency is lower, choose it
                    if (freq[i] < min_freq)
                    {
                        min_freq = freq[i];
                        min_recent = recent[i];
                        replace_idx = i;
                    }
                    // If frequencies are equal, use recency
                    else if (freq[i] == min_freq && recent[i] < min_recent)
                    {
                        min_recent = recent[i];
                        replace_idx = i;
                    }
                }
            }
            frame[replace_idx] = arr[index];
            freq[replace_idx] = 1;        // New page starts with frequency 1
            recent[replace_idx] = ++time; // Set recency to current time
            page_faults++;
        }
        else
        {                         // Page hit
            freq[pos]++;          // Increment frequency
            recent[pos] = ++time; // Update recency
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

    printf("\nLFU with Recency Algorithm:\n");
    int faults = calc_lfu_with_recency(arr, count);
    printf("Total page faults: %d\n", faults);

    return 0;
}