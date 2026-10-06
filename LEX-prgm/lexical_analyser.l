%option noyywrap
%{
#include <stdio.h>

int line_no = 1, sl_no = 1;

#define row(tok) printf("%-6d %-20s %-15s %-6d\n", sl_no++, yytext, tok, line_no)
%}

ID      [a-zA-Z_][a-zA-Z_0-9]*
NUMBER  [0-9]+(\.[0-9]+)?

%%

"int"|"float"|"char"|"double"|"if"|"else"|"while"|"for"|"return"|"void"|"break"|"continue"  row("KEYWORD");
{ID}                                  row("IDENTIFIER");
{NUMBER}                              row("NUMBER");
\"[^"\n]*\"                           row("STRING");
"=="|"!="|"<="|">="|"&&"|"||"|[-+*/=<>]  row("OPERATOR");
[{(]                                  row("OPEN_BRACKET");
[})]                                  row("CLOSE_BRACKET");
[;,]                                  row("PUNCTUATION");
[ \t]+                                ;
\n                                    line_no++;
.                                     row("UNKNOWN");

%%

int main(int argc, char **argv)
{
    if (!(yyin = fopen(argv[1], "r")))
        return printf("Could not open file %s\n", argv[1]), 1;

    printf("%-6s %-20s %-15s %-6s\n--------------------------------------------------------\n",
           "SlNo", "Lexeme", "Token", "LineNo");
    yylex();
    return 0;
}
