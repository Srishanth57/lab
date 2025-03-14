#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define max 20
char stack[max];
int top = -1;
int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;
    else
        return 0;
}

void push(char c)
{
    if (top == max - 1)
    {
        printf("Stack Overflow\n");
    }
    stack[++top] = c;
}
char pop()
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}
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
            push(c);
        }
        else if (c == ')')
        {
            while (stack[top] != '(' && top != -1)
            {
                postfix[j++] = pop();
            }
            pop();
        }

        else if (isOperator(c))

        {

            while (precedence(c) <= precedence(stack[top]) && top != -1)
            {
                postfix[j++] = pop();
            }
            push(c);
        }

        i++;
    }
    while (top != -1)
    {

        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}
int main()
{
    char infix[max], postfix[max];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("The postfix expression is: %s\n", postfix);
    return 0;
}