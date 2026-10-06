%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int op, result;
%}

%%

[-+*/^]     op = yytext[0];
[0-9]+      {
                int n = atoi(yytext);
                switch (op)
                {
                case '+': result += n; break;
                case '-': result -= n; break;
                case '*': result *= n; break;
                case '/': result /= n; break;
                case '^': result = pow(result, n); break;
                default:  result = n;
                }
            }
\n          printf("Result : %d", result);
.           printf("Invalid input");

%%

int main(void)
{
    printf("Enter the expression : ");
    yylex();
    return 0;
}
