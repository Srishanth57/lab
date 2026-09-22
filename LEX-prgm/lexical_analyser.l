%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_no = 1;   /* current line number       */
int sl_no   = 1;   /* serial number for table    */

void print_row(char *lexeme, char *token) {
    printf("%-6d %-20s %-15s %-6d\n", sl_no++, lexeme, token, line_no);
}
%}

DIGIT     [0-9]
LETTER    [a-zA-Z_]
ID        {LETTER}({LETTER}|{DIGIT})*
NUMBER    {DIGIT}+(\.{DIGIT}+)? 

%%

"int"|"float"|"char"|"double"|"if"|"else"|"while"|"for"|"return"|"void"|"break"|"continue" {
    print_row(yytext, "KEYWORD");
}

{ID} {
    print_row(yytext, "IDENTIFIER");
}

{NUMBER} {
    print_row(yytext, "NUMBER");
}

\"([^\"\n])*\" {
    print_row(yytext, "STRING");
}

"=="|"!="|"<="|">="|"&&"|"\|\|" {
    print_row(yytext, "OPERATOR");
}

[+\-*/=<>] {
    print_row(yytext, "OPERATOR");
}

[\{\}\(\)\;\,] {
    print_row(yytext, "PUNCTUATION");
}

[ \t]+     { /* skip whitespace */ }

\n         { line_no++; }

.          { print_row(yytext, "UNKNOWN"); }

%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }
    yyin = file;


    printf("%-6s %-20s %-15s %-6s\n", "SlNo", "Lexeme", "Token", "LineNo");
    printf("--------------------------------------------------------\n");

    yylex();

    return 0;
}
