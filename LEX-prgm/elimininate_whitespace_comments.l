%option noyywrap

%%
"//".*
"/*"(.|\n)*"*/"
[ \t\n]+
%%

int main(int argc, char **argv) {
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("could not open file %s\n", argv[1]);
	return 1;
    }
    yyout = fopen("out.c", "w");
    yylex();
    return 0;
}
