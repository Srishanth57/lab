#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STATES 20
#define MAX_TRANSITIONS_PER_STATE 10

typedef struct transn
{
    size_t to;
    char symbol;
} transition;

typedef struct dfa
{
    size_t numberOfStates;
    size_t numberOfFinalStates;
    char inputSymbols[MAX_STATES];
    int finalStates[MAX_STATES];
    // 2D Array: transition[from_state][transition_index]
    /*

    [
    0: [[1, 'a'], [0, 'b']],
    1: [[0, 'a'], [1, 'b']]
    ]

    */
    transition transition[MAX_STATES][MAX_TRANSITIONS_PER_STATE];
} dfa;

size_t validateInputString(dfa d, int i)
{
    // Input String
    char str[100];
    printf("Enter string: ");
    scanf(" %[^\n]", str); // Note the space before %

    size_t currentState = 0;

    char *p1 = str;
    while (*p1 != '\0')
    {
        bool symbolFound = false;
        for (size_t j = 0; j < i; j++)
        {
            if (*p1 == d.inputSymbols[j])
            {
                currentState = d.transition[currentState][j].to;
                symbolFound = true;
                break;
            }
        }

        if (!symbolFound)
        {
            printf("\n------------------Invalid character %c------------------\n\n", *p1);
            exit(0);
        }

        p1++;
    }

    return currentState;
}

int main()
{

    dfa d = {0};

    // States
    printf("Number of states: ");
    scanf("%zu", &d.numberOfStates);

    // Input Symbols
    char temp[MAX_STATES];
    printf("Input symbols - Q: ");
    scanf(" %[^\n]", temp); // Note the space before %. Use to read a string and replace the newline with \0 automatically.

    int i = 0;
    for (char *ptr = temp; *ptr != '\0'; ptr++)
    {
        if (*ptr == ' ')
            continue;
        d.inputSymbols[i++] = *ptr;
    }

    // Final States
    printf("Number of final states: ");
    scanf("%zu", &d.numberOfFinalStates);

    printf("Enter final states: ");
    for (size_t f = 0; f < d.numberOfFinalStates; f++)
    {
        scanf("%zu", &d.finalStates[f]);
    }

    // Transition function
    for (size_t j = 0; j < d.numberOfStates; j++)
    {
        for (size_t k = 0; k < i; k++)
        {
            printf("delta(q%zu,%c): ", j, d.inputSymbols[k]);
            scanf("%zu", &d.transition[j][k].to);

            d.transition[j][k].symbol = d.inputSymbols[k];
        }
    }

    // Menu driven
    while (1)
    {
        int value;
        bool accepted = false;
        printf("\n\nChoose an option\n1. Enter string\n2. Exit\n");
        scanf("%d", &value);
        switch (value)
        {
        case 1:
        {
            size_t currentState = validateInputString(d, i);

            accepted = false;
            for (size_t k = 0; k < d.numberOfFinalStates; k++)
            {
                if (currentState == d.finalStates[k])
                    accepted = true;
            }

            printf("\n");
            if (accepted)
                printf("------------------String accepted------------------");
            else
                printf("------------------String rejected------------------");
            break;
        }
        case 2:
            printf("\nClosing program....\n");
            exit(0);
            break;
        default:
            printf("Invalid choice");
            break;
        }
    }
    return 0;
}
