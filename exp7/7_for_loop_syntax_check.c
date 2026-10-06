#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	char line[500], *p;
	int forno = 0;

	printf("I am Srishanth S\nRoll No : 58\nHere is my for loop syntax checking output.\n\n");

	if (argc < 2)
		return printf("Error: Input file not specified.\nUsage: %s <input_file>\n", argv[0]), 1;

	FILE *fp = fopen(argv[1], "r");
	if (!fp)
		return printf("Error: Cannot open file '%s'.\n", argv[1]), 1;

	while (fgets(line, sizeof line, fp))
		for (p = line; (p = strstr(p, "for"));)
		{
			/* must be the whole word "for" */
			int word = (p == line || !isalnum(p[-1])) && !isalnum(p[3]) && p[3] != '_';
			p += 3;
			if (!word)
				continue;

			printf("For loop %d:\n", ++forno);
			while (isspace(*p))
				p++;

			if (*p != '(')
			{
				printf("  Error: '(' is missing after 'for'.\n\n");
				if (*p)
					p++;
				continue;
			}

			int semi = 0, depth = 1, closed = 0;
			for (p++; *p && !closed; p++)
				semi += *p == ';', depth += (*p == '(') - (*p == ')'), closed = !depth;

			if (!closed)
				printf("  Error: ')' is missing.\n");
			if (semi != 2)
				printf("  Error: Expected 2 semicolons inside 'for' brackets, found %d.\n", semi);
			if (closed && semi == 2)
				printf("  For loop syntax is OK.\n");
			printf("\n");
		}

	fclose(fp);
	if (!forno)
		printf("Error: 'for' loop is not present.\n");
	return 0;
}
