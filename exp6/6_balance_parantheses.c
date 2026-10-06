#include <stdio.h>
#include <string.h>

#define MAX 500

int main(int argc, char *argv[])
{
	const char *open = "({[", *close = ")}]", *p;
	char stack[MAX];
	int lineNo[MAX], top = -1, line = 1, error = 0, ch;

	printf("I am Srishanth S. Here is my paranthesis balance output.\n");

	if (argc != 2)
		return printf("Usage: %s <filename>\n", argv[0]), 0;

	FILE *fp = fopen(argv[1], "r");
	if (!fp)
		return printf("File cannot be opened\n"), 0;

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
			line++;

		if (ch && strchr(open, ch))
		{
			stack[++top] = ch;
			lineNo[top] = line;
		}
		else if (ch && (p = strchr(close, ch)))
		{
			char expected = open[p - close];
			if (top < 0)
				printf("Left %c missing : Identified at line number %d\n", expected, line), error = 1;
			else if (stack[top--] != expected)
				printf("Parentheses mismatch between %c and %c : Identified at line number %d\n", expected == '(' ? stack[top + 1] : stack[top + 1], ch, line), error = 1;
		}
	}
	fclose(fp);

	for (; top >= 0; top--, error = 1)
		printf("Right %c missing : Identified at line number %d\n", close[strchr(open, stack[top]) - open], lineNo[top]);

	if (!error)
		printf("Parentheses are balanced\n");
	return 0;
}
