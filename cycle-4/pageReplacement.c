#include <stdio.h>
#include <stdbool.h>
#define SIZE 20

// FIFO Algorithm
int calc_fifo(int arr[], int count)
{
    int frame[3] = {-1, -1, -1};
    int page_faults = 0, n = 0;
    int idx = 0;
    for (int index = 0; index < count; index++)
    {
        bool flag = false;
        for (int i = 0; i < 3; i++)
        {
            if (frame[i] == arr[index])
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {

            frame[idx] = arr[index];
            idx = (idx + 1) % 3;

            page_faults++;
        }
        printf("Page: %d | Frames: ", arr[index]);
        for (int i = 0; i < 3; i++)
            printf("%d ", frame[i] != -1 ? frame[i] : -1);
        printf("\n");
    }
    return page_faults;
}

// LFU with Recency Algorithm
int calc_lfu_with_recency(int arr[], int count)
{
    int frame[3] = {-1, -1, -1}, freq[3] = {0}, recent[3] = {0};
    int page_faults = 0, time = 0;

    for (int index = 0; index < count; index++)
    {
        bool flag = false;
        int pos = -1;
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
        {
            int replace_idx = 0, min_freq = freq[0], min_recent = recent[0];
            if (frame[2] != -1)
            {
                for (int i = 1; i < 3; i++)
                {
                    if (freq[i] < min_freq || (freq[i] == min_freq && recent[i] < min_recent))
                    {
                        min_freq = freq[i];
                        min_recent = recent[i];
                        replace_idx = i;
                    }
                }
            }
            else
            {
                for (int i = 0; i < 3; i++)
                    if (frame[i] == -1)
                    {
                        replace_idx = i;
                        break;
                    }
            }
            frame[replace_idx] = arr[index];
            freq[replace_idx] = 1;
            recent[replace_idx] = ++time;
            page_faults++;
        }
        else
        {
            freq[pos]++;
            recent[pos] = ++time;
        }
        printf("Page: %d | Frames: ", arr[index]);
        for (int i = 0; i < 3; i++)
            printf("%d ", frame[i] != -1 ? frame[i] : -1);
        printf("\n");
    }
    return page_faults;
}

// LRU Algorithm
int calc_lru(int arr[], int count)
{
    int frame[3] = {-1, -1, -1}, recent[3] = {0}, page_faults = 0, time = 0;
    for (int index = 0; index < count; index++)
    {
        bool flag = false;
        int pos = -1;
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
        {
            int lru_idx = 0, min_time = recent[0];
            if (frame[2] != -1)
            {
                for (int i = 1; i < 3; i++)
                    if (recent[i] < min_time)
                    {
                        min_time = recent[i];
                        lru_idx = i;
                    }
            }
            else
            {
                for (int i = 0; i < 3; i++)
                    if (frame[i] == -1)
                    {
                        lru_idx = i;
                        break;
                    }
            }
            frame[lru_idx] = arr[index];
            recent[lru_idx] = ++time;
            page_faults++;
        }
        else
        {
            recent[pos] = ++time;
        }
        printf("Page: %d | Frames: ", arr[index]);
        for (int i = 0; i < 3; i++)
            printf("%d ", frame[i] != -1 ? frame[i] : -1);
        printf("\n");
    }
    return page_faults;
}

int main()
{
    int count, arr[SIZE], choice;
    printf("Enter the number of pages: ");
    scanf("%d", &count);
    if (count > SIZE)
    {
        printf("Input exceeds maximum size of %d\n", SIZE);
        return 1;
    }
    printf("Enter the page sequence: ");
    for (int i = 0; i < count; i++)
        scanf("%d", &arr[i]);

    printf("\nChoose an Algorithm:\n");
    printf("1. FIFO\n2. LFU with Recency\n3. LRU\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int faults = 0;
    switch (choice)
    {
    case 1:
        printf("\nFIFO Algorithm:\n");
        faults = calc_fifo(arr, count);
        break;
    case 2:
        printf("\nLFU with Recency Algorithm:\n");
        faults = calc_lfu_with_recency(arr, count);
        break;
    case 3:
        printf("\nLRU Algorithm:\n");
        faults = calc_lru(arr, count);
        break;
    default:
        printf("Invalid choice!\n");
        return 1;
    }
    printf("Total page faults: %d\n", faults);
    return 0;
}