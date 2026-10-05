#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ROW 128

static const char *keywords[] = {
	"void", "int", "main", "include", "stdio", "FILE", "argc", "argv", "printf", "fgetc", "fopen", "while",
	"do", "else", "if", "char", "size_t", "ungetc", "fprintf", "for", "ctype", "stdbool", "define"};

static int is_keyword(const char *w)
{
	for (size_t i = 0; i < sizeof keywords / sizeof *keywords; i++)
		if (!strcmp(keywords[i], w))
			return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
		return printf("Input parameter mismatch\n"), 1;

	FILE *in = fopen(argv[1], "r"), *out = fopen(argv[2], "w");
	fprintf(out, "%-8s%-16s%-20s%-6s\n", "SL.NO", "Token", "Lexeme", "Line_no");

	char lex[ROW];
	int ch, next, sl = 1, line = 1;
	while ((ch = fgetc(in)) != EOF)
	{
		if (ch == '\n')
			line++;
		if (isspace(ch) && ch != '\r' && ch != '\v' && ch != '\f')
			continue;

		int i = 0, dot = 0;
		const char *type;
		memset(lex, 0, sizeof lex);
		lex[i++] = ch;

		if (strchr("({[", ch))
			type = "Open_bracket";
		else if (strchr(")}]", ch))
			type = "Close_bracket";
		else if (ch == ';')
			type = "Semicolon";
		else if (strchr("+-*/", ch))
			type = "Arithmetic_op";
		else if (strchr("#.:,_&\"'%|\\", ch))
			type = "Special_op";
		else if (strchr("<>!=", ch))
		{
			if ((next = fgetc(in)) == '=')
				lex[i++] = next;
			else
				ungetc(next, in);
			type = (ch == '=' && i == 1) ? "Assignment_op" : "Relational_op";
		}
		else if (isdigit(ch) || isalpha(ch))
		{
			int digit = isdigit(ch);
			while (i < ROW - 1 && ((digit ? isdigit(next = fgetc(in)) : isalpha(next = fgetc(in))) || (digit && next == '.')))
				dot |= next == '.', lex[i++] = next;
			ungetc(next, in);
			type = digit ? (dot ? "Float" : "Number") : (is_keyword(lex) ? "Keyword" : "Identifier");
		}
		else
			type = "Undefined";

		fprintf(out, "%-8d%-16s%-20s%-6d\n", sl++, lex, type, line);
	}

	fclose(in);
	fclose(out);
	return 0;
}
