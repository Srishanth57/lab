#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Provide input and output file name as command line args.\n");
        return 1;
    }

    FILE *in = fopen(argv[1], "r"), *out = fopen(argv[2], "w");
    if (!in || !out)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int ch, next, prev;
    while ((ch = fgetc(in)) != EOF)
    {
        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        if (ch != '/')
        {
            fputc(ch, out);
            continue;
        }

        next = fgetc(in);
        if (next == '/') // Single-line comment
            while ((ch = fgetc(in)) != EOF && ch != '\n');
        else if (next == '*') // Multi-line comment
            for (prev = 0; (ch = fgetc(in)) != EOF && !(prev == '*' && ch == '/'); prev = ch);
        else // Just a '/'
        {
            fputc('/', out);
            ungetc(next, in); // ungetc(EOF) is a harmless no-op
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
