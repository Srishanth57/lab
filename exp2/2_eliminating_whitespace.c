#include <stdio.h>
#include <stdlib.h>

void eliminateWhiteSpace(FILE *fp1, FILE *fp2)
{
    int ch, next;

    while ((ch = fgetc(fp1)) != EOF)
    {
        switch (ch)
        {
            // Remove whitespace
            case ' ':
            case '\t':
            case '\n':
                break;

            case '/':
                next = fgetc(fp1);

                /* Single-line comment */ 
                if (next == '/')
                {
                    while ((ch = fgetc(fp1)) != EOF && ch != '\n');
                }

                // Multi-line comment
                else if (next == '*')
                {
                    int  prev;

                    while ((ch = fgetc(fp1)) != EOF)
                    {
                        if (prev == '*' && ch == '/')
                            break;
                        prev = ch;
                    }
                }

                else
                {
                    fputc('/', fp2);
                    if (next != EOF)
                        ungetc(next, fp1);
                }
                break;

            default:
                fputc(ch, fp2);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Provide input and output file name as command line args.\n");
        return 1;
    }

    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "w");

    if (fp1 == NULL || fp2 == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    eliminateWhiteSpace(fp1, fp2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}



/* 
	1. Remove whitespace 
	2. Single line comment : Remove until newline or EOF 
	3. Multi line comment : update ch until EOF and save the prev char or value 
	4. Else revert the file pointer 1 step backward with ungetc
 */ 
