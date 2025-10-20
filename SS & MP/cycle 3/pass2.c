#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2, *f3, *f4;
    char label[20], opcode[20], operand[20], code[20], mnemonic[20], symbol[20];
    char start[20], progname[20], textRecord[100];
    char temp[50];

    int locctr, symaddr, opcodeaddr, len, textLen = 0, textRecordStartAddr;
    long int startAddr, endAddr;

    f1 = fopen("inter.txt", "r");
    f2 = fopen("symtab.txt", "r");
    f3 = fopen("optab.txt", "r");
    f4 = fopen("object.txt", "w");

    if (f1 == NULL || f2 == NULL || f3 == NULL || f4 == NULL)
    {
        perror("Error opening one or more files");
        return 1;
    }

    fscanf(f1, "%s%s%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0)
    {
        strcpy(progname, label);
        strcpy(start, operand);
        startAddr = strtol(start, NULL, 16);
    }
    else
    {
        strcpy(progname, "DEFAULT");
        startAddr = 0;
        rewind(f1);
    }

    long int inter_pos_after_start = ftell(f1);
    while (fscanf(f1, "%x%s%s%s", &locctr, label, opcode, operand) == 4)
    {
        if (strcmp(opcode, "END") == 0)
        {
            endAddr = locctr;
            break;
        }
    }
    len = endAddr - startAddr;

    fseek(f1, inter_pos_after_start, SEEK_SET);

    fprintf(f4, "H^%-6s^%06lX^%06X\n", progname, startAddr, len);

    fscanf(f1, "%x%s%s%s", &locctr, label, opcode, operand);

    textRecordStartAddr = locctr;
    strcpy(textRecord, "");
    textLen = 0;

    while (strcmp(opcode, "END") != 0)
    {
        int currentObjCodeLen = 0;
        strcpy(temp, "");

        rewind(f3);
        int found = 0;

        while (fscanf(f3, "%s%s", code, mnemonic) != EOF)
        {
            if (strcmp(opcode, code) == 0)
            {
                found = 1;
                opcodeaddr = (int)strtol(mnemonic, NULL, 16);
                break;
            }
        }

        if (found)
        {
            rewind(f2);
            symaddr = 0;

            if (strcmp(operand, "--") != 0 && strcmp(operand, "**") != 0)
            {
                while (fscanf(f2, "%s%x", symbol, &symaddr) != EOF)
                {
                    if (strcmp(operand, symbol) == 0)
                    {
                        break;
                    }
                }
            }
            sprintf(temp, "%02X%04X", opcodeaddr, symaddr);
            currentObjCodeLen = 3;
        }
        else if (strcmp(opcode, "WORD") == 0)
        {
            sprintf(temp, "%06X", atoi(operand));
            currentObjCodeLen = 3;
        }
        else if (strcmp(opcode, "BYTE") == 0)
        {
            if (operand[0] == 'C')
            {
                int idx = 0;
                for (int i = 2; operand[i] != '\''; i++)
                {
                    sprintf(temp + idx, "%02X", operand[i]);
                    idx += 2;
                    currentObjCodeLen += 1;
                }
            }
            else if (operand[0] == 'X')
            {
                int idx = 0;
                for (int i = 2; operand[i] != '\''; i++)
                {
                    temp[idx++] = operand[i];
                }
                temp[idx] = '\0';
                currentObjCodeLen = idx / 2;
            }
        }

        if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0)
        {
            if (textLen > 0)
            {
                fprintf(f4, "T^%06X^%02X^%s\n", textRecordStartAddr, textLen, textRecord);
            }
            strcpy(textRecord, "");
            textLen = 0;
        }

        if (currentObjCodeLen > 0)
        {
            if (textLen + currentObjCodeLen > 30)
            {
                fprintf(f4, "T^%06X^%02X^%s\n", textRecordStartAddr, textLen, textRecord);

                strcpy(textRecord, temp);
                textLen = currentObjCodeLen;
                textRecordStartAddr = locctr;
            }
            else
            {
                if (textLen == 0)
                {
                    textRecordStartAddr = locctr;
                }
                strcat(textRecord, temp);
                textLen += currentObjCodeLen;
            }
        }

        fscanf(f1, "%x%s%s%s", &locctr, label, opcode, operand);
    }

    if (textLen > 0)
    {
        fprintf(f4, "T^%06X^%02X^%s\n", textRecordStartAddr, textLen, textRecord);
    }

    fprintf(f4, "E^%06lX\n", startAddr);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    printf("\nObject code generated successfully in object.txt!\n");
    printf("Program length: %d (0x%X)\n", len, len);

    return 0;
}