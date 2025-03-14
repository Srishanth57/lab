#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

char stack[MAX_STACK_SIZE];
int top = -1;

void push(char c)
{
    if (top == MAX_STACK_SIZE - 1)
    {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

void pop()
{
    if (top == -1)
    {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    top--;
}

bool isMatchingPair(char character1, char character2)
{
    if (character1 == '(' && character2 == ')')
        return true;
    else if (character1 == '[' && character2 == ']')
        return true;
    else if (character1 == '{' && character2 == '}')
        return true;
    else
        return false;
}

bool checkBracesMatch(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return false;
    }

    int ch;
    int lineNumber = 1;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            lineNumber++;
        }
        else if (ch == '(' || ch == '[' || ch == '{')
        {
            push(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            if (top == -1)
            {
                fprintf(stderr, "Error: Unmatched closing brace on line %d\n", lineNumber);
                fclose(file);
                return false;
            }
            if (!isMatchingPair(stack[top], ch))
            {
                fprintf(stderr, "Error: Mismatched braces on line %d\n", lineNumber);
                fclose(file);
                return false;
            }
            pop();
        }
    }

    if (top != -1)
    {
        fprintf(stderr, "Error: Unmatched opening braces\n");
        return false;
    }

    fclose(file);
    return true;
}

int main()
{
    char filename[20];
    printf("Enter filename: ");
    scanf("%s", filename);

    if (checkBracesMatch(filename))
    {
        printf("Braces matching.\n");
    }
    else
    {
        printf("Braces not matching.\n");
    }

    return 0;
}