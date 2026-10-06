%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
int yylex(void); int yyerror(char *);
%}

%token NUM
%left '+' '-'
%left '*' '/'
%right '^'

%%
S : E '\n'  { printf("Result: %d\n", $1); exit(0); };
E : E '+' E { $$ = $1 + $3; }
  | E '-' E { $$ = $1 - $3; }
  | E '*' E { $$ = $1 * $3; }
  | E '/' E { $$ = $1 / $3; }
  | E '^' E { $$ = (int)pow($1, $3); }
  | '(' E ')' { $$ = $2; }
  | NUM
  ;
%%

int main(void) {
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

int yylex(void) {
    int ch = getchar();
    if (!isdigit(ch)) return ch;
    ungetc(ch, stdin);
    scanf("%d", &yylval);
    return NUM;
}

int yyerror(char *s) { printf("Invalid expression\n"); return 0; }
