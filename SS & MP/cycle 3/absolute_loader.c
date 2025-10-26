#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *object = fopen("object.txt", "r");
    char line[100], obj_code[70];
    unsigned int addr, len;
    printf("Memory\n");
    while (fgets(line, 100, object) != NULL)
    {
        if (line[0] == 'T')
        {
            sscanf(line, "T^%6X^%2X^%s", &addr, &len, obj_code);
            printf("%04X  ", addr);

            for (int i = 0; i < len * 2; i += 2)
            {
                printf("%c%c", obj_code[i], obj_code[i + 1]);
                if ((i+2) % 8 == 0)
                    printf(" ");
            }
            printf("\n");
        }
    }
    fclose(object);
    return 0;
}