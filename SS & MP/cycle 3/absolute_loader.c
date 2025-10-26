#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *object;
    object = fopen("object.txt", "r");
    int count = 0, addr;
    char line[100];

    char *token;
    const char *delimiter = "^";
    printf("================================================\n");
    printf("|\t\t\tMemory\t\t\t|\n");
    printf("================================================\n");
    while (fgets(line, 100, object) != NULL)
    {

        if (line[0] == 'T')
        {
            int field_count = 0;

            token = strtok(line, delimiter);
            while (token != NULL)
            {
                if (field_count == 1)
                {
                    addr = (int)strtol(token, NULL, 16);

                    printf("%s\t", token);
                }

                if (field_count >= 3)
                {

                    int flag = 1;
                    for (int i = 0; token[i] != '\0'; i++)
                    {
                        if (token[i] != '0')
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        printf("%08s\t", token);
                    }
                }
                field_count++;
                token = strtok(NULL, delimiter);
            }
            printf("\n");
        }
    }
    return 0;
}