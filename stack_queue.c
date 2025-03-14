#include <stdio.h>
#include <stdlib.h>
#define max 10
int front = -1, rear = -1;
int que[max];
void enque(int n)
{
    if (rear == max - 1)
    {
        printf("Queue is full");
    }
    else
    {
        if (front == -1 && rear == -1)
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear++;
        }
        que[rear] = n;
        printf("%d enqueued", n);
    }
}
int deque()
{
    if (front == -1 || rear == -1)
    {
        printf("Queue is empty");
        return -1;
    }
    else
    {

        return que[front++];
    }
}
void display()
{
    if (front == -1 || rear == -1)
    {
        printf("Queue is empty");
        return;
    }
    else
    {
        for (int i = front; i <= rear; i++)
        {
            printf("%d\t", que[i]);
        }
    }
}
int main()
{
    int n, c, d;
    while (1)
    {
        printf("\n1.Enque\n 2.Deque\n 3.Display \n 4.Exit\n Enter your choice:");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            printf("Enter the element to insert:");
            scanf("%d", &n);
            enque(n);
            break;
        case 2:

            d = deque();
            if (front != rear)
                printf("%d deleted", d);

            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
        }
    }
    return 0;
}
