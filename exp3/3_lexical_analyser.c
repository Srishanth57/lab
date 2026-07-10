#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define ROW 128
#define COL 40

static void display_lexemes(int sl_number, int ch, char lexeme[], int line_number, FILE *out)
{
	fprintf(out, "%-8d%-16c%-20s%-6d\n", sl_number, (char)ch, lexeme, line_number);
}

static void display_lexemes_string(int sl_number, char ch[], char lexeme[], int line_number, FILE *out)
{
	fprintf(out, "%-8d%-16s%-20s%-6d\n", sl_number, ch, lexeme, line_number);
}

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		printf("Input parameter mismatch\n");
		return 1;
	}

	char keywords[23][50] = {
		"void", "int", "main", "include", "stdio", "FILE",
		"argc", "argv", "printf", "fgetc", "fopen",
		"while", "do", "else", "if", "char",
		"size_t", "ungetc", "fprintf", "for", "ctype", "stdbool", "define"};

	// Open files
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");

	fprintf(out, "%-8s%-16s%-20s%-6s\n", "SL.NO", "Token", "Lexeme", "Line_no");
	char lexemes[ROW];
	int next, ch;
	int sl_number = 1, line_number = 1;
	while ((ch = fgetc(in)) != EOF)
	{
		int i = 0;
		bool flag = false, increment = true;
		memset(lexemes, 0, sizeof(lexemes));
		if (ch == ' ' || ch == '\t')
			increment = false;
		else if (ch == '\n')
		{
			line_number++;
			increment = false;
		}
		else if (ch == '(' || ch == '{' || ch == '[')
		{
			display_lexemes(sl_number, ch, "Open_bracket", line_number, out);
		}
		else if (ch == ')' || ch == '}' || ch == ']')
		{

			display_lexemes(sl_number, ch, "Close_bracket", line_number, out);
		}
		else if (ch == ';')
		{
			display_lexemes(sl_number, ch, "Semicolon", line_number, out);
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			display_lexemes(sl_number, ch, "Arithmetic_op", line_number, out);
		}
		else if (ch == '#' || ch == '.' || ch == ':' || ch == ',' || ch == '_' || ch == '&' || ch == '\"' || ch == '\'' || ch == '%' ||
				 ch == '|' || ch == '\\' || ch == '&')
		{
			display_lexemes(sl_number, ch, "Special_op", line_number, out);
		}
		else if (ch == '<' || ch == '>' || ch == '!')
		{
			lexemes[i++] = (char)ch;
			next = fgetc(in);
			if (next == '=')
				lexemes[i++] = next;
			else if (next != EOF)
				ungetc(next, in);
			lexemes[i] = '\0';
			display_lexemes_string(sl_number, lexemes, "Relational_op", line_number, out);
		}
		else if (ch == '=')
		{
			lexemes[i++] = (char)ch;
			next = fgetc(in);
			if (next == '=')
			{
				lexemes[i++] = next;
				lexemes[i] = '\0';
				display_lexemes_string(sl_number, lexemes, "Relational_op", line_number, out);
				sl_number++;
				continue;
			}
			ungetc(next, in);
			lexemes[i] = '\0';
			display_lexemes_string(sl_number, lexemes, "Assignment_op", line_number, out);
		}
		else if (isdigit(ch))
		{
			lexemes[i++] = (char)ch;
			while (((ch = fgetc(in)) == isdigit(ch)) || ch == '.')
			{
				if (ch == '.')
					flag = true;
				lexemes[i++] = ch;
			}

			if (ch != EOF)
				ungetc(ch, in);

			if (flag)
				display_lexemes_string(sl_number, lexemes, "Float", line_number, out);
			else
				display_lexemes_string(sl_number, lexemes, "Number", line_number, out);
		}
		else if (isalpha(ch))
		{
			lexemes[i++] = (char)ch;
			while (isalpha(ch = fgetc(in)))
				lexemes[i++] = ch;
			lexemes[i] = '\0';
			for (int i = 0; i < 20; i++)
			{
				if (strcmp(keywords[i], lexemes) == 0)
				{
					flag = true;
					break;
				}
			}

			if (ch != EOF)
				ungetc(ch, in);
			if (flag)
				display_lexemes_string(sl_number, lexemes, "Keyword", line_number, out);
			else
				display_lexemes_string(sl_number, lexemes, "Identifier", line_number, out);
		}
		else
		{
			display_lexemes(sl_number, ch, "Undefined", line_number, out);
		}
		if (increment)
			sl_number++;
	}

	fclose(in);
	fclose(out);

	return 0;
}
