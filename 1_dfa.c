#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct DFA {
    int nos;                  // Number of states
    int noi;                  // Number of input symbols
    int nof;                  // Number of final states
    int delta[10][10];        // Transition function
    int final[10];            // Final states
} DFA;

int main() {

    DFA d;

    printf("\nEnter no of states: ");
    scanf("%d", &d.nos);

    printf("\nEnter no of input symbols: ");
    scanf("%d", &d.noi);

    getchar();

    // Store input symbols as one string
    char inputSymbols[MAX];

    printf("Enter input symbols separated by spaces: ");
    fgets(inputSymbols, sizeof(inputSymbols), stdin);

    inputSymbols[strcspn(inputSymbols, "\n")] = '\0';


    printf("\nEnter no of final states: ");
    scanf("%d", &d.nof);

    // Store final states
    for(int i = 0; i < d.nof; i++) {
        printf("Enter final state no %d: ", i + 1);
        scanf("%d", &d.final[i]);
    }


    // Read transition table
    printf("\nEnter transitions:\n");

    for(int i = 0; i < d.nos; i++) {

        char temp[MAX];
        strcpy(temp, inputSymbols);

        char *token = strtok(temp, " ");

        int j = 0;

        while(token != NULL && j < d.noi) {

            printf("d(q%d,%s): ", i, token);
            scanf("%d", &d.delta[i][j]);

            token = strtok(NULL, " ");
            j++;
        }
    }


   // Check input strings using do-while

char string[MAX];

do {

    printf("\nEnter string to check: ");
    scanf("%s", string);

    int currentState = 0;
    int valid = 1;

    int i = 0;

    // Traverse the string
    while(string[i] != '\0') {

        char symbol = string[i];

        int symbolIndex = -1;


        // Find symbol index
        char temp[MAX];
        strcpy(temp, inputSymbols);

        char *token = strtok(temp, " ");

        int index = 0;


        while(token != NULL) {

            if(token[0] == symbol) {
                symbolIndex = index;
                break;
            }

            token = strtok(NULL, " ");
            index++;
        }


        // Invalid symbol
        if(symbolIndex == -1) {

            printf("Invalid symbol '%c' in string\n", symbol);
            valid = 0;
            break;

        }


        // DFA transition
        currentState = d.delta[currentState][symbolIndex];

        i++;
    }


    // Check final state
    int accepted = 0;

    for(int i = 0; i < d.nof; i++) {

        if(currentState == d.final[i]) {
            accepted = 1;
            break;
        }

    }


    if(valid) {

        if(accepted)
            printf("String Accepted\n");

        else
            printf("String Rejected\n");

    }


} while(1);

    return 0;
}
