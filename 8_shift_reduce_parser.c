/*
   Grammar:
   E -> E+E
   E -> E*E
   E -> (E)
   E -> i
*/

#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1, ip = 0;

void printStep(char action[])
{
	printf("%-15.*s %-15s %-15s\n", top + 1, stack, input + ip, action);
}

int reduce()
{
	if (top >= 0 && stack[top] == 'i') /* E -> i */
	{
		stack[top] = 'E';
		return 1;
	}
	if (top >= 2 && (!memcmp(stack + top - 2, "E+E", 3) ||   /* E -> E+E */
					 !memcmp(stack + top - 2, "E*E", 3) ||   /* E -> E*E */
					 !memcmp(stack + top - 2, "(E)", 3)))    /* E -> (E) */
	{
		stack[top -= 2] = 'E';
		return 1;
	}
	return 0;
}

int main()
{
	printf("Enter input string (end with $): ");
	scanf("%49s", input);
	printf("\n%-15s %-15s %-15s\n---------------------------------------------\n", "Stack", "Input", "Action");

	while (1)
	{
		if (input[ip] == '$' && top == 0 && stack[0] == 'E')
		{
			printStep("Accept");
			break;
		}

		if (reduce())
			printStep("Reduce");
		else if (input[ip] && input[ip] != '$')
		{
			if (top >= 48)
			{
				printf("Error: Stack overflow\n");
				break;
			}
			stack[++top] = input[ip++];
			printStep("Shift");
		}
		else
		{
			printStep("Error");
			break;
		}
	}
	return 0;
}
