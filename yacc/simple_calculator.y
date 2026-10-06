%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int yylex(void);
int yyerror(char *);
%}

%token NUM
%left '+' '-'
%left '*' '/'

%%

S : E '\n'      { printf("Result: %d\n", $1); exit(0); };
E : E '+' E     { $$ = $1 + $3; }
  | E '-' E     { $$ = $1 - $3; }
  | E '*' E     { $$ = $1 * $3; }
  | E '/' E     { $$ = $1 / $3; }
  | NUM
  ;

%%

int main(void)
{
    printf("Enter an expression: ");
    return yyparse();
}

int yylex(void)
{
    int c = getchar();
    if (isdigit(c))
        return ungetc(c, stdin), scanf("%d", &yylval), NUM;
    return c == EOF ? 0 : c;
}

int yyerror(char *s)
{
    return printf("Invalid expression\n"), 0;
}
