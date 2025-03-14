#include <stdio.h>
#define max 20

void merge(int a[], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = 0;
    int b[max];

    while (i <= mid && j <= high)
    {
        if (a[i] <= a[j])
        {
            b[k] = a[i];
            k++, i++;
        }
        else
        {
            b[k] = a[j];
            k++, j++;
        }
    }

    while (i <= mid)
    {
        b[k] = a[i];
        k++, i++;
    }

    while (j <= high)
    {
        b[k] = a[j];
        k++, j++;
    }

    for (i = low, k = 0; i <= high; i++, k++)
    {
        a[i] = b[k];
    }
}

void mergeSort(int a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    mergeSort(arr, 0, n - 1);

    printf("The sorted array is:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
