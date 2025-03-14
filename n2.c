#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node
{
    int data;
    struct Node *next;
};
typedef struct Node *node;

// Function to create a new node
node make(int value)
{
    node newNode = (node)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to create a linked list
node create(node head, int value)
{
    node newNode = make(value);
    if (head == NULL)
    {
        return newNode;
    }
    else
    {
        node temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return head;
}

// Function to insert a node at a specific position
node insert(node head, int value, int position)
{
    node newNode = make(value);
    if (position == 1)
    {
        newNode->next = head;
        return newNode;
    }
    else
    {
        node temp = head;
        for (int i = 1; temp != NULL && i < position - 1; i++)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            printf("Position out of bounds!\n");
        }
        else
        {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
    return head;
}

// Function to delete a node by value
node deleteByValue(node head, int value)
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return head;
    }
    if (head->data == value)
    {
        node temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    node temp = head;
    while (temp->next != NULL && temp->next->data != value)
    {
        temp = temp->next;
    }
    if (temp->next == NULL)
    {
        printf("Value not found!\n");
    }
    else
    {
        node delNode = temp->next;
        temp->next = delNode->next;
        free(delNode);
    }
    return head;
}

// Function to delete a node by position
node deleteByPosition(node head, int position)
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return head;
    }
    if (position == 1)
    {
        node temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    node temp = head;
    for (int i = 1; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL)
    {
        printf("Position out of bounds!\n");
    }
    else
    {
        node delNode = temp->next;
        temp->next = delNode->next;
        free(delNode);
    }
    return head;
}

// Function to search for a value in the linked list
void search(node head, int value)
{
    node temp = head;
    int position = 1;
    while (temp != NULL)
    {
        if (temp->data == value)
        {
            printf("Value found at position %d\n", position);
            return;
        }
        temp = temp->next;
        position++;
    }
    printf("Value not found!\n");
}

// Function to sort the linked list in ascending order
node sort(node head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    for (node i = head; i->next != NULL; i = i->next)
    {
        for (node j = i->next; j != NULL; j = j->next)
        {
            if (i->data > j->data)
            {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    return head;
}

// Function to display the linked list
void display(node head)
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    node temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    node head = NULL;
    int choice, value, position;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Create\n");
        printf("2. Insert\n");
        printf("3. Delete by Value\n");
        printf("4. Delete by Position\n");
        printf("5. Search\n");
        printf("6. Sort\n");
        printf("7. Display\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to create: ");
            scanf("%d", &value);
            head = create(head, value);
            break;
        case 2:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            printf("Enter position to insert: ");
            scanf("%d", &position);
            head = insert(head, value, position);
            break;
        case 3:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            head = deleteByValue(head, value);
            break;
        case 4:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            head = deleteByPosition(head, position);
            break;
        case 5:
            printf("Enter value to search: ");
            scanf("%d", &value);
            search(head, value);
            break;
        case 6:
            head = sort(head);
            printf("List sorted.\n");
            break;
        case 7:
            display(head);
            break;
        case 8:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}