%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int yylex(void); int yyerror(char *);
%}

%token LETTER DIGIT

%%
L : S '\n'    { printf("Valid variable name\n"); exit(0); };
S : LETTER
  | S LETTER
  | S DIGIT
  ;
%%

int main(void) {
    printf("Enter a variable name : ");
    yyparse();
    return 0;
}

int yylex(void) {
    int ch = getchar();
    return isalpha(ch) ? LETTER : isdigit(ch) ? DIGIT : ch;
}

int yyerror(char *s) { printf("Invalid variable name\n"); exit(0); }
