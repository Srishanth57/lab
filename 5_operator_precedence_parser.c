#include <stdio.h>
#include <string.h>

char terminal[10], prec[10][10], stack[50], input[50];
int top = -1, n, ip = 0;

int idx(char c)                       // position of terminal in table
{
	for (int i = 0; i < n; i++)
		if (terminal[i] == c) return i;
	return -1;
}

char gettop()                         // topmost terminal (skips E)
{
	for (int i = top; i >= 0; i--)
		if (stack[i] != 'E') return stack[i];
	return '$';
}

void show()
{
	for (int i = 0; i <= top; i++) putchar(stack[i]);
	printf("\t\t%s\t\t", input + ip);
}

int main()
{
	int i, j;
	char a, b, r, last;

	printf("Enter no of terminals : ");
	scanf("%d", &n);
	printf("Enter the terminals : ");
	for (i = 0; i < n; i++) scanf(" %c", &terminal[i]);

	printf("\nEnter precedence relation (< > = or - for error)\n\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			printf("%c and %c : ", terminal[i], terminal[j]);
			scanf(" %c", &prec[i][j]);
		}

	printf("\nEnter input string (use i): ");
	scanf("%s", input);
	strcat(input, "$");

	stack[++top] = '$';
	printf("\n%-15s %-15s %s\n----------------------------------------\n", "Stack", "Input", "Action");

	while (1)
	{
		a = gettop();
		b = input[ip];
		show();

		if (a == '$' && b == '$') { printf("Accept\n"); break; }

		if (idx(a) < 0 || idx(b) < 0 || (r = prec[idx(a)][idx(b)]) == '-')
		{
			printf("Error\n");
			break;
		}

		if (r == '<' || r == '=')                 // SHIFT
		{
			printf("Shift %c\n", b);
			stack[++top] = b;
			ip++;
		}
		else                                      // REDUCE ('>')
		{
			do {                                  // pop until terminal below is '<' last popped one
				last = gettop();
				while (stack[top] != last) top--; // drop E above terminal
				top--;                            // drop the terminal
			} while (top > 0 && prec[idx(gettop())][idx(last)] != '<');

			if (stack[top] == 'E') top--;         // drop E under the handle (E+E, E*E)
			stack[++top] = 'E';
			printf("Reduce to E\n");
		}
	}
	return 0;
}
