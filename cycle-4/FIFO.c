#include <stdio.h>
#include <stdbool.h>
#define SIZE 20

int calc_fifo(int arr[], int count)
{
    int frame[3] = {-1, -1, -1}; // Initialize frame with -1 to indicate empty
    int page_faults = 0;         // Counter for page faults
    int n = 0;                   // Number of filled frames
    int index = 0;               // Current position in arr

    while (index < count)
    { // Changed from count>0 to process all elements
        bool flag = false;

        // Check if page already exists in frame
        for (int i = 0; i < 3; i++)
        {
            if (frame[i] == arr[index])
            {
                flag = true;
                break;
            }
        }

        // If page not found in frame
        if (!flag)
        {
            // If frame has space, add new page
            if (n < 3)
            {
                frame[n++] = arr[index];
                page_faults++;
            }
            // If frame is full, replace oldest page (FIFO)
            else
            {
                // When frame is full, remove oldest page (first in) by shifting
                // and add new page at end (first out)
                for (int i = 0; i < 2; i++)
                {
                    frame[i] = frame[i + 1];
                }
                frame[2] = arr[index]; // New page takes the last position
                page_faults++;
            }
        }

        // Print current frame state (for debugging)
        printf("Page: %d | Frames: ", arr[index]);
        for (int i = 0; i < 3; i++)
        {
            if (frame[i] != -1)
                printf("%d ", frame[i]);
            else
                printf("- ");
        }
        printf("\n");

        index++;
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

    int faults = calc_fifo(arr, count);
    printf("Total page faults: %d\n", faults);

    return 0;
}