#include <stdio.h>

void swap(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}

int partition(int a[], int low, int high)
{
    int pivot = a[low];
    int p = low + 1;
    int q = high;

    while (p <= q)
    {
        while (a[p] <= pivot)
            p++;
        while (a[q] > pivot)
            q--;

        if (p < q)
        {
            swap(&a[p], &a[q]);
        }
    }

    swap(&a[low], &a[q]);
    return q;
}

void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int i = partition(a, low, high);
        quickSort(a, low, i - 1);
        quickSort(a, i + 1, high);
    }
}

int main()
{
    printf("The Quick Sort algorithm:\n");

    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int arr[20];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    quickSort(arr, 0, size);

    printf("The sorted array is:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
