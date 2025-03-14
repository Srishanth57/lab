#include <stdio.h>
#define max 10
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (arr[largest] < arr[l] && l < n)
        largest = l;
    if (arr[largest] < arr[r] && r < n)
        largest = r;
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapSort(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(a, n, i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}

int main()
{
    int n;
    printf("enter the number of elements\n");
    scanf("%d", &n);
    int arr[max];
    printf("enter the elements\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    heapSort(arr, n);
    printf("the sorted array is\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}