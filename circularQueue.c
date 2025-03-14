#include <stdio.h>
#define max 20
char queue[max];
int front = -1;
int rear = -1;
void enqueue(int n)
{
    if ((rear + 1) % max == front)
    {
        printf("The queue is full");
        return;
    }
    else if (front == -1 && rear == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % max;
    }
    queue[rear] = n;
}
int dequeue()
{
    if (front == -1)
    {
        printf("Queue is empty");
        return -1;
    }
    int temp = queue[front];
    front = (front + 1) % max;
    printf("The deleted element is %d\n", temp);
    return temp;
}
void display()
{

    if (front == -1)
    {
        printf("que is empty");
        return;
    }
    else
    {
        int i = front;
        while (i != rear)
        {
            printf("%d\t", queue[i]);
            i = (i + 1) % max;
        }
        printf("%d\t", queue[rear]);
    }
}
int main()
{
    enqueue(5);
    enqueue(6);
    enqueue(3);
    enqueue(4);
    display();
    dequeue();
    dequeue();
    dequeue();

    enqueue(7);
    enqueue(3);
    display();
    return 0;
}