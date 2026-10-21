/*
   Grammar:
   E -> E+E | E*E | (E) | i
*/

#include <stdio.h>
#include<string.h>

char stack[50], input[50];
int top = -1, ip = 0;

void show(char *action)
{
	printf("%-15.*s %-15s %s\n", top + 1, stack, input + ip, action);
}

int reduce()
{
	if (top < 0) return 0;

	if (stack[top] == 'i')                          // E -> i
	{
		stack[top] = 'E';
		return 1;
	}

	if (top >= 2)
	{
		char x = stack[top - 2], y = stack[top - 1], z = stack[top];

		if ((x == 'E' && (y == '+' || y == '*') && z == 'E') ||   // E -> E+E, E*E
		    (x == '(' && y == 'E' && z == ')'))                   // E -> (E)
		{
			top -= 2;
			stack[top] = 'E';
			return 1;
		}
	}
	return 0;
}

int main()
{
	printf("Enter input string: ");
	scanf("%s", input);
	strcat(input, "$"); 
	printf("\n%-15s %-15s %s\n-----------------------------------------\n", "Stack", "Input", "Action");

	while (1)
	{
		if (input[ip] == '$' && top == 0 && stack[0] == 'E')
		{
			show("Accept");
			break;
		}

		if (reduce())
			show("Reduce");
		else if (input[ip] != '$' && input[ip] != '\0')
		{
			stack[++top] = input[ip++];
			show("Shift");
		}
		else
		{
			show("Error");
			break;
		}
	}
	return 0;
}
