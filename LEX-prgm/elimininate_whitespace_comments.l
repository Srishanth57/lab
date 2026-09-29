%{
#include<stdio.h>
%}


start \/\*
end \*\/


%%

\/\/(.*)  ;

{start}(.|\n)*{end} ; 

[ \t\n]+ {}; 
%%


int main(int argc, char **argv){

    FILE* fp = fopen(argv[1], "r"); 
    FILE* outfp = fopen("out.c" , "w"); 
    
    if(!fp) {
        printf("could not open file %s\n", argv[1]); 
        return 1; 
    } 
    
    yyin = fp; 
    yyout = outfp; 

    yylex(); 
    
    return 0; 
    
}

int yywrap() {
    return 1; 
}


