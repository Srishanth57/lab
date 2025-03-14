#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define max 20
char newStack[max];
// Simple tree node structure
typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
} *NODE;

// Simple stack node structure
NODE stack[100];
int top = -1;
// Function to create a new tree node
NODE newNode(char data)
{
    NODE node = (NODE)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to push node onto stack
void push(NODE node)
{
    stack[++top] = node;
}

// Function to pop node from stack
NODE pop()
{
    if (top == -1)
        return NULL;
    else
        return stack[top--];
}
void newpush(char c)
{
    if (top == max - 1)
    {
        printf("Stack Overflow\n");
    }
    newStack[++top] = c;
}
char newpop()
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    return newStack[top--];
}
// Check if character is an operator
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Create expression tree from postfix expression
NODE buildTree(char *postfix)
{

    NODE t, t1, t2;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        // Create a new node
        t = newNode(postfix[i]);

        // If operand, push onto stack
        if (!isOperator(postfix[i]))
        {
            push(t);
        }
        // If operator, pop two nodes
        else
        {
            t1 = pop(); // first operand (right child)
            t2 = pop(); // second operand (left child)
            t->right = t1;
            t->left = t2;
            push(t);
        }
    }

    return pop();
}

// Print prefix expression (preorder traversal)
void printPrefix(struct Node *root)
{
    if (root != NULL)
    {
        printf("%c", root->data);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

// Print postfix expression (postorder traversal)
void printPostfix(NODE root)
{
    if (root != NULL)
    {
        printPostfix(root->left);
        printPostfix(root->right);
        printf("%c", root->data);
    }
}

// Free the tree memory
int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else
        return -1;
}
void infixToPostfix(char infix[], char postfix[])
{
    int i = 0, j = 0;
    char c;
    while ((c = infix[i]) != '\0')
    {

        if (isalpha(c))
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            newpush(c);
        }
        else if (c == ')')
        {
            while (newStack[top] != '(' && top != -1)
            {
                postfix[j++] = newpop();
            }
            newpop();
        }

        else if (isOperator(c))

        {

            while (precedence(c) <= precedence(newStack[top]) && top != -1)
            {
                postfix[j++] = newpop();
            }
            newpush(c);
        }

        i++;
    }
    while (top != -1)
    {

        postfix[j++] = newpop();
    }
    postfix[j] = '\0';
}
int main()
{
    char postfix[50];
    char infix[50];
    printf("Enter INFIX expression (without spaces): ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    top = -1;
    // Build tree from postfix expression
    struct Node *root = buildTree(postfix);

    // Print expressions
    printf("\nPrefix expression: ");
    printPrefix(root);
    printf("\nPostfix expression: ");
    printPostfix(root);
    printf("\n");

    // Clean up

    return 0;
}