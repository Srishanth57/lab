#include <stdio.h>
#include <stdlib.h>
#define max 20
int rear = -1, front = -1;
int queue[max];
void enqueue(int k)
{
    if (rear == max - 1)
    {
        printf("Overflow\n");
        return;
    }
    else if (front == -1 && rear == -1)
    {
        front = 0;
        rear = 0;
        queue[rear++] = k;
    }
    else
    {
        queue[rear++] = k;
    }
}

void dequeue()
{

    if (front == -1 && rear == -1)
    {
        printf("Underflow\n");
        return;
    }
    else if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        int temp = queue[front];
        printf("%d value is deleted\n", temp);
        front++;
    }
}
void traverse()
{
    if (front == rear)
    {
        printf("Stack is empty\n");
        return;
    }
    for (int i = front; i < rear; i++)
    {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main()
{

    while (1)
    {
        int choice, value;
        printf("1.Enqueue\n2.Dequeue\n3.Traverse\n4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:

            printf("Enter value: ");
            scanf("%d", &value);
            enqueue(value);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            traverse();
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}