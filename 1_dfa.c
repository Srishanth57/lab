#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int main()
{
    int n, nf, f, len = 0, choice, next[MAX][MAX] = {0}, isFinal[MAX] = {0};
    char temp[MAX], sym[MAX + 1] = "", str[100];

    printf("Number of states: ");
    scanf("%d", &n);

    printf("Input symbols - Q: ");
    scanf(" %[^\n]", temp);
    for (char *p = temp; *p; p++)
        if (*p != ' ')
            sym[len++] = *p;

    printf("Number of final states: ");
    scanf("%d", &nf);
    printf("Enter final states: ");
    while (nf--)
    {
        scanf("%d", &f);
        isFinal[f] = 1;
    }

    for (int j = 0; j < n; j++)
        for (int k = 0; k < len; k++)
        {
            printf("delta(q%d,%c): ", j, sym[k]);
            scanf("%d", &next[j][k]);
        }

    while (1)
    {
        printf("\n\nChoose an option\n1. Enter string\n2. Exit\n");
        scanf("%d", &choice);

        if (choice == 2)
        {
            printf("\nClosing program....\n");
            return 0;
        }
        if (choice != 1)
        {
            printf("Invalid choice");
            continue;
        }

        printf("Enter string: ");
        scanf(" %[^\n]", str);

        int state = 0;
        for (char *p = str; *p; p++)
        {
            char *s = strchr(sym, *p);
            if (!s)
            {
                printf("\n------------------Invalid character %c------------------\n\n", *p);
                exit(0);
            }
            state = next[state][s - sym];
        }

        printf("\n------------------String %s------------------", isFinal[state] ? "accepted" : "rejected");
    }
}
