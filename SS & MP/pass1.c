#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2, *f3, *f4;
    char opcode[20], operand[20], label[20], code[20], mnemonic[20];
    int locctr, start, length;

    f1 = fopen("input.txt", "r");
    f2 = fopen("optab.txt", "r");
    f3 = fopen("symtab.txt", "w");
    f4 = fopen("inter.txt", "w");

    fscanf(f1, "%s%s%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0)
    {
        start = atoi(operand);
        locctr = start;
        fprintf(f4, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(f1, "%s%s%s", label, opcode, operand);
    }
    else
    {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0)
    {
        fprintf(f4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "*") != 0)
        {
            fprintf(f3, "%s\t%d\n", label, locctr);
        }

        rewind(f2);
        int found = 0;
        while (fscanf(f2, "%s%s", code, mnemonic) != EOF)
        {
            if (strcmp(opcode, code) == 0)
            {
                locctr += 3;
                found = 1;
                break;
            }
        }

        if (!found)
        {
            if (strcmp(opcode, "WORD") == 0)
                locctr += 3;
            else if (strcmp(opcode, "RESW") == 0)
                locctr += (3 * atoi(operand));
            else if (strcmp(opcode, "RESB") == 0)
                locctr += atoi(operand);
            else if (strcmp(opcode, "BYTE") == 0)
            {
                if (operand[0] == 'C')
                    locctr += strlen(operand) - 3;
                else if (operand[0] == 'X')
                    locctr += (strlen(operand) - 3) / 2;
            }
        }

        fscanf(f1, "%s%s%s", label, opcode, operand);
    }

    fprintf(f4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    length = locctr - start;
    printf("\nProgram length: %d\n", length);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    return 0;
}