#include <stdio.h>
#include <string.h>

char terminal[10], prec[10][10], stack[50], input[50];
int top = -1, n, ip = 0;

int getindex(char c)
{
	for (int i = 0; i < n; i++)
		if (terminal[i] == c)
			return i;
	return -1;
}

char gettop()
{
	for (int i = top; i >= 0; i--)
		if (stack[i] != 'E')
			return stack[i];
	return '$';
}

/* Prints "stack \t\t remaining input \t\t" */
void show()
{
	for (int i = 0; i <= top; i++)
		putchar(stack[i]);
	printf("\t\t%s\t\t", input + ip);
}

int main()
{
	int i, j, row, col, boundary, prev, len;
	char a, b, handle[20];

	printf("Enter no of terminals : ");
	scanf("%d", &n);
	printf("Enter the terminals : ");
	for (i = 0; i < n; i++)
		scanf(" %c", &terminal[i]);

	printf("\nEnter precedence relation\n\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			printf("%c and %c : ", terminal[i], terminal[j]);
			scanf(" %c", &prec[i][j]);
		}

	printf("\nPrecedence Table\n\n     ");
	for (i = 0; i < n; i++)
		printf("%4c", terminal[i]);
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("%4c", terminal[i]);
		for (j = 0; j < n; j++)
			printf("%4c", prec[i][j]);
		printf("\n");
	}

	printf("\nEnter input string (use i and end with $): ");
	scanf("%s", input);
	if (input[strlen(input) - 1] != '$')
		strcat(input, "$");

	stack[++top] = '$';
	printf("\n%-15s %-15s %s\n---------------------------------------------\n", "Stack", "Input", "Action");

	while (1)
	{
		a = gettop();
		b = input[ip];

		if (top == 1 && stack[0] == '$' && stack[1] == 'E' && b == '$')
		{
			show();
			printf("Accept\n");
			break;
		}

		row = getindex(a);
		col = getindex(b);

		if (row == -1 || col == -1 || prec[row][col] == '-')
		{
			show();
			printf("Error\n\nInput string rejected.\n");
			break;
		}

		if (prec[row][col] == '<' || prec[row][col] == '=')
		{
			show();
			printf("Shift %c\n", b);
			stack[++top] = b;
			ip++;
		}
		else if (prec[row][col] == '>')
		{
			/* find nearest '<' relation between consecutive terminals */
			for (prev = boundary = -1, j = top; j >= 0; j--)
				if (stack[j] != 'E')
				{
					if (prev != -1 && prec[getindex(stack[j])][getindex(stack[prev])] == '<')
					{
						boundary = j;
						break;
					}
					prev = j;
				}

			if (boundary == -1)
			{
				printf("Error: Invalid handle\n");
				break;
			}

			len = top - boundary;
			memcpy(handle, stack + boundary + 1, len);
			handle[len] = '\0';

			show();
			if (strcmp(handle, "i") && !(len == 3 && handle[0] == 'E' && handle[2] == 'E'))
			{
				printf("Invalid handle %s\n\nInput string rejected.\n", handle);
				break;
			}
			printf("Reduce E -> %s\n", handle);

			top = boundary;
			stack[++top] = 'E';
		}
		else
		{
			printf("Invalid precedence relation.\n");
			break;
		}
	}
	return 0;
}
