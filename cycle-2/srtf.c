/* Shortest Remaining Time First scheduling is dome with the help of a circular queue.
1) Create a Process & Queue struct
2) Implement the basic Queue conditions
3) Create a Gantt Chart and a ready queue
4) Update the rq according to the arrival time
5) Check whether the rq is empty or there is not cp running? show idle time and continue
6) sortByRt . If cp is null dequeue from rq: enqueue the cp to rq and dequeue from rq;
7) decrement rt of the cp



*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PS 10
#define QS 20
typedef int Gantt;
// Process structure
typedef struct
{
    int id; // Process ID
    int at; // arrival time
    int bt; // burst time
    int rt; // remaining time
    int ct; // completion time
    int wt; // waiting time
    int tt; // turnaround time
} Process;

typedef struct
{
    Process *data[QS];
    int front;
    int rear;
    int size;
} Queue;

// Queue functions
void initQueue(Queue *q)
{
    q->front = -1;
    q->rear = -1;
    q->size = 0;
}

int isEmpty(Queue *q)
{
    return (q->front == -1);
}

int isFull(Queue *q)
{
    return ((q->rear + 1) % QS == q->front);
}

void enqueue(Queue *q, Process *p)
{
    if (isFull(q))
    {
        printf("Queue overflow!\n");
        return;
    }
    else if (isEmpty(q))
    {
        q->front = 0;
        q->rear = 0;
    }
    else
    {
        q->rear = (q->rear + 1) % QS;
    }
    q->data[q->rear] = p;
    q->size++;
}

Process *dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        return NULL;
    }

    Process *p = q->data[q->front];

    // If only one element
    if (q->front == q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1) % QS;
    }
    q->size--;
    return p;
}

Process *peek(Queue *q)
{
    if (isEmpty(q))
    {
        return NULL;
    }
    return q->data[q->front];
}

// Sort the queue by rt time (bubble sort)
void sortByRt(Queue *q)
{
    if (isEmpty(q))
        return;

    int count = q->size;
    int i, j;

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count - i - 1; j++)
        {
            int idx1 = (q->front + j) % QS;
            int idx2 = (q->front + j + 1) % QS;

            if (q->data[idx1]->rt > q->data[idx2]->rt)
            {
                // Swap
                Process *temp = q->data[idx1];
                q->data[idx1] = q->data[idx2];
                q->data[idx2] = temp;
            }
        }
    }
}

// Update the ready queue with newly arrived p
void updateQueue(Queue *q, Process p[], int n, int current_time)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (p[i].at == current_time && p[i].rt > 0)
        {
            enqueue(q, &p[i]);
        }
    }
}

int main()
{
    Process p[PS];
    int n, i, current_time = 0, completed = 0;
    float total_wt = 0, total_tt = 0;
    Queue rq;           // Ready Queue
    Gantt chart[100];   // For Gantt chart
    Process *cp = NULL; // Current Process
    int ci = 0;         // Chart Index

    // Initialize queue
    initQueue(&rq);

    // Input number of p
    printf("Enter number of p: ");
    scanf("%d", &n);

    // Input process details
    for (i = 0; i < n; i++)
    {
        printf("Enter at time and bt time for Process %d: ", i + 1);
        p[i].id = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    // SRTF algorithm using queue
    while (completed < n)
    {
        // Add newly arrived p to the ready queue
        updateQueue(&rq, p, n, current_time);

        // If the ready queue is empty and no process is running
        if (isEmpty(&rq) && cp == NULL)
        {
            current_time++;
            chart[ci++] = 0; // Idle time
            continue;
        }

        // Sort the queue by rt time
        sortByRt(&rq);

        // Get the process with the shortest rt time
        if (cp == NULL)
        {
            cp = dequeue(&rq);
        }
        else
        {
            // Check if there's a process with shorter rt time
            if (!isEmpty(&rq) && peek(&rq)->rt < cp->rt)
            {
                enqueue(&rq, cp);
                cp = dequeue(&rq);
            }
        }

        // Execute the process for one time unit
        cp->rt--;
        chart[ci++] = cp->id;

        // If the process completes
        if (cp->rt == 0)
        {
            cp->ct = current_time + 1;
            cp->tt = cp->ct - cp->at;
            cp->wt = cp->tt - cp->bt;

            total_wt += cp->wt;
            total_tt += cp->tt;

            completed++;
            cp = NULL;
        }

        current_time++;
    }

    // Print Gantt chart
    printf("\nGantt Chart:\n");

    for (i = 0; i < ci; i++)
    {
        (chart[i] == 0) ? printf("| Idle ") : printf("| P%d ", chart[i]);
    }

    // Print process details
    printf("\nProcess\tat\tbt\tct\twt\ttt\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].ct, p[i].wt, p[i].tt);
    }

    printf("\nAverage wt: %.2f", total_wt / n);
    printf("\nAverage tt: %.2f\n", total_tt / n);

    return 0;
}